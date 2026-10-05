# Integration entry point

This is a standalone reference implementation, not a plugin that loads the
Delta X Software executable. Its own version is 1.0.0; its source baseline is
Delta X Software 2.0.0, commit `e692f07`.

## Read in this order

1. `README.md`: installation, operating steps and folder structure.
2. `docs/ARCHITECTURE.md`: component ownership, algorithm and lifecycle.
3. `docs/PROTOCOL.md`: exact wire semantics, especially S/E and completion.
4. `src/delta_mouse/session.py`: the public session and mouse adapter.
5. `examples/headless_mouse.py` and `examples/existing_transport.py`.
6. `tests/`: executable behavioral specifications and failure scenarios.

## Public API

```python
from delta_mouse import RobotSession, SerialTransport, MouseSettings, Limits

# Run all of this on a single worker thread that exclusively owns the robot.
transport = SerialTransport("COM7", baudrate=115200)
session = RobotSession(
    transport,
    mouse=MouseSettings(xy_mm_per_count=0.15, z_mm_per_notch=1.0),
    limits=Limits(speed=100, acceleration=1500, jerk=15000),
    log=lambda direction, text: print(direction, text),
)
session.start()
# Your worker timer calls session.tick() approximately every 8 ms.
# Wait until session.state == "ready" before further operations.
```

The example port is a placeholder, not a detected robot. Do not automatically
execute the following operations at startup. Wire them to operator actions:

| Application event | Session operation |
| --- | --- |
| Operator chooses Home while idle | `session.home()`; wait for `ready` again |
| Operator confirms an existing home | `session.arm(confirmed_homed=True)` |
| LEFT pressed inside control pad | `session.begin_hold()` |
| Relative input | `session.add_mouse_delta(dx, dy, wheel_notches)` |
| Release / Esc / application loses focus | `session.stop()` |
| Sensitivity adjusted while released | `session.set_mouse_settings(MouseSettings(...))` |
| Speed adjusted | `session.set_speed(100)` |
| Display update | `session.snapshot()` |
| Window closes / disconnect | `session.close()`; continue `tick()` until `closed` or `fault` |

`dx` is positive right, `dy` is positive down, and `wheel_notches` is positive
wheel-up. The adapter converts down into negative Y. A wheel delta of 120 in
Windows/Qt is one notch; preserve fractions for high-resolution wheels.
In continuous mode send raw counts; in pad mode send screen-pixel deltas.
Do not mix raw movement with legacy cursor movement, or raw wheel with Qt wheel.

`RobotSession` and `MotionStream` are not thread-safe. For a threaded UI, use
`ControllerWorker.post(...)`, `heartbeat()` and immutable snapshots, or implement
the same single-owner scheduling in your host. The supplied worker accumulates
adjacent mouse deltas without dropping distance and brakes after 300 ms without
a UI heartbeat. Core-only callers must implement their own input-liveness policy.
No host timer provides hard real-time guarantees.

## Transport contract

The `Transport` protocol has three methods:

- `send(command: str) -> None`: accepts one newline-free ASCII command; transmits
  it exactly once in order, adding LF as appropriate; raises on write failure.
- `read_lines(now: float) -> list[str]`: nonblocking drain of complete responses,
  without line endings, in receive order. Preserve `Ok` and error responses.
- `close() -> None`: closes the connection or releases its exclusive owner.

Reuse the host's connection through `examples/existing_transport.py`. Never
open a second connection to work around host arbitration. A failure releases
the transport but still requires a **host-level recovery lock**: another component
must not immediately send new commands into a possibly nonempty robot queue.

## Invariants to preserve

- Only one controlling client/transport owns the robot throughout the session.
- Use `G90` and offset-relative `PositionOffset` from the same coordinate frame.
- `Ok` means the oldest queued command completed, not that a new command was
  accepted. Telemetry must not retire a move. There are no request IDs.
- At most two unacknowledged motion commands may be dispatched. Never dump the
  whole generated path into serial. Drain late replies before restarting at S0.
- `E` is exit speed in mm/s, never an extruder coordinate. F is mm/s, not mm/min.
- Accumulate displacement even when input is faster than the robot. Release
  deliberately discards only unsent intent. Do not restore the old 4 mm clamp.
- An ordinary close retains the worker and connection until the committed moves,
  tangent brake and final `M205 S0` acknowledgement have completed.
- Error, timeout, reboot or disconnect invalidates the session. Do not reconnect
  automatically or use a late `Ok` to resume motion.
- Native mouse capture registration, clipping and cursor visibility are restored
  on release, focus loss, Esc and close. Retain this cleanup if reusing capture.

## Extending beyond mouse control

For an ordered drawing path, use `session.move_path(list_of_Vec3)` while armed
and idle, or the pure `plan(State(...), points, Limits(...))` API for offline
generation. Ordered paths retain corners and end at rest; live mouse prediction
is unsuitable for exact corner deposition. The current planner limits a path
to 4096 segments and rejects detail below approximately 0.2 mm.

The toolkit does not implement extrusion, paint/glue flow, tool-up/down,
conveyor encoder tracking, calibrated world-to-robot transforms or process
synchronization. Those need a separate scheduler, arrival-time prediction and
hardware-specific I/O. There is no firmware modification in this package.

## Acceptance for a host integration

Run the included tests, then exercise simulator input, wheel-only Z, large
displacement, release, focus loss, blocked UI, delayed acknowledgements and
disconnect in the host. Validate raw capture interactively and measure physical
tracking/stop behavior on the actual robot before claiming equivalent hardware
performance. See `docs/VALIDATION.md`; simulator success is not robot feedback.
