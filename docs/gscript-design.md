# G-Script Design for Delta X Software

## 1. Goals

G-Script is the cell orchestration layer. It does not replace the robot firmware's motion interpolation or any safety circuit. A production program must:

- read like a manufacturing procedure;
- pass static analysis before a command reaches a device;
- wait for real acknowledgements instead of guessing with fixed delays;
- stop in a controlled manner when a device, vision source, encoder, or object ownership fails;
- let several robot threads share one tracking map without claiming the same UID;
- remain compatible with programs that use `N`, `GOTO`, `O...`, `M98`, and `IF ... THEN`.

## 2. Backend architecture

```text
Editor / file / remote API
          |
          v
 GScriptAnalyzer (read-only)
   | diagnostics: GSxxxx
   | no error
   v
 GcodeScript runtime
   | state + current line + timeout
   +--> robot / conveyor / encoder / device
   +--> camera + tracking handshake
   +--> project-scoped VariableManager
```

`GScriptAnalyzer` never controls hardware. It validates line numbers, delimiters, strings, `IF/FOR/WHILE/SWITCH/FUNCTION` structure, labels, `GOTO` targets, `SELECT`, `M98` targets, device names, and canonical primitive argument counts. The UI and runtime invoke the same analyzer, so a socket or API command cannot bypass preflight.

The runtime has an explicit state model:

```text
Idle -> Validating -> Running <-> WaitingForDevice
                       |   ^      WaitingForTimer
                       |   ^      WaitingForCondition
                       |   |             |
                       +----> Stopping <-+
                       +----> Completed
                       +----> Faulted
```

- `Running`: executes a local statement or prepares the next device command.
- `WaitingForDevice`: waits for the matching device acknowledgement.
- `WaitingForTimer`: uses an asynchronous timer; Stop remains responsive.
- `WaitingForCondition`: reevaluates a runtime expression; timeout faults the program and Stop remains responsive.
- `Faulted`: validation, timeout, tracking health, or ownership failed.
- `Stopping`: cancels the run and asks the active adapter to stop its device.

Every run publishes diagnostics, state, current line, and final result. Running state is atomic because the UI and interpreter live in different threads.

## 3. Language conventions

A line has the following form:

```gcode
[N<number>] <statement> [; comment]
```

Conventions for new programs:

- Write commands in uppercase and use meaningful variables such as `#R0SafeZ`.
- Prefer named `LABEL/JUMP` loops; use `GOTO N` only for compatibility.
- Prefer block `IF condition ... ENDIF`; retain `IF condition THEN statement` for short statements.
- Select the worker device with `SELECT robot0` at the start of each thread.
- Declare poses, claim zones, and speeds at the start of a worker instead of scattering numeric literals.
- Never write `.IsPicked` directly; use claim, release, and complete.

Canonical tracking primitives:

```gcode
M98 PcaptureAndDetect(trackingId)
M98 PclaimObject(trackingId,result,owner,minX,maxX,minY,maxY,typeFilter,leaseMs)
M98 PreleaseObject(trackingId,uid,owner)
M98 PcompleteObject(trackingId,uid,owner)
```

Canonical device and guard primitives:

```gcode
M98 Psend(deviceId,command,responseVariable,timeoutMs)
M98 Passert(condition,message)
M98 PwaitUntil(condition,timeoutMs,pollMs,message)
```

The runtime leases a physical device while waiting for its response. Two threads cannot simultaneously own the same `robotN`, `conveyorN`, `encoderN`, `sliderN`, or `deviceN`. Device errors and timeouts fault the owning thread immediately.

`claimObject` writes a snapshot into `#result`. Check `#result.Found` before using its pose. Call `completeObject` only after the pick has been confirmed. Call `releaseObject` when abandoning an object before the pick. An expired lease releases the object automatically.

### Realtime rates and backpressure

Tracking has separate internal and publication rates. Every encoder sample updates the internal pose used by association and claims. The UI and `VariableManager` receive snapshots at `PublishIntervalMs` to avoid copying and emitting thousands of variables per second. Frame commits, claims, releases, and completions still force immediate publication.

Frame and encoder-read queues are bounded. When producers exceed processing capacity, the new request is rejected with a diagnostic and telemetry update instead of creating an unbounded backlog. `Tracking.N.*` exposes vision and encoder age, queue depth, overflow counts, commit latency, publication duration, and coalesced publication counts.

## 4. Multi-robot worker model

Avoid a monolithic script for the whole cell. Use one vision producer and one worker per robot:

| Thread | Responsibility | Device/data source |
|---|---|---|
| `vision0` | Capture, detect, and commit frames | Camera, encoder, tracking 0 |
| `robot0` | Claim by zone/type, pick, and place | Robot 0 |
| `robot1` | Claim by zone/type, pick, and place | Robot 1 |

The vision thread establishes the frame cadence with `PcaptureAndDetect`. Robot workers are independent and coordinate only through tracking ownership. One worker can therefore stop without disrupting the vision loop.

Runnable examples are in `script-example/multi-robot-sorting/`.

## 5. Editor UI/UX

The editor follows one consistent workflow:

1. Debounced validation runs 350 ms after an edit.
2. Errors and warnings are highlighted and listed in Problems.
3. Double-clicking a diagnostic navigates to its source line.
4. `Validate` performs analysis only and never sends a device command.
5. `Run` always performs preflight. An error prevents the Home warning and all G-code transmission.
6. The editor locks while running so source text and line numbers cannot change; the active line is highlighted.
7. The status bar shows `Running`, `Waiting`, `Completed`, or `Faulted`, plus cursor position.
8. `Safe line run` is a commissioning mode. It locks the document and runs one primitive line; structural statements such as `IF`, `ENDIF`, or `FUNCTION` cannot run alone.
9. Autocomplete shares the canonical primitive/device catalog and includes variables from the active project. `Ctrl+Space` opens it explicitly.
10. Signature help identifies the active `M98` primitive and argument without invoking hardware.
11. Problems, realtime Watch, and Threads tabs provide analysis, scoped variable inspection, and thread state. Watch infers variables from source while excluding comments and strings; operators can pin additional telemetry.
12. The wizard creates vision or robot skeletons from unit-tested templates. Generated source still passes through the analyzer before Run.

Stable diagnostic ranges support documentation and service procedures:

- `GS1xxx`: syntax or structural errors that block execution;
- `GS2xxx`: quality or compatibility warnings that allow execution;
- `GSR1xxx`: runtime state faults.

## 6. Safety boundary

Preflight and timeout handling improve operational behavior but are not safety-rated. E-stop, guard doors, STO, mechanical limits, lost air/vacuum, and robot interference zones belong in the controller, PLC, or safety circuit.

Before running an example:

1. Validate with no errors.
2. Run vision only and inspect UIDs and encoder values.
3. Dry-run each robot at `SafeZ` with the gripper disabled.
4. Run one robot with a slow conveyor.
5. Enable the remaining workers and increase speed in controlled steps.

## 7. Evolution path

The analyzer, editor services, and interpreter are separated deliberately. Autocomplete, signature help, Watch, and templates do not modify runtime semantics. The next language-level evolution is a typed AST/IR shared by the interpreter, formatter, and simulator. The current compatibility and preflight layer supports that migration without breaking existing script libraries.
