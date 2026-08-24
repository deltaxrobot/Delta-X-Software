# Multi-Robot Sorting on a Shared Conveyor

## 1. System model

The cell uses one shared moving-object map. The camera produces detections, the encoder turns detections into tracks with stable UIDs, and every robot is a worker that obtains work from the same map.

```text
USB/GigE camera
      | image + capture timestamp
      v
Detect (type, x, y, w, h, angle)
      | calibration P -> C
      v
Tracking + encoder ---> Objects[UID, type, pose, state]
      |
      +-- claim by zone/type ---> robot0 ---> bin/rule 0
      +-- claim by zone/type ---> robot1 ---> bin/rule 1
```

Keep three coordinate systems explicit:

- `P`: camera pixels.
- `C`: the shared conveyor coordinate system in millimetres. Use `+Y` along belt travel and `+X` across the belt.
- `R0`, `R1`, ...: each robot's local coordinate system.

The camera pipeline must ultimately produce poses in `C`. Each worker maps the claimed pick point from `C` to `Ri` through `ConveyorToRobotN`. Claim zones are always defined in `C`, never in robot coordinates.

## 2. Responsibilities

| Component | Responsibility |
|---|---|
| Delta robot | Motion interpolation, end-effector control, and `SYNC` vector execution |
| Conveyor | Stable movement through direct G-code or robot output |
| Encoder | Authoritative belt displacement; computer time is not a substitute |
| Camera | Upstream image capture with rigid mounting and stable illumination |
| Detector | Type, centre, size, and angle; it never assigns the tracking UID |
| Tracking | UID assignment, global association, frame-aware encoder compensation, lifecycle, and ownership |
| Vision G-Script | Capture/detect and wait for the matching `FrameReady` |
| Robot G-Script | Claim one UID, perform conveyor-synchronous pick, then complete or release |

A claim is an owner-specific, time-limited lease. It is the lock that prevents two workers from selecting the same part. Selection prefers the eligible object furthest downstream along the conveyor velocity vector.

The lifecycle is `TENTATIVE -> CONFIRMED -> CLAIMED -> PICKED`; temporarily missing confirmed tracks enter `LOST`. By default, a detection must appear in two consecutive frames before it can be claimed. A `CONFIRMED` track is not claimable unless vision and encoder health are `READY`.

## 3. Recommended installation

1. Mount the encoder on a non-slip shaft or use a measuring wheel with stable pressure. Avoid motor pulses when the transmission can slip relative to the belt.
2. Place the camera far enough upstream for capture, inference, communication, and robot approach. Rigidly mount the camera, lens, and lighting as one assembly.
3. Use strobe or hardware triggering for reflective parts or high speeds when supported. USB is suitable at moderate rates; GigE is preferable when deterministic trigger and timestamps matter.
4. Start with non-overlapping robot workspaces. Allow overlap only after a cell- or PLC-level collision coordinator exists.
5. E-stop, guards, axis limits, and end-effector energy isolation belong in a safety circuit, PLC, or controller. G-Script is not a safety function.

## 4. Calibration order

### 4.1 Encoder

1. Mark two belt positions 500-1000 mm apart.
2. Run in the production direction and record the count difference.
3. Calculate `mm_per_count = measured_distance / count_difference`, then configure the encoder/controller so G-code reports millimetres.
4. Verify sign. If belt travel along `+Y` decreases the value, enable `Reverse Encoder` or invert the sign in exactly one location.
5. Repeat forward and reverse travel at least five times. Travel error must fit within the pick error budget. Correct mechanical slip before software tuning if error changes with load.

### 4.2 Camera pixels `P` to conveyor `C`

