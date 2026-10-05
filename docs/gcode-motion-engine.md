# Host-side G-code motion engine

This implementation generates ordinary Delta X 3 G01 commands. It neither
modifies nor flashes firmware. Mouse control uses it now; the ordered-path API
is available for future drawing/process integrations, not yet wired into those
screens. Conveyor prediction and dispensing/extrusion synchronization are not
implemented by this change.

## Components

- `GcodeMotionPlanner`: pure path-to-segments calculation, with no device I/O.
- `GcodeMotionStream`: latest-target or ordered-path input, bounded transmission,
  replanning, acknowledgements, and braking/close lifecycle.
- `DeviceCommandBroker::SubmitMotion`: exclusive transport for at most two
  outstanding G01 commands and a standalone final M205 S0 reset.
- `MouseJogController`: reads initial position and adapts cursor displacement.
- `LiveTargetTracker`: estimates input velocity from timestamped intent; this
  is not robot position feedback.

`GcodeMotion::State` carries position, incoming direction and scalar speed.
`GcodeMotion::Limits` carries feed, acceleration, jerk, segment length, minimum
length, junction allowance and queued-time target. `plan(state, points, limits,
error)` returns segments with serialized coordinates, integer F/A/J/S/E and
estimated duration. Each plan ends at zero speed.

## Planner

Coordinates are quantized to 0.001 mm before length and timing calculations.
Forward collinear vertices are merged; other vertices retain their order.
Segments are split to at most 2 mm by default. Unrepresentable path detail below
the firmware minimum is rejected rather than silently deleting a drawing corner.
The plan is limited to 4096 segments and commands to 79 characters.

Junction speeds depend on the angle, acceleration, jerk and a 0.05 mm allowance.
Turns of 90 degrees or more stop at the vertex. Gentle turns can share nonzero
edge speed. This is a polyline junction approximation, not geometric spline
blending or a guarantee of bounded joint-space jerk through an exact corner.

Backward and forward passes constrain boundary speeds using symmetric jerk-
limited transitions with zero acceleration at each boundary. For a speed change
dv, transition time is 2*sqrt(dv/J) below A^2/J, otherwise dv/A + A/J. Transition
distance is the mean of entry/exit speed times that duration. Feed and edge
speeds are integers, with S/E no greater than F-2, matching the firmware limits.
A peak-speed search estimates acceleration, cruise and deceleration time.
These estimates approximate the firmware planner; they are not device telemetry.

## Live and ordered inputs

The caller obtains an exclusive broker lease while Ready, establishes G90 and
reads PositionOffset, then constructs a stream with that owner and position.
The stream is parented to the broker, not the caller's dialog.

- `setTarget(position)` replaces only uncommitted intent. The host repeatedly
  replans up to 20 mm ahead from the last committed endpoint and speed using
  the adaptive live follower described below.
- `setPath(points, error)` starts an ordered path while idle. It preserves path
  order and requires every segment to be representable. Feed changes during a
  fixed path are deferred to a future path.
- `stop()` cancels uncommitted intent and adds a finite tangent brake if needed.
- `close()` also drains the stream, resets modal S/E with M205 S0, releases the
  lease and destroys the stream. Closing the UI does not abandon a braking tail.

Replanning from a nonzero committed speed can fail when the target reverses,
the stopping distance is too short, or a lower feed is requested. In those
cases a tangent brake is committed first. Thus live following can overshoot the
new target temporarily; it is not appropriate for exact corner deposition.
Use ordered paths for drawing and other operations that must preserve geometry.

## Adaptive live follower v2

The absolute mouse target still accumulates every displacement. A rolling
40 ms input window estimates velocity, capped at the configured feed. An initial
single sample or initial same-timestamp burst does not infer velocity. Gaps over
100 ms and direction reversals reset the estimate. With no new displacement it decays
after 40 ms and reaches zero at 80 ms.

