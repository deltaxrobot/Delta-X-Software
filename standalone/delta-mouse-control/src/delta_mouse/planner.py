"""Port of GcodeMotionPlanner.cpp. No hardware, threads or GUI objects.

F/S/E are mm/s; A is mm/s^2; J is mm/s^3. E is EXIT SPEED, not extrusion.
Timing and corner limits approximate the firmware; they are not feedback.
"""

from dataclasses import dataclass, replace
import math

from .geometry import Vec3


class MotionError(ValueError):
    pass


@dataclass(frozen=True)
class Limits:
    speed: int = 100
    acceleration: int = 1500
    jerk: int = 15000
    segment_length: float = 2.0
    minimum_length: float = 0.201
    junction_deviation: float = 0.05
    queued_seconds: float = 0.25

    def validate(self):
        for name, low, high in (("speed", 3, 20000), ("acceleration", 1, 50000),
                                ("jerk", 1, 10000000)):
            value = getattr(self, name)
            if type(value) is not int or not low <= value <= high:
                raise MotionError(f"Invalid {name}: {value}")
        if (not all(math.isfinite(v) for v in (self.segment_length, self.minimum_length,
                                             self.junction_deviation, self.queued_seconds))
                or self.minimum_length < 0.201
                or self.segment_length < 2 * self.minimum_length
                or self.junction_deviation < 0 or self.queued_seconds <= 0):
            raise MotionError("Invalid motion limits")


@dataclass(frozen=True)
class State:
    position: Vec3
    direction: Vec3 = Vec3()
    speed: int = 0


@dataclass(frozen=True)
class Segment:
    start: Vec3
    end: Vec3
    feed: int
    acceleration: int
    jerk: int
    entry: int
    exit: int
    seconds: float

    def gcode(self):
        return (f"G01 X{self.end.x:.3f} Y{self.end.y:.3f} Z{self.end.z:.3f} "
                f"F{self.feed} A{self.acceleration} J{self.jerk} S{self.entry} E{self.exit}")

    def end_state(self):
        return State(self.end, (self.end - self.start).normalized(), self.exit)


def transition_time(start, end, limits):
    dv = abs(end - start)
    a, j = limits.acceleration, limits.jerk
    return 2 * math.sqrt(dv / j) if dv <= a * a / j else dv / a + a / j


def transition_distance(start, end, limits):
    return (start + end) * 0.5 * transition_time(start, end, limits)


def duration(distance, entry, exit_speed, limits):
    low, high = max(entry, exit_speed), limits.speed

    def ramp(peak):
        return (transition_distance(entry, peak, limits)
                + transition_distance(peak, exit_speed, limits))

    if ramp(low) > distance + 0.0001:
        return math.inf
    for _ in range(40):
        mid = (low + high) / 2
        if ramp(mid) <= distance:
            low = mid
        else:
            high = mid
    return (transition_time(entry, low, limits) + transition_time(low, exit_speed, limits)
            + max(0, distance - ramp(low)) / low)


def _reachable(start, distance, limits):
    low, high = start, limits.speed - 2
    while low < high:
        mid = (low + high + 1) // 2
        if transition_distance(start, mid, limits) <= distance:
            low = mid
        else:
            high = mid - 1
    return low


def _junction(a, b, limits):
    dot = min(1, max(-1, a.dot(b)))
    if dot > 0.999999:
        return limits.speed - 2
    if dot <= 0:
        return 0
    cosine = math.sqrt((1 + dot) / 2)
    radius = limits.junction_deviation * cosine / (1 - cosine)
    speed = min(math.sqrt(limits.acceleration * radius), (limits.jerk * radius**2)**(1 / 3))
    return min(limits.speed - 2, math.floor(speed))


def _segment(a, b, entry, exit_speed, limits):
    result = Segment(a, b, limits.speed, limits.acceleration, limits.jerk, entry, exit_speed,
                     duration((b - a).length(), entry, exit_speed, limits))
    if not math.isfinite(result.seconds) or len(result.gcode()) > 79 or not b.valid():
        raise MotionError("Motion cannot be represented by the controller protocol")
    return result


def _validate_state(start, maximum):
    if (not start.position.valid() or type(start.speed) is not int
            or not 0 <= start.speed <= maximum
            or (start.speed and (not start.direction.valid() or start.direction.length() < 0.9))):
        raise MotionError("Invalid initial motion state")