1. Fix resolution, focus, exposure, and ROI before collecting points. Any later resize or crop invalidates the matrix.
2. Use Warp/Perspective to flatten the belt plane when the camera is oblique.
3. Place measured references in `C`, enter image/real point pairs in Mapping Point Tool, and calculate the matrix.
4. The two-point mapping supports rotation, scale, and translation. Use Cloud Point Mapping with a grid across the ROI when distortion remains or higher accuracy is required.
5. Validate with points that were not used to fit, especially near every ROI corner. Record maximum and RMS error.

Internal detection passes through Mapping Matrix Node. An external detector returning pixels must set `"coordinateSpace":"image"`; the same mapping is applied.

### 4.3 Conveyor `C` to each robot `Ri`

1. Touch at least two belt references with each robot. Three non-collinear points provide a better check for scale or shear.
2. Calculate and store one matrix per robot, such as `#0.ConveyorToRobot0` and `#0.ConveyorToRobot1` for tracking group 0.
3. Use `.Map(x,y)` in G-Script to convert the object centre into robot coordinates.
4. Determine `AngleOffset` and angle sign independently. Check at 0, 45, and 90 degrees. A mirrored transform requires a sign correction, not only an offset.
5. Transform the belt velocity vector from `C` into each `Ri`. The vector supplied to `SYNC robotN` must be mm/s in robot axes, never counts/s or pixels/s.

### 4.4 Z and timing

1. Teach `SafeZ`, `PickZ`, placement poses, and W limits for every robot.
2. Measure capture-to-detection latency. A frame commits only after both capture/detect encoder samples and detections arrive. `PcaptureAndDetect` waits for `FrameReady`; do not insert a fixed delay to guess inference completion.
3. Set `DistanceThreshold` above detector error plus maximum movement between frames, but below the minimum part separation. A useful starting point is `v_belt * frame_period + 2 * detection_error`.
4. Set `IoUThreshold` low enough to tolerate inter-frame movement but high enough to prevent nearby parts exchanging UIDs.

## 5. External-detector contract

Image-space result:

```json
{
  "type": "objects",
  "protocol": "DXV1",
  "frameId": "41",
  "requestId": "9001",
  "trackingId": 0,
  "coordinateSpace": "image",
  "listName": "#Objects",
  "list": [
    {"type": 0, "x": 412.5, "y": 238.0, "z": 0, "w": 35, "h": 62, "angle": 17, "isPicked": false}
  ]
}
```

Already calibrated conveyor-space result:

```json
{
  "type": "objects",
  "protocol": "DXV1",
  "frameId": "41",
  "requestId": "9001",
  "trackingId": 0,
  "coordinateSpace": "conveyor",
  "listName": "#Objects",
  "list": [
    {"type": 1, "x": -42.2, "y": 285.4, "z": 0, "w": 28, "h": 55, "angle": -8, "isPicked": false}
  ]
}
```

Echo `frameId`, `requestId`, and `trackingId` exactly from the DXV1 image message. Type is a stable integer defined by the model. Delta X assigns the tracking UID after association; the detector never sends it. See `docs/external-vision.md` or click **?** in External Script.

## 6. G-Script tracking primitives

```gcode
M98 PclaimObject(trackingId, resultName, owner, minX, maxX, minY, maxY, typeFilter, leaseMs)
M98 PreleaseObject(trackingId, uid, owner)
M98 PcompleteObject(trackingId, uid, owner)
```

`claimObject` writes:

```text
#result.Found
#result.UID
#result.Type
#result.X  #result.Y  #result.Z
#result.W  #result.L  #result.A
#result.ClaimOwner
#result.ClaimExpiresAt
#result.Status       ; READY / VISION_NOT_READY / VISION_STALE / ENCODER_NOT_READY / ENCODER_STALE
#result.TrackState   ; TENTATIVE / CONFIRMED / LOST / CLAIMED / PICKED
#result.FrameId
```

Rules:

