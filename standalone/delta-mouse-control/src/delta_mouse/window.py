"""Replaceable UI; only ControllerWorker is used to operate the robot."""

import time

from PySide6.QtCore import QEvent, QPointF, QSettings, Qt, QTimer
from PySide6.QtGui import QColor, QPainter, QPen
from PySide6.QtWidgets import (
    QApplication, QCheckBox, QComboBox, QDoubleSpinBox, QFormLayout,
    QGroupBox, QHBoxLayout, QLabel, QMainWindow, QMessageBox,
    QPlainTextEdit, QPushButton, QSpinBox, QVBoxLayout, QWidget,
)

from .capture import RelativeCapture
from .session import MouseSettings
from .worker import ControllerWorker


class MousePad(QWidget):
    def __init__(self, window):
        super().__init__()
        self.owner = window
        self.last = QPointF()
        self.setMinimumSize(390, 290)
        self.setFocusPolicy(Qt.FocusPolicy.StrongFocus)
        self.setCursor(Qt.CursorShape.CrossCursor)

    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            self.setFocus()
            self.last = event.position()
            self.owner.begin_drag()
            event.accept()

    def mouseMoveEvent(self, event):
        if not self.owner.dragging:
            return
        if not event.buttons() & Qt.MouseButton.LeftButton:
            self.owner.end_drag()
        elif not self.owner.capture.active:
            if not self.rect().contains(event.position().toPoint()):
                self.owner.end_drag()
            else:
                delta = event.position() - self.last
                self.last = event.position()
                self.owner.input_delta(delta.x(), delta.y(), 0)

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            self.owner.end_drag()

    def wheelEvent(self, event):
        # Raw mode already consumed RI_MOUSE_WHEEL; never count it twice.
        if self.owner.dragging and not self.owner.capture.active:
            self.owner.input_delta(0, 0, event.angleDelta().y() / 120.0)
        event.accept()

    def leaveEvent(self, event):
        if not self.owner.capture.active:
            self.owner.end_drag()

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.RenderHint.Antialiasing)
        painter.fillRect(self.rect(), QColor("#ecf1ef"))
        painter.setPen(QPen(QColor("#d2ded8"), 1))
        for x in range(0, self.width(), 24):
            for y in range(0, self.height(), 24):
                painter.drawPoint(x, y)
        painter.setPen(QColor("#254b3b"))
        font = painter.font()
        font.setPointSize(17)
        painter.setFont(font)
        painter.drawText(self.rect().adjusted(12, 0, -12, -25), Qt.AlignmentFlag.AlignCenter,
                         "HOLD + MOVE" if not self.owner.dragging else "FOLLOWING MOUSE")
        font.setPointSize(10)
        painter.setFont(font)
        painter.drawText(self.rect().adjusted(12, 70, -12, 0), Qt.AlignmentFlag.AlignCenter,
                         "X / Y: move     Z: scroll\nRelease or Esc: brake")
        painter.setPen(QPen(QColor("#59806d"), 1))
        painter.drawRect(self.rect().adjusted(0, 0, -1, -1))


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Delta Mouse Control 1.0.0 | Adaptive follower v2")
        self.resize(980, 720)
        self.worker = ControllerWorker()
        self.dragging = self.shutting_down = False
        self.hold_requested_at = 0.0
        self.input_error = ""
        self.settings = QSettings()
        self.capture = RelativeCapture(self.input_delta, self.end_drag, self.capture_failed)
        central = QWidget()
        self.setCentralWidget(central)
        outer = QVBoxLayout(central)
        outer.setContentsMargins(24, 20, 24, 20)
        title = QLabel("DELTA / MOUSE")
        title.setObjectName("heading")
        outer.addWidget(title)
        outer.addWidget(QLabel("Standalone motion control  /  Delta X 3  /  Python"))
        row = QHBoxLayout()
        outer.addLayout(row, 1)
        controls = QVBoxLayout()
        row.addLayout(controls, 2)
        connection = QGroupBox("01   Connection")
        form = QFormLayout(connection)
        self.mode = QComboBox()
        self.mode.addItems(["Simulator", "Serial"])
        self.port = QComboBox()
        self.port.setEditable(True)
        self.refresh_ports()
        self.port.setEditText(self.settings.value("port", ""))
        self.baud = QComboBox()
        self.baud.setEditable(True)
        self.baud.addItems(["9600", "57600", "115200", "230400", "250000", "460800", "921600"])
        self.baud.setCurrentText(str(self.settings.value("baud", 115200)))
        form.addRow("Mode", self.mode)
        form.addRow("Port", self.port)
        form.addRow("Baudrate", self.baud)
        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect_robot)
        self.refresh_button = QPushButton("Refresh ports")
        self.refresh_button.clicked.connect(self.refresh_ports)
        form.addRow(self.refresh_button, self.connect_button)
        self.home_button = QPushButton("Home robot")
        self.home_button.clicked.connect(self.home_robot)
        self.homed = QCheckBox("Already homed; position is established")
        self.arm_button = QPushButton("Enable mouse")
        self.arm_button.clicked.connect(lambda: self.worker.post("arm"))
        form.addRow(self.home_button)
        form.addRow(self.homed)
        form.addRow(self.arm_button)
        controls.addWidget(connection)

        tuning = QGroupBox("02   Mouse mapping")
        mapping = QFormLayout(tuning)
        self.xy = QDoubleSpinBox()
        self.xy.setRange(0.01, 1)
        self.xy.setSingleStep(0.01)
        self.xy.setValue(float(self.settings.value("xy", 0.15)))
        self.z = QDoubleSpinBox()
        self.z.setRange(0.25, 2)
        self.z.setSingleStep(0.25)
        self.z.setSuffix(" mm/notch")
        self.z.setValue(float(self.settings.value("z", 1)))
        self.speed = QSpinBox()
        self.speed.setRange(10, 150)
        self.speed.setSuffix(" mm/s")
        self.speed.setValue(int(self.settings.value("speed", 100)))
        self.continuous = QCheckBox("Continuous capture (Windows)")
        self.continuous.setEnabled(self.capture.available)
        self.continuous.setChecked(self.capture.available and self.settings.value("continuous", True, type=bool))
        self.continuous.toggled.connect(self.capture_mode_changed)
        self.capture_mode_changed()
        mapping.addRow("XY sensitivity", self.xy)
        mapping.addRow("Wheel Z step", self.z)
        mapping.addRow("Speed limit", self.speed)
        mapping.addRow(self.continuous)
        self.mapping_explanation = QLabel()
        self.mapping_explanation.setWordWrap(True)
        mapping.addRow(self.mapping_explanation)
        self.update_mapping_label()
        for control in (self.xy, self.z, self.speed):
            control.valueChanged.connect(self.update_mapping)
        controls.addWidget(tuning)
        controls.addStretch()

        right = QVBoxLayout()
        row.addLayout(right, 3)
        self.pad = MousePad(self)
        right.addWidget(self.pad, 1)
        self.coordinates = QLabel()
        self.coordinates.setObjectName("coordinates")
        right.addWidget(self.coordinates)
        self.metrics = QLabel()
        right.addWidget(self.metrics)
        self.status = QLabel("Choose a connection to begin.")
        self.status.setWordWrap(True)
        right.addWidget(self.status)
        self.stop_button = QPushButton("Release / brake   [Esc]")
        self.stop_button.clicked.connect(self.stop_motion)
        right.addWidget(self.stop_button)
        note = QLabel("Hold LEFT while scrolling for Z. Release, Esc or loss of focus cancels the unsent target; "
                      "committed moves and the braking tail finish. This is not an emergency stop. "
                      "Disconnect the robot in Delta X Software before opening its port here.")
        note.setWordWrap(True)
        outer.addWidget(note)
        self.log = QPlainTextEdit()
        self.log.setReadOnly(True)
        self.log.setMaximumBlockCount(250)
        self.log.setMaximumHeight(130)
        self.log.setPlaceholderText("G-code TX / RX log")
        outer.addWidget(self.log)
        self.setStyleSheet("""
            QMainWindow { background: #f8f7f2; }
            QWidget { color: #243d32; font-family: 'Bahnschrift', 'Segoe UI'; font-size: 13px; }
            QLabel#heading { font-size: 30px; font-weight: 700; }
            QGroupBox { border: 1px solid #cbd5cd; border-radius: 6px; margin-top: 12px; padding-top: 14px; }
            QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }
            QPushButton { background: #245d46; color: white; border: none; border-radius: 4px; padding: 9px; }
            QPushButton:disabled { background: #cdd5ce; color: #697b70; }
            QComboBox, QSpinBox, QDoubleSpinBox { background: white; border: 1px solid #b9c7bc; padding: 6px; }
            QPlainTextEdit, QLabel#coordinates { font-family: 'Cascadia Mono', 'Consolas'; font-size: 12px; }
            QPlainTextEdit { background: #edf0ea; border: 1px solid #cbd5cd; }
        """)
        QApplication.instance().installEventFilter(self)
        self.timer = QTimer(self)
        self.timer.setInterval(30)
        self.timer.timeout.connect(self.refresh)
        self.timer.start()
        self.refresh()

    def refresh_ports(self):
        from serial.tools.list_ports import comports
        previous = self.port.currentText()
        self.port.clear()
        self.port.addItems([p.device for p in comports()])
        if previous:
            self.port.setEditText(previous)

    def mouse_settings(self):
        return MouseSettings(self.xy.value(), self.z.value())

    def update_mapping(self):
        self.update_mapping_label()
        self.worker.post("settings", self.mouse_settings(), self.speed.value())

    def update_mapping_label(self):
        unit = "counts" if self.continuous.isChecked() else "pixels"
        note = "Raw movement depends on mouse DPI." if self.continuous.isChecked() else "Leaving the pad stops this mode."
        self.mapping_explanation.setText(f"100 mouse {unit} requests {100 * self.xy.value():g} mm.\n{note}")

    def capture_mode_changed(self):
        self.end_drag()
        self.input_error = ""
        self.xy.setSuffix(" mm/count" if self.continuous.isChecked() else " mm/pixel")
        if hasattr(self, "mapping_explanation"):
            self.update_mapping_label()

    def connect_robot(self):
        snapshot = self.worker.snapshot()
        if snapshot.state not in ("disconnected", "closed"):
            self.end_drag()
            self.worker.post("disconnect")
            return
        try:
            baudrate = int(self.baud.currentText())
            if baudrate <= 0:
                raise ValueError()
        except ValueError:
            self.status.setText("Enter a positive integer baudrate.")
            return
        self.homed.setChecked(False)
        self.worker.post("connect", self.mode.currentText(), self.port.currentText().strip(),
                         baudrate, self.mouse_settings(), self.speed.value())
        self.connect_button.setEnabled(False)

    def home_robot(self):
        if self.mode.currentText() == "Serial":
            answer = QMessageBox.question(self, "Home robot", "G28 moves the robot and its servos to home.\nStart homing now?")
            if answer != QMessageBox.StandardButton.Yes:
                return
        self.worker.post("home")

    def begin_drag(self):
        snapshot = self.worker.snapshot()
        if not snapshot.armed or not snapshot.idle or snapshot.state != "ready" or self.shutting_down:
            return
        self.dragging = True
        self.input_error = ""
        self.hold_requested_at = time.monotonic()
        self.worker.post("begin")
        if self.continuous.isChecked() and not self.capture.start(self.pad):
            self.capture_failed("Could not capture the mouse. Uncheck continuous capture to use pad mode.")
        self.pad.update()

    def input_delta(self, dx, dy, wheel):
        if self.dragging:
            self.worker.post("input", dx, dy, wheel)

    def end_drag(self):
        was_dragging = self.dragging
        self.dragging = False
        self.capture.stop()
        if was_dragging:
            self.worker.post("stop")
        if hasattr(self, "pad"):
            self.pad.update()

    def stop_motion(self):
        self.end_drag()
        self.worker.post("stop")

    def capture_failed(self, message):
        self.end_drag()
        self.input_error = message
        self.log.appendPlainText("INPUT " + message)
        self.status.setText(message)

    def eventFilter(self, watched, event):
        if event.type() == QEvent.Type.KeyPress and event.key() == Qt.Key.Key_Escape:
            self.stop_motion()
            return True
        if event.type() == QEvent.Type.ApplicationDeactivate or (
                watched is self and event.type() == QEvent.Type.WindowDeactivate):
            self.end_drag()
        return super().eventFilter(watched, event)

    def refresh(self):
        self.worker.heartbeat()
        self.capture.check_button()
        snapshot = self.worker.snapshot()
        if snapshot.state in ("fault", "closed", "closing"):
            self.end_drag()
        if self.dragging and not snapshot.held and time.monotonic() - self.hold_requested_at > 0.15:
            self.end_drag()
        idle_ready = snapshot.state == "ready" and snapshot.idle and not self.dragging
        disconnected = snapshot.state in ("disconnected", "closed")
        self.connect_button.setText("Connect" if disconnected else "Disconnect")
        self.connect_button.setEnabled(not self.shutting_down and snapshot.state not in ("closing", "fault", "connecting", "homing"))
        for control in (self.mode, self.port, self.baud, self.refresh_button):
            control.setEnabled(disconnected and not self.shutting_down)
        self.home_button.setEnabled(idle_ready and not self.shutting_down)
        self.homed.setEnabled(idle_ready and not snapshot.armed)
        self.arm_button.setEnabled(idle_ready and self.homed.isChecked() and not snapshot.armed)
        for control in (self.xy, self.z, self.speed):
            control.setEnabled(not self.dragging and not self.shutting_down)
        self.continuous.setEnabled(self.capture.available and not self.dragging)
        self.status.setText(snapshot.message if snapshot.state == "fault" else self.input_error or snapshot.message)
        p, t = snapshot.position, snapshot.target
        self.coordinates.setText(f"Acknowledged  X {p.x:8.3f}  Y {p.y:8.3f}  Z {p.z:8.3f}\n"
                                 f"Target        X {t.x:8.3f}  Y {t.y:8.3f}  Z {t.z:8.3f}")
        self.metrics.setText(f"Remaining {snapshot.remaining_mm:.2f} mm  |  Queue {snapshot.pending}/2\n"
                             f"Motion + braking estimate: {snapshot.committed_seconds * 1000:.0f} ms")
        for line in self.worker.take_logs():
            self.log.appendPlainText(line)
        if self.shutting_down and not self.worker.alive:
            self.close()

    def closeEvent(self, event):
        self.end_drag()
        if not self.shutting_down:
            self.shutting_down = True
            for key, value in (("port", self.port.currentText()), ("baud", self.baud.currentText()),
                               ("xy", self.xy.value()), ("z", self.z.value()), ("speed", self.speed.value()),
                               ("continuous", self.continuous.isChecked())):
                self.settings.setValue(key, value)
            self.worker.post("quit")
        if self.worker.alive:
            event.ignore()
            return
        self.timer.stop()
        QApplication.instance().removeEventFilter(self)
        event.accept()
