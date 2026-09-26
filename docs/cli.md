# Command-line G-Script execution

`delta-x-cli` runs a UTF-8 G-code/G-Script file through an **already open Delta X
Software project**. The application owns device connections, variables,
calibration, camera, tracking and plugins. CLI, Code Run and Block Run share
launch checks and the `GcodeScript` worker, including command response handling.
This version is a local desktop companion, not a standalone headless runtime.

## First run

Open Delta X Software and select your project. Open PowerShell in the installed
application directory. The CLI can request the same automatic robot connection
used by the UI:

```powershell
.\delta-x-cli.exe status
.\delta-x-cli.exe connect-robot --project project0
.\delta-x-cli.exe run "D:\programs\pick-and-place.gcode" --project project0 --thread 0
$LASTEXITCODE
```

On Linux/macOS, use `./delta-x-cli` and normal platform paths. Both processes
must run under the same OS user account. Project and thread default to `project0`
and `0`. `status` lists actual runtime project IDs, which may differ from renamed
tab labels, and existing thread indexes.

`status --json` also reports `cellState`, `cellFaultReason` and
`robotConnected`. Connection is asynchronous: after `connect-robot`, wait until
`robotConnected` is true or issue a harmless read-only device query before
starting motion.

After inspecting the E-stop, guards, work area, robot controller, conveyor and
end effector, a software cell fault can be acknowledged without clicking the UI:

```powershell
.\delta-x-cli.exe reset-fault --project project0 --confirm-safe
```

The explicit `--confirm-safe` flag is required. This command only resets the
Delta X Software cell supervisor; it does not clear a hardware E-stop, controller
alarm or unsafe device state.

Try the bundled software-only example first:

```powershell
.\delta-x-cli.exe run .\script-example\cli-smoke.gcode
```

It calculates a variable, waits briefly and asserts the result. It contains no
robot, conveyor, encoder, camera or output commands.

## Results and stopping

The terminal prints the accepted run ID, execution states, runtime messages and
final result. `run` waits for execution to finish, not merely for acceptance.
Use `--json` for one JSON object per line and `--timeout 120` for a 120-second
overall deadline. Default timeout `0` waits indefinitely; runtime device timeouts
remain unchanged.

Press **Ctrl+C** to request Stop and wait for confirmation, or use another terminal:

```powershell
.\delta-x-cli.exe status
.\delta-x-cli.exe stop RUN_ID
```

Replace `RUN_ID` with the ID from `accepted` or `status`. `stop` acknowledges
submission; the original `run` command reports actual completion. It targets
only an active CLI run. The GUI Stop control also remains available.
Closing/killing the controlling CLI connection requests the existing software
Stop behavior; this is not hardware E-stop. If connection is lost, inspect the
application before retrying because some commands may already have executed.
The CLI never automatically replays a run.

## Shared behavior and limits

- Full source runs from the beginning, preserving loops, variables, macros,
  device selection and asynchronous waits. Implicit devices use the project's
  selected defaults, just like Run. Prefer explicit device names in reusable files.
- Invalid source, a cell that disallows automation, and busy/reserved workers
  reject the run. Two CLI/GUI/Block Run requests cannot reserve the same worker.
- Unsaved text in the selected editor is protected. Save it or use another
  existing thread. Accepted CLI source appears as **CLI program** when selected.
  Neither its original file nor the previous editor file is overwritten. Saving
  later asks for a new file name.
- The existing GUI Home warning is preserved. CLI returns an error instead of
  opening a hidden dialog. `--allow-unhomed` explicitly accepts the same **Run
  Anyway** choice; it does not home the robot or bypass cell faults. This check
  uses the GUI's legacy Z-position heuristic, not a firmware homed flag.
- Files must be non-empty UTF-8 (optional BOM), at most 2 MiB. Encoded requests
  must fit in 4 MiB. The local endpoint is restricted to the current OS user;
  no TCP port or remote-command setting is required.
- With multiple application instances, the first endpoint owner receives CLI
  requests; a second instance cannot replace it. `status` shows its projects.
- Robot auto-connect and explicitly confirmed software-fault reset are available.
  Project creation, detached runs and a standalone headless service are not.

## Exit codes

| Code | Meaning |
| --- | --- |
| 0 | Program completed successfully, or status/stop request succeeded |
| 1 | Runtime failure or stop from another control |
| 2 | Invalid arguments/file or application rejected the request |
| 3 | Connection/protocol failure or completion could not be confirmed |
| 124 | Deadline expired; accepted run confirmed Stop |
| 130 | Ctrl+C interruption; accepted run confirmed Stop |

Before acknowledgment, interruption closes the connection and the server
requests Stop for any run it accepted. Inspect the application if the result is
uncertain. Forced OS termination may produce an OS-specific exit code.

## Building and testing

The root CMake build includes `delta-x-cli` by default and installs it in `bin`.
The console target only depends on Qt Core and Network. On Windows it shares
the application's deployed Qt/MSVC runtime. For legacy qmake, build `cli/cli.pro`
in a separate directory using the same Qt kit, then copy `delta-x-cli.exe` next
to the deployed application executable.

```sh
cmake --build --preset developer-release --target delta-x-cli
python tools/run-tests.py --test cli_transport --test cli_integration --test gscript_runtime
```

Integration tests use temporary settings and software-only scripts with the
real application composition. They do not commission physical hardware.
