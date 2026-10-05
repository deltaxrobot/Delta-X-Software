# G-Script command tour

These executable examples exercise the current built-in G-Script language.
They are a test suite, not one production program: calibration, expected faults,
and simulated motion must not be mixed into a live picking cycle.

## Open an example

In the source checkout, open `script-example/gscript-command-tour/`.
Windows release packages also include the files in `gcode/GScript Command Tour/`.
Use the G-Script file browser or Open to load a file, then Run.

Start with **00-language.gcode**, **01-math.gcode**, and
**03-points-and-map.gcode**. These contain no device or camera commands; they
only write `Examples.*` variables in the current project. A successful run
finishes with a `PASS` message and sets the corresponding `Examples.*Passed`
variable to `1`. Existing variables with these names are replaced.

With the desktop application open, the same files can run through the CLI:

```powershell
.\delta-x-cli.exe status
.\delta-x-cli.exe run ".\script-example\gscript-command-tour\00-language.gcode" --timeout 15
.\delta-x-cli.exe run ".\script-example\gscript-command-tour\01-math.gcode" --timeout 15
.\delta-x-cli.exe run ".\script-example\gscript-command-tour\03-points-and-map.gcode" --timeout 15
```

Use the project/thread reported by `status` if they differ from `project0/0`.
Save any unsaved editor content first. See [CLI usage](cli.md).

## Files and coverage

| File | Examples | Run mode |
| --- | --- | --- |
| `00-language.gcode` | Variables, strings, arithmetic, comparisons, boolean operators; IF/THEN/ELIF/ELSE; FOR/TO/STEP, FOR EACH/IN; WHILE, BREAK, CONTINUE; SWITCH/CASE/DEFAULT; FUNCTION/LOCAL/RETURN; LABEL/JUMP; N/GOTO and O/M98/M99; assert, waitUntil, delay, logMessage | Software only |
| `01-math.gcode` | sin, cos, tan, atan, atan2, sqrt, abs, round, floor, ceil, min, max, pow, log, log10, exp | Software only |
| `02-cloud-mapping.gcode` | All 25 callable cloudPoint functions: calibration CRUD, transforms, confidence/error, validation, grid build, save/load, export/import, point getters | Isolated runner only |
| `03-points-and-map.gcode` | 2D/3D points, component access, affine `.Map(...)` | Software only |
| `10-device-routing.gcode` | SELECT, explicit robot/conveyor/encoder/slider/device routing, raw G/M forwarding, bracket substitution, send/sendGcode, SYNC, legacy syncConveyor/stopSyncConveyor | Isolated runner only; contains motion and outputs |
| `11-vision-tracking.gcode` | pauseCamera, captureCamera, resumeCamera, captureAndDetect, updateTracking, claimObject, releaseObject, completeObject | Isolated runner only |
| `12-object-primitives.gcode` | addObject, clearObjects, deleteFirstObject, deleteObject | Isolated runner only; changes object lists |
| `13-plugin.gcode` | Registered plugin primitive and result assignment | Isolated runner with `test.runtime` provider |
| `14-legacy-area-query.gcode` | GetObjectInArea on X and Y | Isolated runner only |
| `20-robot-readonly.gcode` | Position and model queries via send; replies stored in variables and printed | Connected robot0; no motion or output commands |
| `90-expected-assert-failure.gcode` | Assertion failure and prevention of subsequent statements | Isolated runner only; intentionally faults |
| `91-expected-wait-timeout.gcode` | Condition timeout and prevention of subsequent statements | Isolated runner only; intentionally faults |

Coverage includes all 30 registered language keywords, all 20 built-in M98
primitive names, 16 math functions and 25 callable cloud-point functions.
Aliases with underscores or numbered tracking suffixes are compatibility
spellings, not separate capabilities. Arbitrary firmware G/M commands and
third-party plugin commands are **not** exhaustively covered: those depend on
the installed firmware/plugin and require their own commissioning tests.

`syncConveyor` and `stopSyncConveyor` are legacy flags, not a working substitute
for tracking compensation. `GetObjectInArea` does not reserve an object for a
robot. Use the claim/release/complete protocol for multi-robot ownership.

## Run the full isolated suite

From a development checkout with its normal Qt/OpenCV build dependencies:

```powershell
python tools/run-tests.py --test gscript_runtime --test cli_integration --test gscript_analyzer --test control_plane --jobs 4
```

The runtime test reads the actual example files, uses the real parser and
execution worker, and checks assertions, dispatched commands, signal arguments,
completion state and failure behavior. Cloud mapping uses the real mapper in
a temporary directory. The test fixture owns a separate variable namespace.
The CLI integration test also executes the language and math files through the
application's real CLI bridge and verifies that no hardware command is sent.

The isolated runtime fixture constructs **no serial port, socket connection, or
DeviceManager**. It supplies deterministic asynchronous device, camera and
tracking replies. It registers the test plugin provider only for the test.
The two expected-failure files pass the test only when execution faults with
the expected reason and never reaches the next assignment.

**Never set `Examples.Isolated = 1` manually in a live project.** It is a guard
against accidental execution, not a sandbox switch. Setting the variable does
not disconnect devices or protect calibration. In particular, do not run the
expected-failure examples in an operating cell: fault cleanup may request Stop.

## What a passing test proves

It proves the checked language results and software dispatch/wait contracts.
It does not prove camera accuracy, encoder scaling, physical picking success,
robot motion limits, actuator wiring, or real-time synchronization. The
read-only robot example verifies communication only. No-motion examples do
not replace an independent physical safety system.

`FirmwareVersion` is a raw firmware query, not a G-Script language command. It
was added in later Delta X 3 firmware and older supported firmware may not
respond. The compatibility probe therefore uses `Position` and `ROBOTMODEL`.
The variable manager normalizes a numeric comma-separated Position response to
a vector, so the example prints its `.X`, `.Y`, and `.Z` components separately.

For commissioned conveyor picking, continue with
[multi-robot conveyor sorting](multi-robot-conveyor-sorting.md).
