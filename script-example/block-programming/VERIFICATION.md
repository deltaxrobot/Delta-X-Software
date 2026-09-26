# Block Programming verification — 2026-09-26

Environment: Windows, Qt 6.10.1 / MSVC. The qmake test harness uses OpenCV
4.0.0; the current CMake desktop runtime uses OpenCV 4.11.0.

## Results

| Check | Result |
| --- | --- |
| Block catalog, defaults, templates, nesting, JSON round trip and validation | 12 passed, 0 failed |
| Plugin loading, permissions, host services and responsive panel integration | 13 passed, 0 failed |
| Plugin SDK contract | 4 passed, 0 failed |
| DXV1 protocol companion tests | 3 passed, 0 failed |
| Generated Software Self Test through the live desktop CLI endpoint | Completed, success true |

End-to-end run ID: `c98f28e7-05be-40a5-8ba4-e3735d249fdb`.

The user-requested repeat run also completed successfully with run ID
`5fabb536-b6f2-4c43-90ca-c5a6e8472518` after the fixture/compiler test passed
10/10 again.

The panel integration test loads the actual plugin DLL, constructs and displays
its native widget at a supported narrow size, verifies that toolbox/canvas and
inspector remain usable, selects **Software self-test** through the template
combobox, and checks the workspace, G-Script preview, diagnostics and Load/Run
button state.

The `.dxblocks` fixture is parsed by the real block compiler and its output must
exactly match `Software Self Test.gcode`. That generated file then ran in the
open Delta X Software project. It logged three iterations and
`PASS block programming`, exercised the condition wait and cooperative delay,
and finished successfully without `--allow-unhomed`.

The self-test contains no robot, device, conveyor, encoder, camera, tracking or
output command. It does not validate physical templates or cell commissioning.

## Connected robot motion attempt

The block compiler initially emitted unbracketed motion expressions such as
`X#Target.X`. This could leak a variable name to firmware instead of resolving
it. Motion generation now always emits bracketed parameters such as
`X[#Target.X]`, and regression tests enforce this contract.

The first connected motion run was rejected before movement because the
requested `Z=-281.28` was above the Delta X 3 workspace. After changing the
direction, the robot accepted the 10 mm downward move from `-291.28` to
`-301.28`. Firmware then rejected a return command to the reported Home-edge
coordinate `-291.28`; the robot remained at the accepted lower position. The
fixture now requires an interior start range of `-430 < Z < -295` before any
motion, so it cannot start at the ambiguous Home boundary or without 10 mm of
lower clearance.

After the operator reset the software cell fault, the generated block program
completed a physical round trip successfully. The connected Delta X 3 moved
10 mm downward, waited 500 ms, returned to its measured starting position, and
passed the final Z return-error assertion (`< 1 mm`). The successful live run ID
was `73f2e53d-69ba-4820-a3cd-f6cc2648e46f`.

## Connected 50-cycle block program

`Delta X 50 Cycle Example.dxblocks` is a native block document matching the
requested Home, counter and repeated X/Z motion scenario. It generates six
linear moves per cycle for 50 cycles at `F2000` and `A20000`, then returns Home.
The compiler output is compared byte-for-byte with its checked-in G-Script in a
regression test.

Two runtime defects found during commissioning were fixed and covered by tests:
quoted semicolons are no longer treated as comments, and underscore aliases in
M98 function names no longer remove underscores from argument identifiers such
as `#robot0.HOME_Z`.

The connected Delta X 3 completed all 50 physical cycles and the final Home.
Run ID: `49e2bbe8-57d1-46c4-856c-03cbaaece3f9`. A post-run read-only query
confirmed `(X, Y, Z) = (0, 0, -291.28)` and `MODEL:DELTA_X_3`.

The CLI now exposes UI-equivalent `connect-robot` and an explicitly confirmed
`reset-fault --confirm-safe`. These commands were used successfully before the
physical run, eliminating manual button clicks while retaining an operator
safety acknowledgment.

Direct native-window automation was unavailable because the Computer Use
surface returned no Windows applications. No visual mouse/drag pass was claimed;
widget behavior and responsive geometry were checked through QtTest instead.
