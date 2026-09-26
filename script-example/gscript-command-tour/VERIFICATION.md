# Verification record — 2026-09-26

Environment: Windows, Qt 6.10.1 / MSVC, OpenCV 4.0.0.

## Automated execution

All 12 example files passed their isolated runtime expectations. The two
intentional-failure examples faulted for the expected reason without executing
the following assignment. Coverage inventory checks also passed.

Latest suite results (Qt totals include init/cleanup cases):

| Suite | Passed | Failed |
| --- | ---: | ---: |
| gscript_runtime | 34 | 0 |
| cli_integration | 3 | 0 |
| gscript_analyzer | 18 | 0 |
| control_plane | 14 | 0 |
| variable_manager | 10 | 0 |
| tracking_claim | 23 | 0 |
| plugin_contract | 4 | 0 |
| vision_protocol_python | 3 | 0 |

The updated desktop application compiled successfully. Runtime fixes discovered
by the examples cover mixed-operator precedence/associativity, comparisons after
function calls, the sendGcode alias, parenthesized clearObjects/deleteObject,
and parenthesized logMessage argument handling.

## Connected robot attempt — NOT PASSED

The already-open desktop application (older executable) accepted
`20-robot-readonly.gcode` through the real CLI. Position and ROBOTMODEL waits
received responses. FirmwareVersion then timed out after 3000 ms; the CLI
reported failure (exit 1) and the worker entered Faulted.

Run ID: `c0961321-87e2-4f5d-bdf8-94f037247f21`.

No Home, motion, or tool-output command was included in the probe. The existing
timeout/fault path can send safety-stop commands. Do not automatically reset
the cell or replay the probe. Inspect the robot and acknowledge/reset the cell
through the normal operator workflow before another live run.

The local Delta X 3 firmware source recognizes FirmwareVersion, but that does
not establish which firmware is flashed on the attached robot. This attempt
does not establish a root cause or validate physical motion, vision, conveyor
tracking, encoder feedback, or picking.

Repository history later confirmed that the standalone `FirmwareVersion` query
was introduced by firmware commit `668a2b9`. Older supported branches expose
version information only through the multiline `Infor` response. The portable
read-only example now requires only `Position` and `ROBOTMODEL`; firmware-version
discovery is documented as version-dependent rather than a G-Script capability.

The first compatible-probe run completed and identified `MODEL:DELTA_X_3`.
Logging the whole Position value appeared blank because VariableManager correctly
normalized the numeric CSV reply to `QVector3D`, whose generic QVariant string
conversion is empty. The example was updated to log `.X`, `.Y`, and `.Z`.

After fixing `PlogMessage` to resolve vector members and deploying the rebuilt
application, the final connected-robot probe passed on `robot0`. It reported
Position `X=0`, `Y=0`, `Z=-291.28`, model `MODEL:DELTA_X_3`, emitted
`PASS robot queries`, and finished `Completed` with `success: true`.

Final run ID: `a4c0cdff-b9b2-4dc9-965e-558ed9361f34`.

This validates the G-Script/CLI read-response path against the attached robot.
It still does not validate homing, physical movement, outputs, encoder scaling,
camera detection, conveyor synchronization, or picking safety.

## Updated desktop application — PASSED software-only runs

After the operator closed the application, the updated executable was deployed
to `build/ui-review-release/DeltaRobotSoftware.exe`, its hash was checked against
the build output, and the application was reopened. The previous executable was
retained as a timestamped `.before-command-tour-*.bak` backup. No process was
forcibly terminated.

The following bundled files then ran through the actual desktop CLI endpoint
in `project0/thread0`, each returning exit code 0, `Completed`, `success: true`
and its expected PASS message:

| File | Run ID |
| --- | --- |
| `00-language.gcode` | `aca8239b-4274-4e05-8d1c-a17717fdbb2b` |
| `01-math.gcode` | `ec405d7c-365b-476b-8d81-4693a4ce33e3` |
| `03-points-and-map.gcode` | `e2c7b1ae-029f-4fc4-8725-287a78c355a5` |

These runs did not use `--allow-unhomed` and contained no device commands.
The robot probe was not replayed; the earlier FirmwareVersion timeout remains
unresolved and physical operation remains unverified.
