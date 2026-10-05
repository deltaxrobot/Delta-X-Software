"""Offscreen UI regressions. No physical robot or actual cursor capture."""

import ctypes
import os
import sys
import time
from types import SimpleNamespace

os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")

import pytest

pytest.importorskip("PySide6")
pytest.importorskip("serial")
from PySide6.QtCore import QEvent, QPoint, QPointF, Qt
from PySide6.QtGui import QWheelEvent
from PySide6.QtWidgets import QApplication

from delta_mouse.window import MainWindow


def wait_for(app, condition, seconds=5):
    deadline = time.monotonic() + seconds
    while not condition():
        assert time.monotonic() < deadline
        app.processEvents()
        time.sleep(0.005)


@pytest.fixture
def window(tmp_path):
    from PySide6.QtCore import QSettings
    app = QApplication.instance() or QApplication([])
    app.setOrganizationName("DeltaMouseTests")
    app.setApplicationName("OffscreenTests")
    QSettings.setDefaultFormat(QSettings.Format.IniFormat)
    QSettings.setPath(QSettings.Format.IniFormat, QSettings.Scope.UserScope, str(tmp_path))
    gui = MainWindow()
    gui.show()
    gui.xy.setValue(0.15)
    gui.z.setValue(1)
    gui.speed.setValue(100)
    gui.continuous.setChecked(False)
    gui.connect_robot()
    wait_for(app, lambda: gui.worker.snapshot().state == "ready")
    gui.worker.post("arm")
    wait_for(app, lambda: gui.worker.snapshot().armed)
    yield app, gui
    gui.close()
    wait_for(app, lambda: not gui.worker.alive)
    app.processEvents()


def wheel(widget, delta=120):
    event = QWheelEvent(QPointF(20, 20), QPointF(20, 20), QPoint(), QPoint(0, delta),
                        Qt.MouseButton.LeftButton, Qt.KeyboardModifier.NoModifier,
                        Qt.ScrollPhase.NoScrollPhase, False)
    QApplication.sendEvent(widget, event)


def test_gui_wheel_requires_hold_and_updates_only_z(window):
    app, gui = window
    initial = gui.worker.snapshot().position
    wheel(gui.pad)
    app.processEvents()
    assert gui.worker.snapshot().target == initial
    gui.begin_drag()
    wait_for(app, lambda: gui.worker.snapshot().held)
    for _ in range(4):
        wheel(gui.pad, 30)
    wait_for(app, lambda: abs(gui.worker.snapshot().position.z - initial.z - 1) < 0.201)
    result = gui.worker.snapshot()
    assert result.position.x == initial.x
    assert result.position.y == initial.y
    gui.end_drag()
    wait_for(app, lambda: not gui.worker.snapshot().held and gui.worker.snapshot().idle)


def test_escape_releases_and_ui_heartbeat_stops_input(window):
    from PySide6.QtTest import QTest
    app, gui = window
    gui.begin_drag()
    wait_for(app, lambda: gui.worker.snapshot().held)
    gui.input_delta(300, 0, 0)
    QTest.keyClick(gui.pad, Qt.Key.Key_Escape)
    assert not gui.dragging
    wait_for(app, lambda: not gui.worker.snapshot().held and gui.worker.snapshot().idle)
    gui.begin_drag()
    wait_for(app, lambda: gui.worker.snapshot().held)
    gui.input_delta(300, 0, 0)
    gui.timer.stop()
    wait_for(app, lambda: not gui.worker.snapshot().held)
    assert "heartbeat" in gui.worker.snapshot().message
    gui.refresh()
    assert not gui.dragging


def test_focus_loss_releases_mouse(window):
    app, gui = window
    gui.begin_drag()
    wait_for(app, lambda: gui.worker.snapshot().held)
    QApplication.sendEvent(gui, QEvent(QEvent.Type.WindowDeactivate))
    assert not gui.dragging
    wait_for(app, lambda: not gui.worker.snapshot().held)


def test_pad_xy_mapping_and_leaving_stops_input(window):
    from PySide6.QtGui import QMouseEvent
    app, gui = window
    gui.begin_drag()
    gui.pad.last = QPointF(20, 20)
    wait_for(app, lambda: gui.worker.snapshot().held)
    event = QMouseEvent(QEvent.Type.MouseMove, QPointF(40, 10), QPointF(40, 10),
                        Qt.MouseButton.NoButton, Qt.MouseButton.LeftButton, Qt.KeyboardModifier.NoModifier)
    QApplication.sendEvent(gui.pad, event)
    wait_for(app, lambda: abs(gui.worker.snapshot().position.x - 3) < 0.201)
    assert gui.worker.snapshot().target.y == pytest.approx(1.5)
    QApplication.sendEvent(gui.pad, QEvent(QEvent.Type.Leave))
    assert not gui.dragging
    wait_for(app, lambda: not gui.worker.snapshot().held)


def test_close_window_drains_active_motion_before_worker_exits(window):
    app, gui = window
    gui.begin_drag()
    wait_for(app, lambda: gui.worker.snapshot().held)
    gui.input_delta(800, 0, 0)
    wait_for(app, lambda: gui.worker.snapshot().pending > 0)
    gui.close()
    wait_for(app, lambda: not gui.worker.alive)
    assert gui.worker.snapshot().state == "closed"
    assert gui.worker.snapshot().position.x < 30


def test_mapping_help_matches_current_sensitivity_and_mode(window):
    app, gui = window
    gui.xy.setValue(0.3)
    assert "100 mouse pixels requests 30 mm" in gui.mapping_explanation.text()


@pytest.mark.skipif(sys.platform != "win32", reason="Windows RAWINPUT structure ABI")
def test_windows_raw_wheel_signed_and_legacy_wheel_not_double_counted(window):
    from ctypes import wintypes as w
    from delta_mouse.capture import _Header, _Input, _Mouse
    app, gui = window
    assert ctypes.sizeof(_Mouse) == 24
    assert ctypes.sizeof(_Header) == (24 if ctypes.sizeof(ctypes.c_void_p) == 8 else 16)
    assert ctypes.sizeof(_Input) == ctypes.sizeof(_Header) + 24
    events = []
    capture = gui.capture
    capture.moved = lambda *args: events.append(args)
    capture.window = 123
    capture.active = True
    packet = _Input()
    packet.mouse.buttons.parts.flags = 0x0400
    packet.mouse.buttons.parts.data = 65536 - 120
    packet.mouse.x = 10

    def read(handle, code, pointer, size, header):
        ctypes.memmove(pointer, ctypes.byref(packet), ctypes.sizeof(packet))
        return ctypes.sizeof(packet)

    capture.api = SimpleNamespace(GetForegroundWindow=lambda: 123, GetAsyncKeyState=lambda key: 0x8000,
                                  GetRawInputData=read)
    message = w.MSG()
    message.hWnd = 123
    message.message = 0x00FF
    capture.nativeEventFilter(b"windows_generic_MSG", ctypes.addressof(message))
    assert events == [(10, 0, -1)]
    gui.dragging = True
    gui.input_delta = lambda *args: events.append(args)
    wheel(gui.pad, -120)
    assert events == [(10, 0, -1)]
    gui.dragging = False
    capture.active = False
