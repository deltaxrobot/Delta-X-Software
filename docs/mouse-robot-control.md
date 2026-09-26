# Mouse robot control

Connect and establish the position of the selected robot, then choose **Mouse
control** in the Robot tab. The cell must be Ready with no pending commands.
The selected robot remains exclusively reserved until the dialog closes and
its committed motion, braking tail and profile reset have completed.

- Hold the left button inside the pad and drag: right is +X, up is +Y.
- While holding, wheel up/down changes Z by the configured step.
- Release, lose window focus or press Esc to brake and stop.
- After stopping, press again to establish a new cursor/robot origin.

On Windows, **Continuous mouse capture** is enabled by default. While holding,
the cursor is hidden and raw relative mouse movement continues beyond the pad
or screen edges. XY sensitivity defaults to 0.15 mm per raw mouse count;
100 counts requests 15 mm independent of event batching. Physical mouse travel
depends on the mouse DPI, not Windows pointer acceleration. Start with small
movements and a low sensitivity when testing a different mouse.

Uncheck continuous capture to use pad mode, also used on other platforms.
In pad mode, sensitivity is mm per screen pixel and leaving the pad stops motion.
Release and press again inside the pad to continue moving farther.

Wheel Z defaults to 1 mm per notch in both modes. The
requested feed limit defaults to 100 mm/s (adjustable 10-150 mm/s). Actual
speed depends on segment length, acceleration, jerk and communications.

## Motion behavior

The updated dialog identifies itself as **Adaptive follower v2**. It estimates
mouse velocity, combines feed-forward with position-error catch-up, selects
time-based segments and sends the next command near the end of the current one.
It does not raise the existing F/A/J limits or discard accumulated displacement.
Mapped mouse motion faster than the speed limit still creates lag; no host
algorithm can remove that limit while preserving displacement.

Live prediction can aim up to 3 mm ahead, over at most 80 ms. It expires after
80 ms without new input, then the robot settles to the accumulated mouse target
within the firmware's minimum-move resolution. Stopping or reversing may
temporarily overshoot; 3 mm is not a maximum physical overshoot or stop distance.
Do not use live mouse prediction for precision dispensing at sharp corners.

Startup stops the application's legacy jogging loop, selects G90, and reads
PositionOffset. Missing, malformed and non-finite positions are rejected.
The controller then uses the shared [G-code motion engine](gcode-motion-engine.md).
No firmware changes are required.

The mouse target accumulates input without the former 4 mm clamp or 200 ms
expiry. Small residuals accumulate until the firmware's approximately 0.2 mm
minimum move is reached. Hold until the remaining-distance display reaches
the target; releasing cancels the unsent target.

The host plans a short moving horizon (20 mm, not a total travel limit), uses forward/backward speed planning
with A1500 J15000, and matches exit E to the next entry S when possible.
At most two motion commands are dispatched without completion acknowledgements.
The host aims to keep estimated committed time plus braking within 250 ms,
reducing segment size at low speed. This is a scheduling estimate, not a
measured or guaranteed stop time. One indivisible profile may exceed it.
The dialog displays the queue depth and estimated motion/braking duration.

On a reversal that cannot preserve the committed velocity, the robot first
brakes along the previous tangent, then approaches the new target. It can
therefore briefly move in the old direction. On release or close, the already
sent moves finish and an additional finite braking segment may be sent. The
stream remains alive under the broker even after the dialog is destroyed.
After a normal close, M205 S0 resets both modal edge speeds before unlocking
the robot. G90 and the last F/A/J remain set; programs should set their profile.

If the physical command queue empties, the next profile starts from zero rather
than assuming the preceding nonzero velocity survived the gap. Firmware still
pauses its step timer between commands; software look-ahead and pipelining do
not establish hard real-time motion or prove physical smoothness.

## Faults and recovery

Errors, timeouts, disconnects, safety preemption or leaving Ready stop further
streaming. An uncertain in-flight stream locks that robot in the command broker
so late Ok messages cannot acknowledge a new session. Stop/reset the controller
to establish an empty controller queue, then restart the software and establish
the robot position before resuming. The software does not reset hardware for you.

This is not an emergency stop. Controller workspace checks still apply;
acknowledged coordinates are commanded endpoints, not encoder measurements.
The supported protocol baseline is [Delta X 3](robot-firmware-delta-x-3.md).

## Verification

Run `python tools/run-tests.py --test mouse_jog --test control_plane`.
Tests cover look-ahead, corner speeds, braking feasibility, fixed-path vertices,
mouse displacement, sub-threshold accumulation, FIFO completion, asynchronous
telemetry, errors/timeouts/disconnects, queue ownership, release/reversal and
dialog destruction. A timed controller emulator checks streaming behavior,
including a 120 mm mouse target across multiple planning horizons. An injected
capture backend checks continuous input, capture failure and focus/Esc cleanup.
Live-following regressions also cover moving straight/curved targets, velocity
expiry, same-timestamp batches, final deceleration and stopping without releasing.
Native Windows capture and cursor restoration still require an interactive test.
Hardware smoothness, actual queue capacity and stop distance require measurement.
