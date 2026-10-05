# G-Script User Guide

G-Script is Delta X Software's orchestration language for robots, conveyors, encoders, cameras, tracking, and general I/O. The robot controller remains responsible for motion interpolation, and an independent controller/PLC/safety circuit remains responsible for E-stop, STO, guards, and collision risk.

The canonical language and runtime references are:

- [`docs/gscript-runtime.md`](docs/gscript-runtime.md): operator workflow, variables, device commands, waiting, faults, and multi-robot examples.
- [`docs/gscript-design.md`](docs/gscript-design.md): analyzer, runtime state model, editor behavior, and language conventions.
- [`docs/multi-robot-conveyor-sorting.md`](docs/multi-robot-conveyor-sorting.md): calibration, tracking, ownership, and commissioning of a shared conveyor cell.
- [`GScript_Documentation.html`](GScript_Documentation.html): bundled in-application help.

## Basic syntax

```gcode
; Comment
SELECT robot0
#Speed = 500
G28
G01 X100 Y200 Z-80 F[#Speed]
M98 Pdelay(200)
```

Variables begin with `#` and are project-scoped. Use `LOCAL` inside a function for temporary values.

```gcode
FUNCTION Clamp(value,minimum,maximum)
    IF #value < #minimum THEN RETURN #minimum
    IF #value > #maximum THEN RETURN #maximum
    RETURN #value
ENDFUNCTION
```

## Control flow

```gcode
IF #Confidence >= 0.80
    #Bin = 1
ELIF #Confidence >= 0.60
    #Bin = 2
ELSE
    #Bin = 0
ENDIF

FOR #i = 0 TO 9 STEP 1
    IF #i == 5 THEN CONTINUE
ENDFOR

WHILE #Counter < 100
    #Counter = #Counter + 1
ENDWHILE
```

Named `LABEL/JUMP` loops are preferred for new source. Numbered `N` lines and `GOTO` remain available for compatibility.

## Device commands

Address the device explicitly in production code:

```gcode
robot0 G01 X100 Y20 Z-80 F500
conveyor0 M311 S100
encoder0 M317
device0 M42 P1
```

Use `Psend` when a response and timeout are required:

```gcode
M98 Psend(encoder0,"M317",#EncoderReply,1000)
M98 PwaitUntil(#Vacuum.R0.OK == 1,500,10,"robot0: vacuum timeout")
M98 Passert(#Cell.Ready == 1,"Cell is not ready")
```

## Multi-robot tracking

Use one vision loop for a tracking ID and one worker per robot:

```gcode
; Vision thread
LABEL VISION_LOOP
M98 PcaptureAndDetect(0)
M98 Pdelay(10)
JUMP VISION_LOOP
```

```gcode
; Robot worker
SELECT robot0
#Owner = "robot0"
M98 PclaimObject(0,#Target,#Owner,-180,180,300,450,-1,30000)

IF #Target.Found == 1
    G01 X[#Target.X] Y[#Target.Y] Z-80 W[#Target.A] F500 SYNC
    M03
    M98 PwaitUntil(#Vacuum.R0.OK == 1,500,10,"vacuum timeout")
    M98 PcompleteObject(0,#Target.UID,#Owner)
ENDIF
```

Call `releaseObject` when abandoning a part before pickup. Never write `IsPicked` directly, because doing so bypasses ownership and can let two workers select the same UID.

## Validation and execution

`Validate` performs static analysis only. `Run` repeats preflight before any device command. Errors under `GS1xxx` block execution; `GS2xxx` are warnings; runtime failures use `GSR1xxx`. During execution, the editor reports `Running`, `WaitingForDevice`, `WaitingForTimer`, `WaitingForCondition`, `Completed`, `Faulted`, or `Stopping`.

Commission with vision only, then dry-run each robot at Safe Z, then enable one real worker at low conveyor speed. Enable additional workers only after mapping, UID stability, ownership, stop behavior, and physical safety controls have passed acceptance tests.