The follower adds a velocity feed-forward term to position-error catch-up
(`|v| + |error| / 0.12`, limited by the configured feed). It never increases the
configured acceleration or jerk. Prediction accounts for the estimated queue
delay plus 60 ms, capped at 80 ms and 3 mm. Prediction is disabled below 10 mm/s.
That 3 mm is an intent offset, NOT a bound on physical tracking error or stopping
distance. Sent moves and braking can overshoot when input stops or reverses.
Stale intent returns to the exact accumulated target, subject to the firmware's
approximately 0.2 mm minimum representable correction.

Segments aim for 60 ms of cruise travel, capped at 8 mm, instead of fixed 2 mm
chunks. The finite look-ahead retains a terminal stop but only its first segment
is committed. Close to the target, an indivisible feasible final deceleration is
kept intact: subdividing it would add artificial zero-acceleration boundaries
and can leave an uncorrectable sub-minimum position residue.

Live mode refills the second physical slot only when an estimated 25-50 ms of
the current command remains, rather than filling both slots immediately. This
lets later mouse input replace unsent intent. A known expired head waits for
its acknowledgement and restarts from rest, rather than assuming velocity
survived a gap. Segment length is reduced as needed to retain braking budget.
Ordered paths continue to use the original geometry-preserving planner and
eager two-command pipeline.

The `liveTrackingLatency` emulator test drives a straight target at 80 mm/s and
a curved target with X speed 45 mm/s and Y = 6*sin(4*t). On the development
Windows run, mean distance to the last acknowledged endpoint fell from roughly
41-45 mm to 17 mm on the straight case and from 15-18 mm to 8-10 mm on the curved
case. These are host-scheduled emulator results, not measured physical lag or a
hard-real-time guarantee; OS scheduling also affects them. Tests guard the
latency trend, final settling, prediction expiry, reversal and release.

## Transmission and time budget

At most two commands are physically dispatched. The budget includes estimated
remaining execution, the candidate segment and a reserved braking duration.
The default is 250 ms, not a claimed real-world latency. The head estimate ages
with a monotonic timer; queue ownership is released only by actual replies.
Observed acknowledgement intervals adjust an overhead allowance. Live segment
size can shrink to fit the budget; a single indivisible profile is allowed to exceed
the nominal budget to avoid deadlock and is shown in the UI estimate.

Only exact Ok (case-insensitive) completes a stream command. Ordinary unsolicited
position/I/O telemetry does not consume an acknowledgement. Errors fail the
entire stream. A lost reply, disconnect, cancellation, cell-state interruption
or safety preemption latches a per-device fault, rejecting subsequent non-safety
work so late replies cannot be attributed to new commands. Recovery requires
establishing an empty controller queue and a new software broker session.

If acknowledgement timing suggests all dispatched motion may already have
finished, the stream drains outstanding replies before restarting at S0.
This avoids inferring continued velocity from a backlog of delayed Ok messages.

The receiver has no request IDs or replace/cancel-queued-segment operation.
Already dispatched segments cannot be rewritten, so abrupt input changes have
an unavoidable committed-motion delay. Firmware pauses between G-codes even
with E > 0. If the queue starves, the host restarts from S0 and replans any
uncommitted fixed path rather than claiming continuous velocity across the gap.
On host/transport loss the already sent finite segments can still execute;
the software cannot guarantee delivery of the reserved braking tail.

## Extension boundaries

Drawing can supply ordered XYZ paths and use the same planner. It still needs
tool-up/down sequencing and its UI integration. Moving workpieces need a
timestamped, calibrated encoder transform evaluated at predicted arrival time,
including the committed queue; a constant coordinate offset is insufficient.
Extrusion, paint and glue need separate process scheduling and hardware-specific
flow control. Delta X 3 E means exit speed, not an extruder coordinate.

The current broker stream is available in Ready under an exclusive manual
lease. Automation-mode policy must be designed before using it from production
G-Script or conveyor tracking. Do not bypass that policy through raw serial I/O.
