# Architecture

```text
Mouse / other input source
       |
Optional PySide6 UI + Windows RelativeCapture
       |
ControllerWorker (single I/O thread, coalesced deltas, UI heartbeat)
       |
RobotSession (handshake, home gate, mouse mapping, errors, close)
       |
MotionStream ------ TargetTracker (input velocity only)
       |
planner.py (pure S-curve estimate, look-ahead, braking)
       |
Transport: serial / timed simulator / host connection adapter
```

## Source map

| Python module | Responsibility | C++ baseline |
| --- | --- | --- |
| `geometry.py`, `planner.py` | Pure vectors, path planning, live following, G-code | `GcodeMotionPlanner.cpp` |
| `tracker.py` | Rolling input-velocity estimate | `LiveTargetTracker.cpp` |
| `stream.py` | Two-slot pipeline, estimates, replanning, brake | `GcodeMotionStream.cpp` |
| `session.py` | Mouse mapping, startup, home gate, lifecycle | `MouseJogController.cpp`, broker behavior |
| `protocol.py`, `transport.py` | Framing, serial I/O, emulator | Firmware reference and broker completion rules |
| `capture.py` | Windows relative motion and wheel | `RelativeMouseCapture.cpp`, raw wheel handling |
| `worker.py`, `window.py` | Optional threaded UI | Standalone adaptation of `MouseJogDialog.cpp` |

The C++ files are provenance only; they are not runtime dependencies. This port
uses Python double precision instead of QVector3D float precision, so it preserves
the algorithm and constraints but does not promise byte-for-byte segment identity.

## Motion algorithm

Each mouse delta contributes to an absolute target. Input velocity is estimated
over roughly 40 ms and capped by F. Reversals and input gaps over 100 ms reset
the estimate. It decays after 40 ms without input, reaching zero after 80 ms.

Feed demand combines input velocity and position catch-up:
`ceil(input_speed + position_error / 0.12)`, bounded by the configured feed and
the committed boundary state. Prediction uses queue delay plus 60 ms, capped
at 80 ms and 3 mm, and is disabled below 10 mm/s. When prediction expires,
the follower returns to the exact accumulated target within minimum resolution.

A live plan extends up to 20 mm ahead. This is a rolling horizon, not a limit
on total travel. Cruise segments target 60 ms and are capped at 8 mm. Each
plan includes a terminal stop, but only the next short segment is committed.

For a change in scalar velocity `dv`, symmetric transition time is
`2*sqrt(dv/J)` when `dv <= A*A/J`, otherwise `dv/A + A/J`. Transition distance
is average endpoint speed times transition time. Forward/backward passes
limit edge speeds, with zero acceleration assumed at each segment boundary.

Coordinates round to 0.001 mm before timing. Exact forward collinear vertices
can merge. Turns of 90 degrees or more stop; smaller turns use a junction
allowance of 0.05 mm. This is a polyline approximation, not geometric spline
blending or a proof of joint-space jerk limits. A reversal from committed
velocity brakes on the old tangent before approaching the new target.

## Scheduling

The core is ticked at approximately 8 ms. Live mode fills a second slot only
when estimated remaining motion is about 25-50 ms. The queue budget aims for
250 ms including the candidate move and reserved brake. A single indivisible
profile may exceed the budget and is reported honestly in the snapshot.

FIFO `Ok` replies advance acknowledged position. Predictions never fabricate
acknowledgements. If the physical queue may have starved, start again at S0.
The timer, duration model and queue estimates are not measured execution time.
Host or transport loss may prevent delivery of the reserved braking tail.

## Lifecycle

```text
new -> connecting -> ready (unarmed)
                      | home -> homing -> ready (armed)
                      | explicit existing-home confirmation -> armed
                      | hold -> following -> release -> drain -> idle
                      | close -> closing -> drain -> M205 S0 -> closed
any active state -> error/timeout/disconnect/reboot -> fault (terminal)
```

`state == ready` alone does not mean idle or armed; use the corresponding
snapshot fields. Closing during incomplete startup/homing fails the session
because the outstanding controller transaction cannot be cancelled reliably.
An `Ok` only reports a commanded endpoint. It does not establish encoder-based
physical position or prove successful homing after mechanical failure.
