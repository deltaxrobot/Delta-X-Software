"""Thread-safe GUI adapter. All session and serial work stays on one thread."""

from collections import deque
from dataclasses import replace
import threading
import time

from .planner import MotionError
from .session import RobotSession, Snapshot
from .transport import SerialTransport, SimulatedTransport


class ControllerWorker:
    def __init__(self):
        self._lock = threading.Lock()
        self._commands = deque()
        self._logs = deque(maxlen=250)
        self._snapshot = Snapshot()
        self._heartbeat = time.monotonic()
        self._quit = False
        self._overflow = False
        self._recovery_required = False
        self._thread = threading.Thread(target=self._run, name="delta-mouse-io", daemon=True)
        self._thread.start()

    def post(self, action, *args):
        with self._lock:
            if action in ("stop", "disconnect", "quit"):
                # Unsent input is cancelled on release, including queued begin events.
                self._commands = deque(c for c in self._commands if c[0] not in ("input", "begin"))
            if action == "input" and self._commands and self._commands[-1][0] == "input":
                old = self._commands.pop()[1]
                args = tuple(a + b for a, b in zip(old, args))
            if len(self._commands) >= 256:
                self._overflow = True
            else:
                self._commands.append((action, args))

    def heartbeat(self):
        with self._lock:
            self._heartbeat = time.monotonic()

    def snapshot(self):
        with self._lock:
            return self._snapshot

    def take_logs(self):
        with self._lock:
            result = list(self._logs)
            self._logs.clear()
        return result

    @property
    def alive(self):
        return self._thread.is_alive()

    def _log(self, direction, line):
        with self._lock:
            self._logs.append(f"{direction:5} {line}")

    def _run(self):
        session = None
        while not self._quit:
            with self._lock:
                commands = list(self._commands)
                self._commands.clear()
                heartbeat = self._heartbeat
                overflow = self._overflow
                self._overflow = False
            if overflow and session:
                session.fail("UI command queue overflow")
            for action, args in commands:
                try:
                    if action == "connect":
                        if self._recovery_required:
                            raise MotionError("Restart after restoring an empty controller queue")
                        if session and session.state not in ("closed", "fault"):
                            raise MotionError("Disconnect the current session first")
                        mode, port, baudrate, mouse, speed = args
                        transport = SimulatedTransport() if mode == "Simulator" else SerialTransport(port, baudrate)
                        from .planner import Limits
                        session = RobotSession(transport, mouse=mouse, limits=replace(Limits(), speed=speed), log=self._log)
                        session.start()
                    elif action == "quit":
                        if session:
                            session.close()
                        self._quit = True
                    elif session:
                        if action == "disconnect":
                            session.close()
                        elif action == "begin":
                            session.begin_hold()
                        elif action == "input":
                            session.add_mouse_delta(*args)
                        elif action == "stop":
                            session.stop()
                        elif action == "home":
                            session.home()
                        elif action == "arm":
                            session.arm(confirmed_homed=True)
                        elif action == "settings":
                            session.set_mouse_settings(args[0])
                            session.set_speed(args[1])
                except Exception as exc:
                    self._log("ERROR", str(exc))
                    if session and session.state != "fault":
                        session.message = str(exc)
                    elif not session:
                        with self._lock:
                            self._snapshot = Snapshot(message=f"Connection failed: {exc}")
            if session:
                if session.held and time.monotonic() - heartbeat > 0.3:
                    session.stop()
                    session.message = "Mouse input stopped because the UI heartbeat expired."
                session.tick()
                if session.state == "fault":
                    self._recovery_required = True
                with self._lock:
                    self._snapshot = session.snapshot()
            time.sleep(0.008)
        # A window close keeps this thread alive until the braking tail completes.
        if session:
            while session.state not in ("closed", "fault"):
                session.tick()
                with self._lock:
                    self._snapshot = session.snapshot()
                time.sleep(0.008)
