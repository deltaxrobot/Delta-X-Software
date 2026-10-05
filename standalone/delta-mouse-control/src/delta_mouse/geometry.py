"""Small immutable vectors, with no NumPy or GUI dependency."""

from dataclasses import dataclass
import math


@dataclass(frozen=True)
class Vec3:
    x: float = 0.0
    y: float = 0.0
    z: float = 0.0

    def __add__(self, other):
        return Vec3(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return Vec3(self.x - other.x, self.y - other.y, self.z - other.z)

    def __mul__(self, scale):
        return Vec3(self.x * scale, self.y * scale, self.z * scale)

    def dot(self, other):
        return self.x * other.x + self.y * other.y + self.z * other.z

    def length(self):
        return math.sqrt(self.dot(self))

    def normalized(self):
        length = self.length()
        return self * (1 / length) if length else Vec3()

    def valid(self):
        return all(math.isfinite(v) and abs(v) <= 100000 for v in (self.x, self.y, self.z))

    def rounded(self):
        def quantize(value):
            return math.copysign(math.floor(abs(value) * 1000 + 0.5) / 1000, value)
        return Vec3(*(quantize(v) for v in (self.x, self.y, self.z)))
