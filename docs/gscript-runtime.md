# G-Script Runtime Operator Guide

This is the canonical guide for new G-Script programs. In Delta X Software, open **G-Script -> Help** to view it inside the application.

For executable examples of the built-in commands, start with the
[G-Script command tour](gscript-command-tour.md). It separates software-only
examples, isolated hardware-contract tests, and read-only robot queries.

Commissioning-ready examples are in `script-example/multi-robot-sorting/` in both the source tree and release package. Open `00-vision-tracking`, `10-robot0-type0`, and `11-robot1-type1` in three separate G-Script threads.

## 1. Scope

The desktop companion `delta-x-cli` uses the same G-Script worker and connected
devices as Code Run. With Delta X Software open, use
`delta-x-cli run program.gcode --project project0 --thread 0`. It waits for the
result and supports Ctrl+C, `status`, `stop RUN_ID`, `--timeout` and `--json`.
See [Command-line G-Script execution](cli.md) for the complete guide.

G-Script orchestrates robots, conveyors, encoders, cameras, tracking, and I/O devices. Robot firmware remains responsible for motion interpolation. PLC, STO, E-stop, and safety circuits must operate independently of G-Script.

The application analyzes every program before execution. Structural errors, invalid canonical primitive arguments, unresolved control flow, unknown `M98` macros, and malformed device names block execution. They never fall through to the generic G-code path or reach a default robot.

## 2. Minimal program

```gcode
SELECT robot0
G28
G01 X0 Y0 Z-100 F500
M98 Pdelay(200)
```

`SELECT` chooses the active device for the thread. A device may also be addressed explicitly at the start of a line:

```gcode
robot0 G01 X100 Y20 Z-80 F500
conveyor0 M311 S100
encoder0 M317
device0 M42 P1
```

Valid device names are `robotN`, `conveyorN`, `encoderN`, `sliderN`, and `deviceN`. Explicit device addressing is recommended in production programs.

### Editor assistance

- Autocomplete opens after entering a keyword or variable; press `Ctrl+Space` explicitly. Suggestions include control flow, G/M codes, primitives, devices, and variables in the active project.
- Inside `M98 P...(...)`, the editor displays the primitive signature and active argument.
- **Details** shows or hides the Problems, Watch, Threads, and Console pane. It is closed initially to leave more room for source code; validation errors open Problems automatically. Software cell faults remain visible outside this pane.
- **Problems** lists diagnostics; double-click an entry to navigate to the source line.
- **Watch** automatically follows `#...` variables referenced by source. Use **Pin variable** for telemetry or I/O not present in source. Values come from the current project's `VariableManager` namespace.
- **Threads** displays state, line, device, and detail for every G-Script thread. Double-click a row to switch editors.
- **Console** contains the device log, command input, and destination selector. Submitting a command can operate hardware; opening the tab alone does not.
- **New from template** creates a vision worker or robot pick worker. Generated code still requires real mapping, zone, pose, and machine-limit review.

`Validate`, autocomplete, Watch, and the template wizard never send hardware commands.

## 3. Generic commands and responses

```gcode
M98 Psend(deviceId, command, responseVariable, timeoutMs)
```

The first two arguments are required. `responseVariable` and `timeoutMs` are optional.

```gcode
M98 Psend(encoder0, "M317", #EncoderReply, 1000)
; Psend faults on a timeout or device error; EncoderReply contains the response.

#SafeZ = -200
#PickZ = -300
M98 Passert(#SafeZ > #PickZ, "Safe Z must be above Pick Z")

#IoCommand = "M42 P1"
M98 Psend(device0, #IoCommand, #IoReply, 1500)
```

While waiting, the thread is in `WaitingForDevice`. A device error or timeout transitions it to `Faulted`; execution does not continue automatically.

Each physical device processes only one response-bearing command at a time. `DeviceCommandBroker` queues commands from multiple G-Script threads in FIFO order and routes each response to the owning request. Manual and remote motion commands are blocked in AUTO. Safety stop commands have priority and may cancel queued work. Do not bypass the broker with another G-code path.

### Closed-loop process waits

```gcode
M98 PwaitUntil(condition, timeoutMs[, pollMs[, message]])
```

