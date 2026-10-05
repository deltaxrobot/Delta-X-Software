"""Single-owner robot lifecycle. Drive tick() every ~8 ms from ONE thread."""

from dataclasses import dataclass
import math
import time

from .geometry import Vec3
from .planner import Limits, MotionError
from .protocol import is_error, is_telemetry, position_response
from .stream import MotionStream
from .transport import Transport


@dataclass(frozen=True)
class MouseSettings:
    xy_mm_per_count: float = 0.15
    z_mm_per_notch: float = 1.0

    def validate(self):
        if (not math.isfinite(self.xy_mm_per_count) or not 0.01 <= self.xy_mm_per_count <= 1
                or not math.isfinite(self.z_mm_per_notch) or not 0.25 <= self.z_mm_per_notch <= 2):
            raise ValueError("Mouse sensitivity: XY 0.01-1 mm/count, Z 0.25-2 mm/notch")


@dataclass(frozen=True)
class Snapshot:
    state: str = "disconnected"
    message: str = "Choose Simulator or a serial port, then connect."
    position: Vec3 = Vec3()
    target: Vec3 = Vec3()
    remaining_mm: float = 0
    pending: int = 0
    committed_seconds: float = 0
    armed: bool = False
    held: bool = False
    idle: bool = True


class RobotSession:
    """Owns the connection exclusively. A faulted session cannot be reused.

    Construct/open/start/tick/close on one owner thread. Use ControllerWorker
    when UI and communication run on different threads. Closing is asynchronous:
    keep ticking until state == 'closed' (or 'fault').
    """

    def __init__(self, transport: Transport, *, clock=time.monotonic, limits=Limits(),
                 mouse=MouseSettings(), log=None):
        limits.validate()
        mouse.validate()
        self.transport, self.clock, self.limits, self.mouse = transport, clock, limits, mouse
        self.log = log or (lambda direction, line: None)
        self.state, self.message = "new", "Not started"
        self.stream = None
        self.armed = self.held = self.closing = False
        self.request = None
        self.deadline = 0.0
        self.mouse_target = Vec3()
        self._closed_transport = False
        self._home_requested = False

    def start(self):
        if self.state != "new":
            raise MotionError("Create a new session for each connection")
        self.state = "connecting"
        self.message = "Identifying Delta X 3..."
        self._request("IsDelta")

    def _send(self, command):
        self.log("TX", command)
        try:
            self.transport.send(command)
        except Exception as exc:
            self.fail(f"Transport write failed: {exc}")
            raise MotionError(self.message) from exc

    def _request(self, command, timeout=3.0):
        self.request = command
        self.deadline = self.clock() + timeout
        self._send(command)

    def tick(self):
        if self.state in ("new", "closed", "fault"):
            return
        now = self.clock()
        try:
            # Process the complete receive batch BEFORE issuing another command.
            # A late second Ok cannot acknowledge a command sent mid-batch.
            lines = self.transport.read_lines(now)
            next_request = None
            for line in lines:
                self.log("RX", line)
                if is_error(line):
                    raise MotionError(f"Controller stopped or rejected a command: {line}")
                if is_telemetry(line):
                    continue
                if self.request:
                    next_request = self._response(line, now)
                elif line.strip().lower() == "ok":
                    if self.stream is None:
                        raise MotionError("Unexpected acknowledgement during startup")
                    self.stream.acknowledge(now)
                # Other unsolicited telemetry never consumes a motion acknowledgement.
            if next_request:
                self._request(*next_request)
            if self.request and now >= self.deadline:
                raise MotionError(f"Timeout waiting for {self.request}; controller queue is uncertain")
            if self.stream and not self.request and self.state not in ("fault", "closed"):
                self.stream.pump(now)
                if self.closing and self.stream.idle:
                    self._request("M205 S0")
        except Exception as exc:
            self.fail(str(exc))

    def _response(self, line, now):
        request = self.request
        expected = {"IsDelta": "yesdelta", "ROBOTMODEL": "model:delta_x_3",
                    "G90": "ok", "M205 S0": "ok", "G28": "ok"}
        if request == "PositionOffset":
            position = position_response(line)
            self.stream = MotionStream(position, now, self._send, self.limits)
            self.mouse_target = position
            self.armed = self._home_requested
            self._home_requested = False
            self.state = "ready"
            self.message = "Ready. Hold the pad to move." if self.armed else "Position read. Home, or confirm the robot is already homed."
        elif line.strip().lower() != expected[request]:
            raise MotionError(f"Expected {expected[request]!r} for {request}, received {line!r}")
        self.request = None
        if request == "IsDelta":
            return ("ROBOTMODEL",)
        if request == "ROBOTMODEL":
            return ("G90",)
        if request == "G90":
            return ("M205 S0",)
        if request == "M205 S0":
            if self.closing:
                self._finish_close()
            else:
                return ("PositionOffset",)
        if request == "G28":
            return ("PositionOffset",)
        return None

    def _require_idle(self):
        if self.state != "ready" or not self.stream or not self.stream.idle or self.held or self.closing:
            raise MotionError("Wait for a ready, idle robot")

    def arm(self, *, confirmed_homed=False):
        self._require_idle()
        if not confirmed_homed:
            raise MotionError("Confirm an established physical home before enabling motion")
        self.armed = True
        self.message = "Ready. Hold the pad to move."

    def home(self):
        self._require_idle()
        self.armed = False
        self._home_requested = True
        self.state, self.message = "homing", "Homing; waiting for completion and position..."
        self._request("G28", 60.0)

    def begin_hold(self):
        self._require_idle()
        if not self.armed:
            raise MotionError("Home or confirm the existing home first")
        self.mouse_target = self.stream.completed.position
        self.held = True
        self.message = "Following: right +X, up +Y, wheel up +Z."

    def add_mouse_delta(self, dx=0.0, dy=0.0, wheel_notches=0.0):
        if not self.held or self.closing or self.state != "ready":
            return
        if not all(math.isfinite(v) for v in (dx, dy, wheel_notches)):
            self.fail("Non-finite mouse input")
            return
        delta = Vec3(dx * self.mouse.xy_mm_per_count, -dy * self.mouse.xy_mm_per_count,
                     wheel_notches * self.mouse.z_mm_per_notch)
        if not delta.length():
            return
        target = self.mouse_target + delta
        try:
            self.stream.set_target(target, self.clock())
        except MotionError as exc:
            self.fail(str(exc))
            return
        self.mouse_target = target

    def set_mouse_settings(self, settings):
        settings.validate()
        if self.held:
            raise MotionError("Release the mouse before changing sensitivity")
        self.mouse = settings

    def set_speed(self, speed):
        if self.stream:
            self.stream.set_speed(speed)
            self.limits = self.stream.limits

    def move_path(self, points):
        self._require_idle()
        if not self.armed:
            raise MotionError("Home or confirm the existing home first")
        self.stream.set_path(points, self.clock())
        self.message = "Running ordered path."

    def stop(self):
        self.held = False
        if self.stream and self.state == "ready" and not self.closing:
            self.stream.stop(self.clock())
            self.message = "Released. Draining committed motion and braking."

    def close(self):
        if self.state in ("closed", "fault"):
            self._close_transport()
            return
        self.held = False
        self.closing = True
        if self.state != "ready":
            self.fail("Closed before the active startup/homing transaction completed; queue state is uncertain")
            return
        self.state, self.message = "closing", "Finishing motion, braking and resetting S/E..."
        self.stream.stop(self.clock())

    def _close_transport(self):
        if not self._closed_transport:
            self._closed_transport = True
            try:
                self.transport.close()
            except Exception as exc:
                self.log("ERROR", f"Close failed: {exc}")

    def _finish_close(self):
        self._close_transport()
        self.state, self.message = "closed", "Disconnected after motion drained and S/E reset."
        self.armed = self.held = False

    def fail(self, reason):
        if self.state == "fault":
            return
        self.state = "fault"
        self.message = reason + ". Establish an empty robot queue and restart this application before reconnecting."
        self.armed = self.held = False
        self._close_transport()

    def snapshot(self):
        stream = self.stream
        return Snapshot(
            state=self.state, message=self.message,
            position=stream.completed.position if stream else Vec3(),
            target=stream.target if stream else Vec3(),
            remaining_mm=(stream.target - stream.completed.position).length() if stream else 0,
            pending=len(stream.inflight) if stream else 0,
            committed_seconds=stream.committed_seconds(self.clock()) if stream else 0,
            armed=self.armed, held=self.held, idle=stream.idle if stream else True,
        )
