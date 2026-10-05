# Multi-Robot Conveyor Sorting Example

These files are a commissioning baseline for one `#Objects` tracking list, one camera, and two robots sharing a conveyor.

1. Calibrate the camera into conveyor coordinate system `C`.
2. Create two matrices in tracking group 0: `#0.ConveyorToRobot0` and `#0.ConveyorToRobot1`.
3. Replace claim zones, Z heights, placement poses, belt speed, and angle offsets in each worker.
4. Create three G-Script threads and load `00-vision-tracking.gcode`, `10-robot0-type0.gcode`, and `11-robot1-type1.gcode`.
5. Dry-run with a raised Z before enabling the end effector or production conveyor.

In **Tracking Runtime Configuration**, start with `Publish period = 50 ms`, `Maximum camera age = 2000 ms`, `Maximum encoder age = 2000 ms`, `Frame completion timeout = 3000 ms`, `Maximum queued frames = 8`, and `Maximum queued encoder samples = 24`. The **Tracking status** line must show no overflow, and encoder/camera age must remain below the stale limits before a robot is enabled.

Both workers use `Passert` to validate Safe Z relative to Pick Z and use `PreleaseObject` when confidence is below the process threshold. Set `R0MinConfidence` and `R1MinConfidence` from a validated model; never remove the release branch.

The vision thread uses the `PcaptureAndDetect(0)` handshake. Execution resumes only after the correlated frame has both encoder samples, detections, and a tracking `FrameReady` event. Do not insert a fixed inference delay between capture and tracking.

New tracks require two consecutive detections to become `CONFIRMED` by default. A worker faults when Status is `VISION_STALE` or `ENCODER_STALE` so the cell can stop instead of waiting indefinitely.

Both workers support optional closed-loop vacuum confirmation. `R0UseVacuumFeedback` and `R1UseVacuumFeedback` default to zero for delay-based dry runs. Set the appropriate flag to one after the I/O backend publishes `Vacuum.R0.OK` or `Vacuum.R1.OK`. `PwaitUntil` faults after 500 ms if pickup is not confirmed, and `PcompleteObject` runs only after the sensor succeeds.

The sample convention is `+Y` along conveyor travel, robot0 in Y=300..450, robot1 in Y=600..750, robot0 selecting type 0, and robot1 selecting type 1. These values are examples, not safe machine parameters.

See `docs/multi-robot-conveyor-sorting.md` for installation, calibration, tracking, and acceptance procedures.