`PwaitUntil` reevaluates a `VariableManager` expression without blocking the thread. Non-zero is success. `pollMs` defaults to 20 ms and is clamped to 5-1000 ms. Timeout faults the program with the supplied message. Confirm a pick from an actual vacuum sensor:

```gcode
M03
M98 PwaitUntil(#Vacuum.R0.OK == 1, 500, 10, "robot0: vacuum timeout")
M98 PcompleteObject(0, #Target.UID, #Owner)
```

The I/O backend or device plugin must publish `Vacuum.R0.OK` into the active project. Never call `PcompleteObject` before pickup is confirmed. During the wait, the runtime state is `WaitingForCondition`, the expression appears in `GScript.<thread>.ActiveCondition`, and Stop remains responsive.

## 4. Variables and namespaces

Use relative names in G-Script. The application adds the active project namespace:

```gcode
#Speed = 500
#PickX = #Target.X
#Message = "ready"
```

Important runtime namespaces include:

```text
GScript.thread0.State / Running / LastError / Response
GScript.thread0.ActiveDevice / ActiveCommand / CurrentLine
Cell.State / FaultReason / ActiveWorkerCount
Cell.LastRejectedCommand / LastRejectedOwner / LastRejectedReason
robot0.Connected / State / Position.X ... Position.V / LastResponse
Encoder.0.RawPosition / Position / Velocity / LastUpdateAt
Camera.Connected / State / Width / Height
ExternalVision.State / Connected / FramesSent / ResultsReceived / LastLatencyMs
Tracking.0.State / LastFault / ObjectCount
Tracking.0.PendingFrames / PendingEncoderReads
Tracking.0.EncoderAgeMs / VisionAgeMs / LastCommitLatencyMs
Tracking.0.FramesCaptured / FramesCommitted / FramesRejected / FramesExpired
Tracking.0.FrameQueueOverflows / EncoderQueueOverflows
Tracking.0.Publications / PublicationsSuppressed / LastPublishDurationUs
Objects.Count
Objects.0.UID / Type / Confidence / Label / ExternalId
Objects.0.X / Y / Z / W / L / A
Objects.0.State / Confirmed / IsClaimed / ClaimOwner
```

G-Script can read every value published by a backend into the active project's `VariableManager`. It cannot access UI widgets or internal Qt objects directly.

## 5. Functions and local variables

Function arguments are local. Declare temporary values with `LOCAL`; they are removed when the function returns and never pollute the project store.

```gcode
FUNCTION Sum(limit)
    LOCAL #i = 0
    LOCAL #total = 0
    WHILE #i < #limit
        #total = #total + #i
        #i = #i + 1
    ENDWHILE
    RETURN #total
ENDFUNCTION

#Result = #Sum(10)
```

Assigning to a variable that was not declared `LOCAL` still creates or updates a project variable for backward compatibility.

## 6. Control flow

```gcode
IF #Value > 10
    #Class = 2
ELIF #Value > 5
    #Class = 1
ELSE
    #Class = 0
ENDIF

FOR #i = 0 TO 9 STEP 1
    IF #i == 5 THEN CONTINUE
ENDFOR

WHILE #Counter < 100
    #Counter = #Counter + 1
    IF #Counter > 20 THEN BREAK
ENDWHILE

SWITCH #Class
CASE 0
    #BinX = 100
CASE 1
    #BinX = 200
DEFAULT
    #BinX = 300
ENDSWITCH
```

`SWITCH` does not fall through. After one branch executes, control advances past `ENDSWITCH`. Place `LABEL/JUMP` at outer block boundaries; never jump between scopes inside `IF`, `FOR`, `WHILE`, `SWITCH`, or `FUNCTION`.

## 7. Multi-robot vision and tracking

Vision thread:

```gcode
LABEL VISION_LOOP
M98 PcaptureAndDetect(0)
M98 Pdelay(10)
JUMP VISION_LOOP
```

Robot worker:

