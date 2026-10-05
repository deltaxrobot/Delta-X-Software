"""Offline geometry-preserving plan; prints G-code, never opens a connection."""

from delta_mouse import Limits, State, Vec3, plan

start = State(Vec3(0, 0, -300))
points = [Vec3(20, 0, -300), Vec3(20, 20, -300), Vec3(0, 20, -300), Vec3(0, 0, -300)]
segments = plan(start, points, Limits(speed=50))
print("G90")
for segment in segments:
    print(segment.gcode())
print("M205 S0")
