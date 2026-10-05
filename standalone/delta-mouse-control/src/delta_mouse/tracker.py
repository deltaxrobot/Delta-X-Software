"""Estimate intent velocity without dropping accumulated mouse displacement."""

from collections import deque

from .geometry import Vec3


class TargetTracker:
    def __init__(self, position, now):
        self.reset(position, now)

    def reset(self, position, now):
        self.samples = deque([(position, now)])
        self.estimate = Vec3()

    def observe(self, position, now):
        last, when = self.samples[-1]
        delta = position - last
        if now < when or now - when > 0.1 or delta.dot(self.estimate) < 0:
            self.reset(position, now)
            return
        if not delta.length():
            return
        if now == when:
            self.samples[-1] = (position, now)
        else:
            self.samples.append((position, now))
        while len(self.samples) > 2 and now - self.samples[1][1] >= 0.04:
            self.samples.popleft()
        age = now - self.samples[0][1]
        if age >= 0.008:
            self.estimate = (position - self.samples[0][0]) * (1 / age)

    def velocity(self, now, speed_limit):
        age = now - self.samples[-1][1]
        length = self.estimate.length()
        if len(self.samples) < 2 or age < 0 or age >= 0.08 or length < 0.001:
            return Vec3()
        decay = 1 if age <= 0.04 else (0.08 - age) / 0.04
        return self.estimate * (decay * min(1, speed_limit / length))