def plan(start: State, path: list[Vec3], limits: Limits = Limits()) -> list[Segment]:
    limits.validate()
    _validate_state(start, limits.speed - 2)
    if len(path) > 4096:
        raise MotionError("Look-ahead exceeds 4096 points")
    points = [start.position.rounded()]
    for point in path:
        if not point.valid():
            raise MotionError("Invalid path coordinate")
        point = point.rounded()
        if point == points[-1]:
            continue
        while len(points) >= 2:
            a, b = points[-1] - points[-2], point - points[-1]
            if a.dot(b) <= 0:
                break
            line = point - points[-2]
            if (a - line * (a.dot(line) / line.dot(line))).length() > 0.0005:
                break
            points.pop()
        points.append(point)
    nodes = [points[0]]
    for a, b in zip(points, points[1:]):
        delta = b - a
        if delta.length() < limits.minimum_length:
            raise MotionError("Path detail is below the firmware minimum move length")
        count = math.ceil(delta.length() / limits.segment_length)
        if len(nodes) + count > 4096:
            raise MotionError("Look-ahead exceeds 4096 segments")
        nodes.extend((a + delta * (n / count)).rounded() for n in range(1, count + 1))
    count = len(nodes) - 1
    if not count:
        return []
    deltas = [b - a for a, b in zip(nodes, nodes[1:])]
    distances = [d.length() for d in deltas]
    if any(d < 0.2 for d in distances):
        raise MotionError("Rounded segment is below the firmware minimum move length")
    directions = [d.normalized() for d in deltas]
    speeds = [start.speed] + [_junction(a, b, limits) for a, b in zip(directions, directions[1:])] + [0]
    if start.speed and _junction(start.direction.normalized(), directions[0], limits) < start.speed:
        raise MotionError("Committed velocity requires braking before changing direction")
    for i in range(count - 1, -1, -1):
        maximum = _reachable(speeds[i + 1], distances[i], limits)
        if i == 0 and speeds[0] > maximum:
            raise MotionError("Committed velocity requires more braking distance")
        speeds[i] = min(speeds[i], maximum)
    for i in range(count):
        speeds[i + 1] = min(speeds[i + 1], _reachable(speeds[i], distances[i], limits))
    return [_segment(nodes[i], nodes[i + 1], speeds[i], speeds[i + 1], limits) for i in range(count)]


def brake(start: State, limits: Limits = Limits()) -> Segment:
    limits.validate()
    _validate_state(start, 19998)
    if not start.speed:
        raise MotionError("A stationary state does not need a braking segment")
    profile = replace(limits, speed=max(3, start.speed + 2))
    distance = max(profile.minimum_length, transition_distance(start.speed, 0, profile) + 0.002)
    end = (start.position + start.direction.normalized() * distance).rounded()
    return _segment(start.position, end, start.speed, 0, profile)


def follow(start: State, target: Vec3, velocity: Vec3, queued_seconds: float,
           limits: Limits = Limits()) -> list[Segment]:
    limits.validate()
    _validate_state(start, 19998)
    if not target.valid() or not velocity.valid() or not math.isfinite(queued_seconds) or queued_seconds < 0:
        raise MotionError("Invalid live target or timing")
    input_speed = min(limits.speed, velocity.length())
    offset = target - start.position
    prediction = (velocity.normalized() * min(3, input_speed * min(0.08, queued_seconds + 0.06))
                  if input_speed >= 10 else Vec3())
    if not (target + prediction).valid():
        raise MotionError("Predicted target is out of range")
    delta = target + prediction - start.position
    if delta.length() < limits.minimum_length:
        return [brake(start, limits)] if start.speed else []
    feed = min(limits.speed, max(3, start.speed + 2, math.ceil(input_speed + offset.length() / 0.12)))
    length = min(limits.segment_length, max(2 * limits.minimum_length, feed * 0.06))
    if input_speed > 1:
        length = min(length, max(2 * limits.minimum_length, delta.length() * 0.5))
    live = replace(limits, speed=feed, segment_length=length)
    destination = start.position + delta.normalized() * min(20, delta.length())
    try:
        return plan(start, [destination], live)
    except MotionError:
        if not start.speed:
            raise
        end = destination.rounded()
        displacement = end - start.position.rounded()
        if (live.speed >= start.speed + 2
                and displacement.length() <= transition_distance(start.speed, 0, live) + 2 * limits.minimum_length
                and _junction(start.direction.normalized(), displacement.normalized(), live) >= start.speed):
            try:
                return [_segment(start.position.rounded(), end, start.speed, 0, live)]
            except MotionError:
                pass
        return [brake(start, limits)]
