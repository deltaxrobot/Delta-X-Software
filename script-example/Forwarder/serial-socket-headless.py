import sys
import os
import time
import socket
import threading
import subprocess
import importlib
import signal
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

import serial
from serial import Serial, SerialException
from serial.tools import list_ports


class HeadlessEventBus:
    """Simple event bus for headless mode that just prints to console."""
    
    def __init__(self):
        pass
    
    def log(self, message: str):
        timestamp = time.strftime("%H:%M:%S")
        print(f"[{timestamp}] {message}", flush=True)
    
    def serial_status(self, status: str):
        print(f"Serial: {status}", flush=True)
    
    def server_status(self, status: str):
        print(f"Socket: {status}", flush=True)
    
    def found_port(self, port: str):
        self.log(f"Selected port: {port}")
    
    def clients_count(self, count: int):
        print(f"Clients: {count}", flush=True)


class SocketBridgeServer:
    """TCP server on port 8855 that forwards data to/from serial."""

    def __init__(self, bus: HeadlessEventBus, host: str = "0.0.0.0", port: int = 8855):
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
            self.bus.clients_count(0)

        if self._server_thread and self._server_thread.is_alive():
            self._server_thread.join(timeout=1.0)

    def send_to_all_clients(self, data: bytes):
        """Send data from serial to all connected TCP clients."""
        with self._clients_lock:
            for c in self._clients.copy():
                try:
                    c.sendall(data)
                except Exception:
                    try:
                        c.close()
                    except Exception:
                        pass
                    if c in self._clients:
                        self._clients.remove(c)
            if len(self._clients) >= 0:
                self.bus.clients_count(len(self._clients))

    def _run(self):
        try:
            self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self._server_socket.bind((self.host, self.port))
            self._server_socket.listen(5)
            self._server_socket.settimeout(1.0)
            self.bus.server_status(f"Listening on {self.host}:{self.port}")
        except Exception as e:
            self.bus.log(f"Error initializing socket server: {e}")
            return

        while self._running.is_set():
            try:
                client, addr = self._server_socket.accept()
                with self._clients_lock:
                    self._clients.append(client)
                    self.bus.clients_count(len(self._clients))
                self.bus.log(f"Client connected: {addr}")
                client_thread = threading.Thread(
                    target=self._handle_client,
                    args=(client, addr),
                    name=f"Client-{addr}",
                    daemon=True
                )
                client_thread.start()
            except socket.timeout:
                continue
            except Exception as e:
                if self._running.is_set():
                    self.bus.log(f"Accept error: {e}")
                    time.sleep(0.2)

        self.bus.server_status("Socket server stopped")

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
                        self.bus.log(f"Serial write error: {e}")
        finally:
            try:
                client.close()
            except Exception:
                pass
            with self._clients_lock:
                if client in self._clients:
                    self._clients.remove(client)
                self.bus.clients_count(len(self._clients))
            self.bus.log(f"Client disconnected: {addr}")


