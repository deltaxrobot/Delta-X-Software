# Supported protocol

Baseline: Delta X 3 firmware reviewed by Delta X Software 2.0.0. The standalone
package identifies `YesDelta` and requires `MODEL:DELTA_X_3`; it does not treat an
unidentified generic G-code controller as compatible.

Serial is selected-port/selected-baud, 8 data bits, no parity, one stop bit,
no software/hardware flow control. Commands are ASCII, uppercase parameter
letters, space-separated, LF-terminated, at most 79 characters before LF.
Receive framing accepts CRLF or LF, buffers partial lines and drains multiple
lines. Invalid encoding or overlong lines fail the session.

Connection sequence (strict, one transaction at a time):

| Command | Expected terminal response |
| --- | --- |
| `IsDelta` | `YesDelta` |
| `ROBOTMODEL` | `MODEL:DELTA_X_3` |
| `G90` | `Ok` |
| `M205 S0` | `Ok` |
| `PositionOffset` | `X,Y,Z` or up to six finite numeric axes; no trailing Ok |

The legacy application's `jogging (0, 0, 0)` command is a host-side feature and
is intentionally not sent to this standalone hardware connection. Close the
other application's controlling session before connecting here.

An explicit Home action sends `G28`, waits up to 60 seconds for `Ok`, then
queries `PositionOffset`. There is no automatic home on connection. G28 also
moves servo channels on the baseline firmware. A successful protocol response
does not prove correct physical homing after a jam or failed switch.

Generated motion example:

```text
G01 X12.000 Y-3.000 Z-299.000 F100 A1500 J15000 S20 E30
```

| Token | Meaning | Unit |
| --- | --- | --- |
| X/Y/Z | Absolute target in the active work-offset frame | mm |
| F | Maximum segment speed | mm/s |
| A | Acceleration limit | mm/s^2 |
| J | Jerk limit | mm/s^3 |
| S | Segment entry speed | mm/s |
| E | Segment exit speed, not extrusion | mm/s |

Normal segments have integer S/E no greater than F-2. The baseline has an
approximately 0.2 mm minimum move; the planner reserves 0.201 mm before
rounding. Subminimum mouse deltas accumulate. Tiny ordered-path detail is
rejected instead of silently deleting vertices.

Only exact `Ok`, case-insensitive, completes a move. Position/I/O telemetry
does not consume FIFO acknowledgements. Recognized errors include `error`,
`Unknown:`, `Delta:EStop`, `Delta:Stop`, `Delta:Pause` and an unexpected boot
`Init Success!`. A fault terminates the session and closes the transport; it
does not send an automatic reset/resume or claim already-sent moves stopped.

Motion acknowledgements time out at estimated duration plus three seconds.
Startup commands use three seconds. Late replies must not be attributed to a
new session without establishing an empty controller queue.

Only a normal close drains and sends `M205 S0`, resetting both modal edge speeds.
G90 and the last F/A/J remain set. The next application/program should set its
own motion profile explicitly. Robot geometry, offsets and stored configuration
are never rewritten by this package.

The controller cannot replace/cancel an already queued move. Its response
destination is shared across transports. This requires an exclusive client and
does not provide hard real-time following. Workspace/kinematic checks still
belong to the actual controller; this package is not a collision checker and
does not infer a calibrated workspace from generic dimensions.