- `Found = 0`, `Status = READY`: no eligible object; wait briefly and retry.
- `VISION_NOT_READY` or `ENCODER_NOT_READY`: startup is incomplete; do not accept work.
- `VISION_STALE` or `ENCODER_STALE`: fault the worker instead of retrying silently.
- Call `completeObject` only after the end effector has secured the part and any required sensor confirms it.
- Call `releaseObject` when abandoning a part before pickup.
- If a worker terminates, the monotonic lease expires and another worker may claim the part. Late complete/release operations are rejected.
- Tracking rejects new claims when detections or encoder data exceed the configured stale threshold (2 seconds by default).
- `CompleteRejected` or `ReleaseRejected` faults the worker because ownership can no longer be trusted.

## 7. Commissioning sequence

1. Verify E-stop, stop the conveyor, and place the end effector in a safe state.
2. Connect robots, encoder, conveyor, and camera; home each robot at low speed.
3. Load camera, mapping, and tracking settings. Verify stationary object coordinates in `C`.
4. Run the belt slowly with the vision thread only. Every `PcaptureAndDetect(0)` must return `FrameReady:n`; the UID must remain stable across the ROI.
5. Dry-run one robot with the end effector disabled or Z raised.
6. Perform real picks with one robot before enabling another.
7. Use exactly one vision thread and one worker thread per robot. Never run multiple vision producers into one tracking ID.

Examples are in `script-example/multi-robot-sorting/`.

## 8. Minimum acceptance criteria

- Encoder: cumulative camera-to-pick travel error fits inside the pick error budget.
- Mapping: validation error at ROI edges fits inside the permitted suction/grip radius.
- Tracking: 100 consecutive parts retain UIDs without out-of-policy ghost tracks.
- Association: reorder detections, pass two parts close together, omit 1-5 frames, and vary type labels; UIDs follow the configured policy.
- Ownership: two workers compete for one part and exactly one receives `Found=1`.
- Recovery: terminate a worker after a claim; the part unlocks only after lease expiry and is never picked twice beforehand.
- Safety response: lost camera/encoder, robot timeout, or rejected ownership causes a controlled cell stop.

## 9. Tracking parameters and remaining integration work

Source defaults confirm after two hits, remove a confirmed track after five missed frames, remove a tentative track after one missed frame, change type after three consistent frames, and time out a frame after three seconds. Revalidate these values against actual FPS, belt speed, and part density.

The software provides shared tracking, frame-aware encoder compensation, global association, lifecycle, atomic claims, leases, health faults, bounded queues, and sensor-wait primitives. Physical deployments must still configure and validate geometric collision avoidance, controller-specific sensor mappings, encoder wrap/reset behavior, recipe/bin management, OEE, and the cell-level fault/recovery state machine.

## 10. Realtime and vacuum-sensor commissioning

In **Tracking Manager**, start with `Publish interval = 50 ms`, `Vision stale = 2000 ms`, `Encoder stale = 2000 ms`, `Frame timeout = 3000 ms`, `Max pending frames = 8`, and `Max encoder reads = 24`, then click **Apply**. During vision-only operation:

- `Tracking.N.State` remains `READY`;
- `PendingFrames` and `PendingEncoderReads` regularly return to zero;
- `FrameQueueOverflows` and `EncoderQueueOverflows` remain zero;
- `EncoderAgeMs`, `VisionAgeMs`, and `LastCommitLatencyMs` remain below the accepted budget.

When a vacuum sensor is available, publish a project-scoped Boolean such as `Vacuum.R0.OK` and use:

```gcode
M03
M98 PwaitUntil(#Vacuum.R0.OK == 1,500,10,"robot0: vacuum timeout")
M98 PcompleteObject(0,#R0Target.UID,#R0Owner)
```

The timeout must exceed the measured worst-case vacuum build time but remain shorter than the time for a part to leave the pick zone. On timeout, G-Script faults and preserves ownership evidence; the cell recovery procedure decides whether to release the claim, reject the part, or move the robot to a safe pose. Never use a simulated sensor for final machine acceptance.
