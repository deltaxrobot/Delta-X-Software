# Validation and limitations

Development platform: Windows, Python 3.12.10, PySide6 6.9.1, pyserial 3.5.
Run `python -m pytest -q` from the project root. GUI tests use the offscreen
Qt platform and are skipped if optional GUI dependencies are absent.

Recorded development run (2026-09-27): **61 tests passed**. The offscreen GUI
smoke test, PowerShell launcher syntax check, Python wheel build and isolated
source-ZIP check also passed. The headless example reached `(120, 30, -297)`
from `(0, 0, -300)` with zero remaining target distance, maximum queue depth two,
and a clean close. These coordinates are simulator results.

Automated coverage includes:

- Continuous straight paths, corner retention, finite profiles, invalid limits,
  coordinate rounding, representable G-code length and subminimum rejection.
- Prediction bounds, velocity expiry, same-timestamp batches, reversal braking,
  final deceleration and lower requested feed.
- A held 120 mm mouse displacement across multiple planning horizons, small
  accumulated deltas, fractional wheel-only Z, straight/curved live targets.
- Two outstanding commands at most, telemetry filtering, FIFO acknowledgements,
  release/rebase, ordered paths and graceful close with modal edge-speed reset.
- Handshake/home gating, malformed position, timeout, transport loss, controller
  errors/reboot, unexpected Ok, and extra replies in the same receive batch.
- Partial serial framing, selected baudrate forwarding, partial write errors.
- Offscreen wheel events, Esc, focus loss and UI-heartbeat expiry.
- Windows RAWINPUT structure sizes, signed wheel deltas and suppression of
  duplicate legacy wheel events using injected native packets.

The simulator uses the host duration model. It tests scheduling and protocol
behavior, not independent physical dynamics. A passing test does not prove
tracking latency, smoothness, collision avoidance or actual stopping distance.

Before live use, verify port/baudrate and exclusive ownership, establish the
physical home, then test a small XY gesture and wheel-only Z at reduced speed.
Check displacement scale/directions, cursor cleanup after focus/Esc/close,
screen-edge continuity, release while moving and physical response to connection
loss. Measure following and stopping on the actual robot if latency matters.
No physical robot motion was issued as part of the package's automated checks.

Native registration/clipping restoration and cursor visibility still require
interactive Windows validation with the actual mouse. Non-Windows pad mode is
implemented but has not been validated on those operating systems.
