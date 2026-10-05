"""Bounded, acknowledgement-driven live or ordered motion stream."""

from collections import deque
from dataclasses import replace

from .geometry import Vec3
from .planner import Limits, MotionError, State, brake, follow, plan
from .tracker import TargetTracker


class MotionStream:
    def __init__(self, position, now, send, limits=Limits()):
        limits.validate()
        self.limits = limits
        self.send = send
        self.completed = State(position)
        self.target = position
        self.inflight = deque()
        self.path = deque()
        self.tracker = TargetTracker(position, now)
        self.head_started = now
        self.overhead = 0.002
        self.following = self.stopping = self.path_mode = self.drain_after_delay = False

    @property
    def idle(self):
        return not self.inflight and not self.following

    @property
    def boundary(self):
        return self.inflight[-1].end_state() if self.inflight else self.completed

    def set_target(self, target, now):
        if not target.valid():
            raise MotionError("Mouse target is out of range")
        if not self.following or self.stopping or self.path_mode:
            self.tracker.reset(target, now)
        else:
            self.tracker.observe(target, now)
        self.target = target
        self.path.clear()
        self.path_mode = self.stopping = False
        self.following = True

    def set_path(self, points, now):
        if not self.idle:
            raise MotionError("An ordered path can only start while idle")
        moves = plan(self.completed, points, self.limits)
        self.path = deque(moves)
        self.tracker.reset(self.completed.position, now)
        self.path_mode = self.following = bool(moves)
        self.stopping = False
        if points:
            self.target = points[-1]

    def set_speed(self, speed):
        if type(speed) is not int or not 10 <= speed <= 150:
            raise MotionError("Mouse speed must be an integer from 10 to 150 mm/s")
        if self.path_mode and not self.idle:
            raise MotionError("Wait for the ordered path before changing speed")
        self.limits = replace(self.limits, speed=speed)

    def remaining_seconds(self, now):
        seconds = sum(m.seconds + self.overhead for m in self.inflight)
        if self.inflight:
            seconds -= min(max(0, now - self.head_started), self.inflight[0].seconds)
        return max(0, seconds)

    def committed_seconds(self, now):
        state = self.boundary
        return self.remaining_seconds(now) + (brake(state, self.limits).seconds if state.speed else 0)

    def _next_plan(self, now, limits):
        state = self.boundary
        if self.stopping:
            return [brake(state, limits)] if state.speed else []
        if self.path_mode:
            return list(self.path)
        return follow(state, self.target, self.tracker.velocity(now, limits.speed),
                      self.remaining_seconds(now), limits)

    def pump(self, now):
        if self.inflight and now - self.head_started > self.inflight[0].seconds + 3:
            raise MotionError("Motion acknowledgement timed out; controller queue is uncertain")
        dispatched = 0
        while (self.following and len(self.inflight) < 2 and dispatched < 2
               and not (self.drain_after_delay and self.inflight)):
            if not self.path_mode and not self.stopping and self.inflight:
                refill_lead = min(0.050, max(0.025, 0.020 + self.overhead))
                if (self.remaining_seconds(now) > refill_lead
                        or now - self.head_started >= self.inflight[0].seconds + self.overhead):
                    break
            limits = self.limits if self.path_mode else replace(self.limits, segment_length=8.0)
            planned = self._next_plan(now, limits)
            if not planned:
                self.following = (not self.stopping and not self.path_mode
                                  and self.tracker.velocity(now, limits.speed).length() > 0)
                break
            move = planned[0]

            def committed_time():
                tail = brake(move.end_state(), limits).seconds if move.exit else 0
                return self.remaining_seconds(now) + move.seconds + self.overhead + tail

            while (not self.path_mode and not self.stopping
                   and committed_time() > limits.queued_seconds
                   and limits.segment_length > 2 * limits.minimum_length):
                limits = replace(limits, segment_length=max(2 * limits.minimum_length, limits.segment_length * 0.8))
                planned = self._next_plan(now, limits)
                if not planned:
                    break
                move = planned[0]
            if not planned:
                break
            if committed_time() > self.limits.queued_seconds and self.inflight:
                break
            if self.path_mode:
                self.path.popleft()
            if not self.inflight:
                self.head_started = now
            self.inflight.append(move)
            dispatched += 1
            self.send(move.gcode())

    def acknowledge(self, now):
        if not self.inflight:
            raise MotionError("Unexpected Ok; another client or a stale command may be present")
        total = sum(m.seconds + self.overhead for m in self.inflight)
        if len(self.inflight) > 1 and now - self.head_started > total + 0.02:
            self.drain_after_delay = True
        completed = self.inflight.popleft()
        excess = min(0.1, max(0, now - self.head_started - completed.seconds))
        self.overhead = 0.8 * self.overhead + 0.2 * excess
        self.completed = completed.end_state()
        self.head_started = now
        if not self.inflight:
            self.drain_after_delay = False
            if self.completed.speed:
                self.completed = replace(self.completed, speed=0)
                if self.path_mode and self.path:
                    self.path = deque(plan(self.completed, [m.end for m in self.path], self.limits))

    def stop(self, now):
        self.path.clear()
        self.path_mode = False
        self.stopping = self.following = True
        state = self.boundary
        self.target = brake(state, self.limits).end if state.speed else state.position
        self.tracker.reset(self.target, now)