```gcode
SELECT robot0
#Owner = "robot0"

LABEL WORK_LOOP
M98 PclaimObject(0, #Target, #Owner, -180, 180, 300, 450, -1, 30000)

IF #Target.Found == 1
    IF #Target.Confidence >= 0.60
        G01 X[#Target.X] Y[#Target.Y] Z-80 W[#Target.A] F500
        ; Perform the pickup cycle.
        M98 PcompleteObject(0, #Target.UID, #Owner)
    ELSE
        M98 PreleaseObject(0, #Target.UID, #Owner)
    ENDIF
ELSE
    M98 Pdelay(20)
ENDIF
JUMP WORK_LOOP
```

A claim snapshot contains `Found`, `UID`, `Type`, `Confidence`, `Label`, `ExternalId`, pose, dimensions, owner, state, and frame ID. Release an abandoned pre-pick claim with:

```gcode
M98 PreleaseObject(0, #Target.UID, #Owner)
```

Never write `IsPicked` directly because that bypasses multi-robot ownership.

## 8. Runtime state and fault handling

Runtime states are `Idle`, `Validating`, `Running`, `WaitingForDevice`, `WaitingForTimer`, `WaitingForCondition`, `Completed`, `Faulted`, and `Stopping`.

Resolve all **Problems** errors before running. On a fault, inspect:

```gcode
#LastState = #GScript.thread0.State
#LastError = #GScript.thread0.LastError
```

Use `Passert` to stop when a process condition is invalid. Do not use fixed delays to guess that a camera or device has finished; use `PcaptureAndDetect`, `Psend`, and `PwaitUntil` for actual acknowledgements or state.

### Cell state and controlled stop

The G-Script status bar reports `CELL: READY`, `AUTO RUNNING`, `PAUSED`, `FAULTED`, or `RECOVERING`:

- Starting the first G-Script places the cell in `AutoRunning`; `Cell.ActiveWorkerCount` tracks all workers.
- A worker fault or pause triggers controlled stop: stop camera cycling, cancel queues, send stop commands to registered robots/conveyors/sliders, and request all running G-Scripts to stop.
- A device command timeout cancels that device's queued commands and faults the cell. It never sends the next command because a late response could be misidentified.
- In `Faulted`, only safety commands are accepted. **Reset fault** is enabled only after all workers stop and always requires operator confirmation.
- Reset clears only the software fault. Before confirmation, inspect E-stop/STO, robot workspaces, held parts, vacuum, and controller state. The old program never resumes automatically.

Terminal and custom conveyor commands must name their target, for example `conveyor0 M311 100`. Manual motion is rejected while the cell is in AUTO; stop commands such as `robot0 M84` retain safety priority.

### Network defaults

The control server binds only to `127.0.0.1` by default. DXV1 external detection remains available on that endpoint, while legacy assignments that run G-Script, edit source, emit events, or write variables are disabled. Enable LAN access only on an assessed trusted network. The legacy protocol has no TLS or token and must never be exposed to the Internet. `Network.AllowLegacyRemoteControl = true` is only a compatibility switch for an explicitly reviewed deployment.

## 9. Tracking realtime settings

In **Tracking Runtime Configuration**, select `trackingN`, configure the encoder,
tracked-object list, direction-vector variable, and real-time limits, then click
**Apply Tracking Settings**:

- `Publish period`: snapshot period for the UI and `VariableManager`; default 50 ms. Use zero only when every encoder sample must publish.
- `Maximum camera age` and `Maximum encoder age`: maximum input age before health becomes stale.
- `Frame completion timeout`: maximum time for one frame to receive capture/detect encoder samples and detections.
- `Maximum queued frames` and `Maximum queued encoder samples`: backlog limits. New work is rejected with an overflow counter when full.

The UI's **Tracking status** line shows health, input age, queue depth, commit latency, and last fault. Persistent settings use `trackingN.Realtime.*`; session telemetry uses `Tracking.N.*`.

Tracking uses separate internal and publication rates. Every encoder sample updates the pose used for claims, so reducing UI publication frequency never makes claim coordinates stale.

## 10. Safe commissioning sequence

1. Validate the program and resolve every error.
2. Run vision only; verify coordinates, UIDs, confidence, and encoder values.
3. Dry-run the robot at Safe Z with the end effector and conveyor disabled.
4. Run one robot with the conveyor at low speed.
5. Verify release and complete behavior when stopping mid-cycle.
6. Enable additional workers and increase speed incrementally.

G-Script does not replace E-stop, STO, mechanical limits, or PLC safety.
