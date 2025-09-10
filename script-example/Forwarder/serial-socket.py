import sys
import os
import time
import socket
import threading
import subprocess
import importlib
from typing import Optional, List


def ensure_dependency(module: str, package: Optional[str] = None) -> None:
    """Ensure a Python module is importable; if not, install the package via pip."""
    try:
        importlib.import_module(module)
        return
    except Exception:
        pkg = package or module
        try:
            print(f"[setup] Installing {pkg}...", flush=True)
            subprocess.check_call([sys.executable, "-m", "pip", "install", pkg])
        except subprocess.CalledProcessError as e:
            print(f"[setup] Failed to install {pkg}: {e}", flush=True)
            raise
        # Try again
        importlib.invalidate_caches()
        importlib.import_module(module)


# Ensure required dependencies before importing them
ensure_dependency("serial", "pyserial")
ensure_dependency("PyQt5", "PyQt5")

from PyQt5 import QtCore, QtWidgets
import serial
from serial import Serial, SerialException
from serial.tools import list_ports


class UIEventBus(QtCore.QObject):
    log = QtCore.pyqtSignal(str)
    serial_status = QtCore.pyqtSignal(str)
    server_status = QtCore.pyqtSignal(str)
    found_port = QtCore.pyqtSignal(str)
    clients_count = QtCore.pyqtSignal(int)


class SocketBridgeServer:
    """TCP server on port 8855 that forwards data to/from serial."""

    def __init__(self, bus: UIEventBus, host: str = "0.0.0.0", port: int = 8855):
        self.bus = bus
        self.host = host
        self.port = port
        self._server_socket: Optional[socket.socket] = None
        self._server_thread: Optional[threading.Thread] = None
        self._running = threading.Event()
        self._clients: List[socket.socket] = []
        self._clients_lock = threading.Lock()
        self._on_data_from_client = None  # type: Optional[callable]

    def set_on_client_data(self, cb):
        self._on_data_from_client = cb

    def start(self):
        if self._server_thread and self._server_thread.is_alive():
            return
        self._running.set()
        self._server_thread = threading.Thread(target=self._run, name="SocketServer", daemon=True)
        self._server_thread.start()

    def stop(self):
        self._running.clear()
        try:
            if self._server_socket:
                try:
                    self._server_socket.shutdown(socket.SHUT_RDWR)
                except Exception:
                    pass
                try:
                    self._server_socket.close()
                except Exception:
                    pass
        finally:
            self._server_socket = None

        with self._clients_lock:
            for c in self._clients:
                try:
                    c.shutdown(socket.SHUT_RDWR)
                except Exception:
                    pass
                try:
                    c.close()
                except Exception:
                    pass
            self._clients.clear()
            self.bus.clients_count.emit(0)

        if self._server_thread and self._server_thread.is_alive():
            self._server_thread.join(timeout=1.0)

    def broadcast(self, data: bytes):
        if not data:
            return
        dead = []
        with self._clients_lock:
            for c in list(self._clients):
                try:
                    c.sendall(data)
                except Exception:
                    dead.append(c)
            for d in dead:
                try:
                    d.close()
                except Exception:
                    pass
                if d in self._clients:
                    self._clients.remove(d)
            if dead:
                self.bus.clients_count.emit(len(self._clients))

    def _run(self):
        try:
            srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            srv.bind((self.host, self.port))
            srv.listen(5)
            srv.settimeout(1.0)
            self._server_socket = srv
            self.bus.server_status.emit(f"Đã mở socket {self.host}:{self.port}")
        except Exception as e:
            self.bus.server_status.emit(f"Không mở được socket trên cổng {self.port}: {e}")
            self.bus.log.emit(f"Socket error: {e}")
            return

        while self._running.is_set():
            try:
                try:
                    client, addr = self._server_socket.accept()
                except socket.timeout:
                    continue
                except OSError:
                    break
                self.bus.log.emit(f"Client kết nối: {addr}")
                with self._clients_lock:
                    self._clients.append(client)
                    self.bus.clients_count.emit(len(self._clients))
                t = threading.Thread(target=self._handle_client, args=(client, addr), daemon=True)
                t.start()
            except Exception as e:
                self.bus.log.emit(f"Lỗi accept: {e}")
                time.sleep(0.2)

        self.bus.server_status.emit("Socket server đã dừng")

    def _handle_client(self, client: socket.socket, addr):
        try:
            client.settimeout(1.0)
            while self._running.is_set():
                try:
                    data = client.recv(4096)
                except socket.timeout:
                    continue
                except ConnectionResetError:
                    break
                except OSError:
                    break
                if not data:
                    break
                # push to serial
                if self._on_data_from_client:
                    try:
                        self._on_data_from_client(data)
                    except Exception as e:
                        self.bus.log.emit(f"Ghi serial lỗi: {e}")
        finally:
            try:
                client.close()
            except Exception:
                pass
            with self._clients_lock:
                if client in self._clients:
                    self._clients.remove(client)
                self.bus.clients_count.emit(len(self._clients))
            self.bus.log.emit(f"Client ngắt: {addr}")


