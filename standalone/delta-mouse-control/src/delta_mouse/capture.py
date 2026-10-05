"""Windows foreground Raw Input; pad mode is available on other platforms.

The caller owns this object for at least as long as the native event filter is
installed. Raw counts and raw wheel packets are authoritative while active.
"""

import ctypes
from ctypes import wintypes as w
import sys

from PySide6.QtCore import QAbstractNativeEventFilter, Qt
from PySide6.QtWidgets import QApplication, QWidget


class _Device(ctypes.Structure):
    _fields_ = [("page", w.WORD), ("usage", w.WORD), ("flags", w.DWORD), ("target", w.HWND)]


class _Header(ctypes.Structure):
    _fields_ = [("kind", w.DWORD), ("size", w.DWORD), ("device", w.HANDLE), ("wparam", ctypes.c_size_t)]


class _Buttons(ctypes.Structure):
    _fields_ = [("flags", w.WORD), ("data", w.WORD)]


class _ButtonUnion(ctypes.Union):
    _fields_ = [("packed", w.ULONG), ("parts", _Buttons)]


class _Mouse(ctypes.Structure):
    _fields_ = [("flags", w.WORD), ("buttons", _ButtonUnion), ("raw_buttons", w.ULONG),
                ("x", w.LONG), ("y", w.LONG), ("extra", w.ULONG)]


class _Input(ctypes.Structure):
    _fields_ = [("header", _Header), ("mouse", _Mouse)]


class RelativeCapture(QAbstractNativeEventFilter):
    def __init__(self, moved, released, failed):
        super().__init__()
        self.moved, self.released, self.failed = moved, released, failed
        self.active = False
        self.pad = None
        self._registered = self._clipped = False
        self._previous = None
        self.available = sys.platform == "win32" and QApplication.platformName() == "windows"
        if not self.available:
            return
        self.api = ctypes.WinDLL("user32", use_last_error=True)
        signatures = {
            "GetForegroundWindow": ([], w.HWND),
            "GetAsyncKeyState": ([ctypes.c_int], ctypes.c_short),
            "GetCursorPos": ([ctypes.POINTER(w.POINT)], w.BOOL),
            "GetClipCursor": ([ctypes.POINTER(w.RECT)], w.BOOL),
            "ClipCursor": ([ctypes.POINTER(w.RECT)], w.BOOL),
            "RegisterRawInputDevices": ([ctypes.POINTER(_Device), w.UINT, w.UINT], w.BOOL),
            "GetRegisteredRawInputDevices": ([ctypes.POINTER(_Device), ctypes.POINTER(w.UINT), w.UINT], w.UINT),
            "GetRawInputData": ([w.HANDLE, w.UINT, ctypes.c_void_p, ctypes.POINTER(w.UINT), w.UINT], w.UINT),
        }
        for name, (arguments, result) in signatures.items():
            function = getattr(self.api, name)
            function.argtypes, function.restype = arguments, result

    def start(self, pad):
        self.stop()
        if not self.available or not pad.isVisible():
            return False
        self.window = int(pad.window().winId())
        if self.api.GetForegroundWindow() != self.window:
            return False
        count = w.UINT(0)
        if self.api.GetRegisteredRawInputDevices(None, ctypes.byref(count), ctypes.sizeof(_Device)) == 0xFFFFFFFF:
            return False
        devices = (_Device * count.value)()
        if count.value and self.api.GetRegisteredRawInputDevices(devices, ctypes.byref(count), ctypes.sizeof(_Device)) == 0xFFFFFFFF:
            return False
        self._previous = None
        for device in devices:
            if device.page == 1 and device.usage == 2:
                self._previous = _Device(device.page, device.usage, device.flags, device.target)
        self._previous_clip = w.RECT()
        cursor = w.POINT()
        if not self.api.GetClipCursor(ctypes.byref(self._previous_clip)) or not self.api.GetCursorPos(ctypes.byref(cursor)):
            return False
        device = _Device(1, 2, 0, self.window)
        if not self.api.RegisterRawInputDevices(ctypes.byref(device), 1, ctypes.sizeof(device)):
            return False
        self._registered = True
        self.pad = pad
        self._clip = w.RECT(cursor.x, cursor.y, cursor.x + 1, cursor.y + 1)
        if not self.api.ClipCursor(ctypes.byref(self._clip)):
            self.stop()
            return False
        self._clipped = self.active = True
        QApplication.instance().installNativeEventFilter(self)
        pad.grabMouse(Qt.CursorShape.BlankCursor)
        if QWidget.mouseGrabber() != pad:
            self.stop()
            return False
        return True

    def stop(self):
        self.active = False
        app = QApplication.instance()
        if app:
            app.removeNativeEventFilter(self)
        if self._registered:
            device = self._previous or _Device(1, 2, 1, None)  # RIDEV_REMOVE
            self.api.RegisterRawInputDevices(ctypes.byref(device), 1, ctypes.sizeof(device))
            self._registered = False
        if self._clipped:
            current = w.RECT()
            if self.api.GetClipCursor(ctypes.byref(current)) and bytes(current) == bytes(self._clip):
                if not self.api.ClipCursor(ctypes.byref(self._previous_clip)):
                    self.api.ClipCursor(None)
            self._clipped = False
        if self.pad and QWidget.mouseGrabber() == self.pad:
            self.pad.releaseMouse()
        self.pad = None

    def check_button(self):
        if self.active and (self.api.GetForegroundWindow() != self.window
                            or not self.api.GetAsyncKeyState(1) & 0x8000):
            self.stop()
            self.released()

    def nativeEventFilter(self, event_type, message):
        if not self.active:
            return False, 0
        msg = w.MSG.from_address(int(message))
        if msg.message != 0x00FF or msg.hWnd != self.window:  # WM_INPUT
            return False, 0
        try:
            self.check_button()
            if not self.active:
                return False, 0
            packet = _Input()
            size = w.UINT(ctypes.sizeof(packet))
            read = self.api.GetRawInputData(msg.lParam, 0x10000003, ctypes.byref(packet),
                                           ctypes.byref(size), ctypes.sizeof(_Header))
            if read == 0xFFFFFFFF or read < ctypes.sizeof(packet) or packet.header.kind != 0:
                return False, 0
            mouse = packet.mouse
            if mouse.buttons.parts.flags & 0x0002:
                self.stop()
                self.released()
            elif mouse.flags & 0x0001:
                self.stop()
                self.failed("Absolute pointer detected. Turn off continuous capture for pad mode.")
            else:
                wheel = ctypes.c_short(mouse.buttons.parts.data).value / 120 if mouse.buttons.parts.flags & 0x0400 else 0
                if mouse.x or mouse.y or wheel:
                    self.moved(mouse.x, mouse.y, wheel)
        except Exception as exc:
            self.stop()
            self.failed(f"Mouse capture failed: {exc}")
        # Keep DefWindowProc/Qt raw-input cleanup and legacy button processing.
        return False, 0