class SerialBridge:
    """Scan serial ports, find the one replying YesDelta to IsDelta, and bridge."""

    def __init__(self, bus: HeadlessEventBus, baudrate: int = 115200, handshake_tx: bytes = b"IsDelta\n", handshake_expect: bytes = b"YesDelta"):
        self.bus = bus
        self.baudrate = baudrate
        self.handshake_tx = handshake_tx
        self.handshake_expect = handshake_expect
        self._stop = threading.Event()
        self._serial: Optional[Serial] = None
        self._reader_thread: Optional[threading.Thread] = None
        self._scanner_thread: Optional[threading.Thread] = None
        self._socket_server: Optional[SocketBridgeServer] = None

    def set_socket_server(self, ss: SocketBridgeServer):
        self._socket_server = ss

    def start(self):
        if self._scanner_thread and self._scanner_thread.is_alive():
            return
        self._stop.clear()
        self._scanner_thread = threading.Thread(target=self._scan_loop, name="SerialScanner", daemon=True)
        self._scanner_thread.start()

    def stop(self):
        self._stop.set()
        self._close_serial()
        if self._scanner_thread and self._scanner_thread.is_alive():
            self._scanner_thread.join(timeout=2.0)

    def rescan(self, new_baud: int):
        self.baudrate = new_baud
        self._close_serial()

    def write_to_serial(self, data: bytes):
        """Send data from TCP client to serial port."""
        if self._serial and self._serial.is_open:
            try:
                self._serial.write(data)
                return True
            except Exception as e:
                self.bus.log(f"Serial write error: {e}")
                self._close_serial()
        return False

    def _close_serial(self):
        if self._serial:
            try:
                self._serial.close()
            except Exception:
                pass
            self._serial = None
        self.bus.serial_status("Closed")

    def _scan_loop(self):
        while not self._stop.is_set():
            if not self._serial or not self._serial.is_open:
                found_port = self._scan_for_device()
                if found_port:
                    self.bus.found_port(found_port)
                    self._start_reader()
                else:
                    self.bus.serial_status("Scanning...")
            time.sleep(2.0)

    def _scan_for_device(self) -> Optional[str]:
        """Scan all serial ports looking for our device."""
        ports = list_ports.comports()
        for port_info in ports:
            port_name = port_info.device
            try:
                ser = Serial(port_name, baudrate=self.baudrate, timeout=2.0)
                time.sleep(0.1)  # Let it settle
                ser.write(self.handshake_tx)
                ser.flush()
                
                # Read response
                start_time = time.time()
                response = b""
                while time.time() - start_time < 2.0:
                    if ser.in_waiting > 0:
                        chunk = ser.read(ser.in_waiting)
                        response += chunk
                        if self.handshake_expect in response:
                            self._serial = ser
                            self.bus.serial_status(f"Connected to {port_name}")
                            return port_name
                ser.close()
            except Exception as e:
                self.bus.log(f"Error testing {port_name}: {e}")
                continue
        return None

    def _start_reader(self):
        if self._reader_thread and self._reader_thread.is_alive():
            return
        if not self._serial:
            return
        self._reader_thread = threading.Thread(target=self._reader_loop, name="SerialReader", daemon=True)
        self._reader_thread.start()

    def _reader_loop(self):
        """Read from serial and forward to all TCP clients."""
        while not self._stop.is_set() and self._serial and self._serial.is_open:
            try:
                if self._serial.in_waiting > 0:
                    data = self._serial.read(self._serial.in_waiting)
                    if data and self._socket_server:
                        self._socket_server.send_to_all_clients(data)
                else:
                    time.sleep(0.01)
            except Exception as e:
                self.bus.log(f"Serial read error: {e}")
                self._close_serial()
                break


class HeadlessApplication:
    """Headless version of the serial-socket bridge application."""
    
    def __init__(self, baudrate: int = 115200, socket_host: str = "0.0.0.0", socket_port: int = 8855):
        self.bus = HeadlessEventBus()
        self.socket_server = SocketBridgeServer(self.bus, socket_host, socket_port)
        self.serial_bridge = SerialBridge(self.bus, baudrate)
        self.running = True
        
        # Wire them together
        self.serial_bridge.set_socket_server(self.socket_server)
        self.socket_server.set_on_client_data(self.serial_bridge.write_to_serial)
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
    
    def _signal_handler(self, signum, frame):
        print(f"\nReceived signal {signum}, stopping application...")
        self.stop()
    
    def start(self):
        """Start the headless application."""
        self.bus.log("Starting headless application...")
        
        # Start services
        self.socket_server.start()
        self.serial_bridge.start()
        
        self.bus.log("Application started. Press Ctrl+C to stop.")
        
        try:
            # Keep the main thread alive
            while self.running:
                time.sleep(1.0)
        except KeyboardInterrupt:
            self.bus.log("Received Ctrl+C, stopping...")
        finally:
            self.stop()
    
    def stop(self):
        """Stop the application gracefully."""
        self.running = False
        try:
            self.serial_bridge.stop()
        except Exception:
            pass
        try:
            self.socket_server.stop()
        except Exception:
            pass
        self.bus.log("Application stopped.")


def main():
    import argparse
    
    parser = argparse.ArgumentParser(description="Serial-Socket Bridge (Headless Mode)")
    parser.add_argument("--baudrate", type=int, default=115200, help="Serial baudrate (default: 115200)")
    parser.add_argument("--host", default="0.0.0.0", help="Socket server host (default: 0.0.0.0)")
    parser.add_argument("--port", type=int, default=8855, help="Socket server port (default: 8855)")
    
    args = parser.parse_args()
    
    app = HeadlessApplication(args.baudrate, args.host, args.port)
    app.start()


if __name__ == "__main__":
    main()