class SerialBridge:
    """Scan serial ports, find the one replying YesDelta to IsDelta, and bridge."""

    def __init__(self, bus: UIEventBus, baudrate: int = 115200, handshake_tx: bytes = b"IsDelta\n", handshake_expect: bytes = b"YesDelta"):
        self.bus = bus
        self.baudrate = baudrate
        self.handshake_tx = handshake_tx
        self.handshake_expect = handshake_expect
        self._stop = threading.Event()
        self._serial: Optional[Serial] = None
        self._reader_thread: Optional[threading.Thread] = None
        self._scanner_thread: Optional[threading.Thread] = None
        self._socket_server: Optional[SocketBridgeServer] = None
        self.connected_port: Optional[str] = None

    def set_socket_server(self, server: SocketBridgeServer):
        self._socket_server = server

    def start(self):
        if self._scanner_thread and self._scanner_thread.is_alive():
            return
        self._stop.clear()
        self._scanner_thread = threading.Thread(target=self._scan_loop, name="SerialScanner", daemon=True)
        self._scanner_thread.start()

    def stop(self):
        self._stop.set()
        try:
            if self._serial and self._serial.is_open:
                try:
                    self._serial.close()
                except Exception:
                    pass
        finally:
            self._serial = None

    def rescan(self, baudrate: Optional[int] = None):
        if baudrate:
            self.baudrate = baudrate
        self.stop()
        time.sleep(0.2)
        self.start()

    def write(self, data: bytes):
        ser = self._serial
        if not ser or not ser.is_open:
            return
        try:
            ser.write(data)
        except Exception as e:
            self.bus.log.emit(f"Serial write error: {e}")

    def _scan_loop(self):
        self.bus.serial_status.emit("Đang quét cổng...")
        while not self._stop.is_set():
            ports = list(list_ports.comports())
            if not ports:
                self.bus.log.emit("Không tìm thấy cổng nào. Chờ 2s...")
                time.sleep(2.0)
                continue
            for p in ports:
                if self._stop.is_set():
                    break
                dev = getattr(p, "device", None) or getattr(p, "name", None) or str(p)
                if not dev:
                    continue
                self.bus.log.emit(f"Thử {dev} @ {self.baudrate}")
                try:
                    if self._probe_port(dev):
                        self.connected_port = dev
                        self.bus.found_port.emit(dev)
                        self.bus.serial_status.emit(f"Đã kết nối {dev} @ {self.baudrate}")
                        self._reader_thread = threading.Thread(target=self._read_loop, name="SerialReader", daemon=True)
                        self._reader_thread.start()
                        # Stay until disconnected or rescan requested
                        while not self._stop.is_set() and self._serial and self._serial.is_open:
                            time.sleep(0.2)
                        break
                except Exception as e:
                    self.bus.log.emit(f"Lỗi khi thử {dev}: {e}")
            if self._stop.is_set():
                break
            # If not connected, wait and retry
            if not (self._serial and self._serial.is_open):
                self.bus.serial_status.emit("Chưa tìm thấy thiết bị Delta. Thử lại sau 3s...")
                time.sleep(3.0)

    def _probe_port(self, dev: str) -> bool:
        try:
            ser = Serial(dev, self.baudrate, timeout=0.3, write_timeout=0.3)
        except Exception as e:
            self.bus.log.emit(f"Không mở được {dev}: {e}")
            return False
        try:
            # Give device a moment
            time.sleep(0.15)
            try:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
            except Exception:
                pass
            ser.write(self.handshake_tx)
            ser.flush()
            deadline = time.time() + 1.0
            buf = b""
            while time.time() < deadline:
                chunk = ser.read(64)
                if chunk:
                    buf += chunk
                    if self.handshake_expect in buf:
                        # Keep port open for session
                        self._serial = ser
                        return True
            return False
        finally:
            if self._serial is not ser:
                try:
                    ser.close()
                except Exception:
                    pass

    def _read_loop(self):
        ser = self._serial
        if not ser or not ser.is_open:
            return
        self.bus.log.emit("Bắt đầu đọc dữ liệu từ serial...")
        while not self._stop.is_set():
            try:
                n = ser.in_waiting if hasattr(ser, "in_waiting") else 0
                if n:
                    data = ser.read(n)
                else:
                    data = ser.read(1)  # small timeout applies
                if data:
                    if self._socket_server:
                        self._socket_server.broadcast(data)
                    # Log compactly (limit preview)
                    preview = data[:32]
                    dots = "..." if len(data) > 32 else ""
                    try:
                        txt = preview.decode(errors="replace")
                    except Exception:
                        txt = str(preview)
                    self.bus.log.emit(f"Serial → Socket {len(data)}B: {txt}{dots}")
            except (SerialException, OSError) as e:
                self.bus.log.emit(f"Serial lỗi: {e}. Thử quét lại...")
                break
            except Exception as e:
                self.bus.log.emit(f"Lỗi đọc serial: {e}")
                time.sleep(0.1)
        # Cleanup and trigger rescan
        try:
            if ser and ser.is_open:
                ser.close()
        except Exception:
            pass
        self._serial = None
        if not self._stop.is_set():
            # trigger rescan quietly
            self.bus.serial_status.emit("Mất kết nối serial. Đang quét lại...")


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Delta Serial ↔ Socket (8855)")
        self.resize(640, 440)

        self.bus = UIEventBus()
        self.socket_server = SocketBridgeServer(self.bus)
        self.serial_bridge = SerialBridge(self.bus)
        self.socket_server.set_on_client_data(self.serial_bridge.write)
        self.serial_bridge.set_socket_server(self.socket_server)

        # UI
        cw = QtWidgets.QWidget()
        v = QtWidgets.QVBoxLayout(cw)

        # Row: status
        row = QtWidgets.QHBoxLayout()
        self.lbl_serial = QtWidgets.QLabel("Serial: chưa kết nối")
        self.lbl_server = QtWidgets.QLabel("Socket: chưa mở")
        self.lbl_clients = QtWidgets.QLabel("Clients: 0")
        row.addWidget(self.lbl_serial)
        row.addStretch(1)
        row.addWidget(self.lbl_server)
        row.addStretch(1)
        row.addWidget(self.lbl_clients)
        v.addLayout(row)

        # Row: controls
        ctrl = QtWidgets.QHBoxLayout()
        ctrl.addWidget(QtWidgets.QLabel("Baud:"))
        self.cmb_baud = QtWidgets.QComboBox()
        for b in [115200, 57600, 38400, 19200, 9600]:
            self.cmb_baud.addItem(str(b), b)
        self.cmb_baud.setCurrentText("115200")
        self.btn_rescan = QtWidgets.QPushButton("Quét lại")
        self.btn_rescan.clicked.connect(self.on_rescan)
        ctrl.addWidget(self.cmb_baud)
        ctrl.addWidget(self.btn_rescan)
        ctrl.addStretch(1)
        v.addLayout(ctrl)

        # Log
        self.txt_log = QtWidgets.QPlainTextEdit()
        self.txt_log.setReadOnly(True)
        v.addWidget(self.txt_log)

        self.setCentralWidget(cw)

        # Signals
        self.bus.log.connect(self._append_log)
        self.bus.serial_status.connect(self._set_serial_status)
        self.bus.server_status.connect(self._set_server_status)
        self.bus.found_port.connect(self._set_found_port)
        self.bus.clients_count.connect(self._set_clients_count)

        # Start services
        self.socket_server.start()
        self.serial_bridge.start()

    # UI slots
    @QtCore.pyqtSlot()
    def on_rescan(self):
        b = int(self.cmb_baud.currentText())
        self.bus.log.emit(f"Yêu cầu quét lại với baud {b}")
        self.serial_bridge.rescan(b)

    @QtCore.pyqtSlot(str)
    def _append_log(self, line: str):
        t = time.strftime("%H:%M:%S")
        self.txt_log.appendPlainText(f"[{t}] {line}")

    @QtCore.pyqtSlot(str)
    def _set_serial_status(self, s: str):
        self.lbl_serial.setText(f"Serial: {s}")

    @QtCore.pyqtSlot(str)
    def _set_server_status(self, s: str):
        self.lbl_server.setText(f"Socket: {s}")

    @QtCore.pyqtSlot(str)
    def _set_found_port(self, p: str):
        self._append_log(f"Đã chọn cổng: {p}")

    @QtCore.pyqtSlot(int)
    def _set_clients_count(self, n: int):
        self.lbl_clients.setText(f"Clients: {n}")

    def closeEvent(self, event):
        try:
            self.serial_bridge.stop()
        except Exception:
            pass
        try:
            self.socket_server.stop()
        except Exception:
            pass
        super().closeEvent(event)


def main():
    # For Windows high-DPI friendliness
    try:
        QtWidgets.QApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
        QtWidgets.QApplication.setAttribute(QtCore.Qt.AA_UseHighDpiPixmaps)
    except Exception:
        pass

    app = QtWidgets.QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
