"""Delta X 3 framing and response classification, not generic RepRap G-code."""

import re

from .geometry import Vec3
from .planner import MotionError


def command_bytes(command):
    if not command or len(command) > 79 or any(c in command for c in "\r\n\x00"):
        raise MotionError("Commands must be single ASCII lines of at most 79 characters")
    try:
        return (command + "\n").encode("ascii")
    except UnicodeEncodeError as exc:
        raise MotionError("Non-ASCII command") from exc


def is_error(line):
    text = line.strip().lower()
    return ("error" in text or text.startswith(("unknown:", "delta:estop"))
            or text in ("delta:stop", "delta:pause")
            or text.startswith("init success"))


def is_telemetry(line):
    return bool(re.fullmatch(r"[IA]\d+\s+V[-+]?\d+(?:\.\d+)?", line.strip(), re.IGNORECASE))


def position_response(line):
    parts = line.strip().split(",")
    if not 3 <= len(parts) <= 6:
        raise MotionError(f"Invalid PositionOffset response: {line!r}")
    try:
        values = [float(p) for p in parts]
    except ValueError as exc:
        raise MotionError(f"Invalid PositionOffset response: {line!r}") from exc
    import math
    if not all(math.isfinite(v) and abs(v) <= 100000 for v in values):
        raise MotionError("PositionOffset contains non-finite or out-of-range coordinates")
    return Vec3(*values[:3])


class LineBuffer:
    def __init__(self):
        self.pending = bytearray()

    def feed(self, data):
        self.pending.extend(data)
        lines = []
        while b"\n" in self.pending:
            raw, _, tail = self.pending.partition(b"\n")
            self.pending = bytearray(tail)
            if len(raw) > 512:
                raise MotionError("Controller response exceeded 512 bytes")
            try:
                text = raw.decode("ascii").strip()
            except UnicodeDecodeError as exc:
                raise MotionError("Non-ASCII serial data; verify the baudrate") from exc
            if text:
                lines.append(text)
        if len(self.pending) > 512:
            raise MotionError("Unterminated controller response exceeded 512 bytes")
        return lines
