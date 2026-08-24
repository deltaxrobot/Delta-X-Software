# Test suite

Run the complete suite from the repository root:

```powershell
python tools/run-tests.py
```

The runner locates Qt/MSVC, creates out-of-source builds under `build-tests/`,
executes every QtTest binary, then runs the DXV1 Python protocol tests. Use
`python tools/run-tests.py --help` for filtering and CI options.

The `filter_worker` suite covers the image-filter boundary independently of the
UI thread, including malformed settings and blur-kernel normalization.

The `device_state` suite guards the cross-thread device snapshot contract so
status reads never create or touch a serial/socket object from the wrong thread.

The `plugin_contract` suite validates the versioned SDK metadata independently
of any vendor camera runtime.

The `plugin_manager` suite builds a real API v2 fixture and verifies discovery,
capabilities, commands, project-scoped settings, disabled IDs, duplicate
rejection, missing directories, and unload on every supported operating system.

The industrial camera runtime test is executed when a built plugin is available.
Use `--require-industrial-plugin` in release validation when skipping it must fail.

`tests/tests.pro` is also provided for IDE discovery and aggregate qmake builds;
the Python runner remains the canonical build-and-test entry point.
