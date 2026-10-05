"""Transport seam: supply your own send/read_lines/close adapter to integrate."""

from collections import deque
from dataclasses import replace
import math
import time
from typing import Protocol

from .geometry import Vec3
from .planner import Limits, MotionError, duration
from .protocol import LineBuffer, command_bytes


class Transport(Protocol):
    def send(self, command: str) -> None:
        """Send exactly one command in order, or raise; never silently drop it."""

    def read_lines(self, now: float) -> list[str]:
        """Return available complete lines without blocking, in receive order."""

    def close(self) -> None:
        """Release the transport. This does not cancel robot motion."""


class SerialTransport:
    def __init__(self, port: str, baudrate: int = 115200):
        import serial
        if not port.strip() or type(baudrate) is not int or baudrate <= 0:
            raise ValueError("A serial port and a positive integer baudrate are required")
        self.serial = serial.Serial(port=port, baudrate=baudrate, timeout=0, write_timeout=0.1,
                                    bytesize=8, parity="N", stopbits=1, xonxoff=False,
                                    rtscts=False, dsrdtr=False)
        self.buffer = LineBuffer()

    def send(self, command):
        data = command_bytes(command)
        if self.serial.write(data) != len(data):
            raise OSError("Partial serial write; controller queue is uncertain")

    def read_lines(self, now):
        if not self.serial.is_open:
            raise OSError("Serial connection is closed")
        return self.buffer.feed(self.serial.read(min(16384, self.serial.in_waiting)))

    def close(self):
        self.serial.close()


class SimulatedTransport:
    """Timed FIFO protocol emulator. It does not model physical robot dynamics."""

    def __init__(self, clock=time.monotonic, position=Vec3(0, 0, -300), ack_delay=0.002):
        self.clock = clock
        self.position = self.tail = position
        self.ack_delay = ack_delay
        self.events = deque()
        self.log = deque(maxlen=10000)
        self.closed = False
        self.max_depth = 0

    def send(self, command):
        command_bytes(command)
        if self.closed:
            raise OSError("Simulator is closed")
        now = self.clock()
        self.log.append(command)
        endpoint = None
        seconds = self.ack_delay
        if command == "IsDelta":
            reply = "YesDelta"
        elif command == "ROBOTMODEL":
            reply = "MODEL:DELTA_X_3"
        elif command in ("G90", "M205 S0"):
            reply = "Ok"
        elif command == "G28":
            endpoint = self.tail = Vec3(0, 0, -300)
            seconds = 0.5
            reply = "Ok"
        elif command == "PositionOffset":
            reply = f"{self.position.x},{self.position.y},{self.position.z}"
        elif command.startswith("G01 "):
            values = {token[0]: float(token[1:]) for token in command.split()[1:]}
            endpoint = Vec3(values["X"], values["Y"], values["Z"])
            limits = replace(Limits(), speed=int(values["F"]), acceleration=int(values["A"]), jerk=int(values["J"]))
            seconds += duration((endpoint - self.tail).length(), int(values["S"]), int(values["E"]), limits)
            if not math.isfinite(seconds):
                raise MotionError("Simulator received an infeasible profile")
            self.tail = endpoint
            reply = "Ok"
        else:
            reply = "Unknown:" + command
        due = max(now, self.events[-1][0] if self.events else now) + seconds
        self.events.append((due, reply, endpoint))
        self.max_depth = max(self.max_depth, len(self.events))

    def read_lines(self, now):
        if self.closed:
            raise OSError("Simulator is closed")
        lines = []
        while self.events and self.events[0][0] <= now:
            _, reply, endpoint = self.events.popleft()
            if endpoint is not None:
                self.position = endpoint
            lines.append(reply)
        return lines

    def close(self):
        self.closed = True
