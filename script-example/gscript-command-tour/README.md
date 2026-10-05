# G-Script command tour

Start with `00-language.gcode`, `01-math.gcode` and `03-points-and-map.gcode`.
They execute without device commands and report PASS on success.

Read the [complete guide](../../docs/gscript-command-tour.md) for coverage,
CLI commands, isolated testing, and physical-hardware limitations.

Files marked **ISOLATED HARNESS ONLY** must not run in a live project.
Never manually set `Examples.Isolated`. The variable is not a sandbox switch.
`90-*` and `91-*` intentionally fail; the test runner checks these failures.

Run the whole suite from the repository root:

```powershell
python tools/run-tests.py --test gscript_runtime --test cli_integration --test gscript_analyzer --test control_plane --jobs 4
```
