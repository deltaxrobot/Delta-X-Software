"""GUI-independent public integration API. Units: millimetres and seconds."""

from .geometry import Vec3
from .planner import Limits, MotionError, State, brake, follow, plan
from .session import MouseSettings, RobotSession, Snapshot
from .transport import SerialTransport, SimulatedTransport, Transport

__version__ = "1.0.0"
__all__ = [
    "Limits", "MotionError", "MouseSettings", "RobotSession", "SerialTransport",
    "SimulatedTransport", "Snapshot", "State", "Transport", "Vec3", "brake",
    "follow", "plan",
]
