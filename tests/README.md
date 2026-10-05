# Test suite

Run the complete suite from the repository root:

```powershell
python tools/run-tests.py
```

The runner locates Qt/MSVC, creates out-of-source builds under `build-tests/`,
executes every QtTest binary, then runs the DXV1 Python protocol tests. Use
`python tools/run-tests.py --help` for filtering and CI options.

The `mouse_jog` suite exercises jerk-limited look-ahead, corner speeds, ordered
paths, a two-command FIFO, delayed acknowledgements, low-feed time budgeting,
exclusive ownership, fault quarantine, XY/wheel input, reversal/braking and
dialog-close cleanup. Continuous-capture tests inject relative input to request
120 mm across multiple planning horizons and check focus/Esc and capture-failure
cleanup. They do not exercise native Windows cursor capture. The suite uses a
timed controller emulator and never moves hardware.
The live-follower tests measure acknowledged-endpoint lag for moving straight
and curved targets and check prediction expiry, bounded feed, final settling,
unsplit terminal braking and release while velocity prediction is active.
Live-follow settling is checked against `Limits::minimumLength` (0.201 mm),
including a stable empty queue after prediction expires. Sub-minimum stationary
corrections are intentionally not emitted; representable fixed-path endpoints
retain their stricter position checks.

The `phone_camera` suite tests the local HTTPS server with ephemeral credentials:
pairing authorization, single-phone ownership, correlated JPEG delivery, stale
frames, size limits, timeout and session revocation. It needs a Qt TLS backend
and OpenSSL on PATH for test certificate generation; it never modifies trust
stores or uses a physical phone. Actual mobile browser permissions and certificate
installation still need a phone acceptance test.

The `filter_worker` suite covers the image-filter boundary independently of the
UI thread, including malformed settings and blur-kernel normalization.

The `device_state` suite guards the cross-thread device snapshot contract so
status reads never create or touch a serial/socket object from the wrong thread.

The `plugin_contract` suite validates the versioned SDK metadata independently
of any vendor camera runtime.

The `block_programming` suite verifies the block catalog, templates, nested
document round trips, input bounds, structural/process diagnostics, and that
generated templates pass the real G-Script analyzer.

The `plugin_manager` suite builds real API v2 and v3 libraries. It verifies
backward-compatible discovery, permissions, lifecycle, G-Script/device/service
registration, events, commands, project-scoped settings, disabled IDs,
duplicate rejection, missing directories, reverse cleanup, and unload on every
supported operating system. It also loads the bundled Block Programming plugin,
creates its native panel, and exercises its catalog/template/compile commands.
`gscript_runtime` also executes a dynamically
registered primitive and stores its result in a project variable.

The [G-Script command tour](../docs/gscript-command-tour.md) is executable test
data in `script-example/gscript-command-tour/`. `gscript_runtime` runs all 12
files with isolated variables, temporary mapping files and mocked asynchronous
hardware responses. It also checks example coverage against the registered
keywords, M98 targets and numeric-function dispatch table. `cli_integration`
runs the software-only language/math files through the real application bridge.

The industrial camera runtime test is executed when a built plugin is available.
Use `--require-industrial-plugin` in release validation when skipping it must fail.

`tests/tests.pro` is also provided for IDE discovery and aggregate qmake builds;
the Python runner remains the canonical build-and-test entry point.

## UI regression checks

The Robot panel tests also exercise `RobotPanelLayout` without device objects:
Control/I/O/Setup at 380, 480 and 720 logical pixels; 3 and 6 axes; both themes;
no horizontal overflow or jogging/step-selector overlap; unchanged I/O parent
lookup and no Home/jog/output activation while arranging or navigating the UI.

For native visual inspection, launch the built `tst_ui_theme` executable with
`--robot-preview` (without `QT_QPA_PLATFORM=offscreen`). It opens only the Robot
form, with no device objects, project persistence, or hardware command bindings.
This preview does not replace integration checks in the full application.

The `ui_theme` suite covers Dark and Light control geometry, semantic button
contrast, disabled states, SVG indicator resources, syntax colors after theme
switching, jogging bounds, and navigation text width. It loads the real Designer
forms plus the real settings panel and generic dialog. Device/canvas/editor
widgets in the form preview use lightweight stand-ins: no robot, encoder,
camera, project runtime, or motion worker is started. Settings use a separate
Qt test-mode application identity, not the user's Delta X configuration.

`cli_transport` covers fragmented messages, malformed/oversized requests,
streaming results and exclusive endpoint ownership. `cli_integration` loads
the actual RobotWindow with isolated settings, runs software-only programs,
and checks completion, Stop, disconnect cancellation, busy-worker rejection
and unsaved editor protection. No motion commands are used.

To also generate preview images on Windows:

```powershell
$env:QT_QPA_PLATFORM = 'offscreen'
$env:DELTA_X_UI_SNAPSHOTS = "$PWD/build/ui-audit"
python tools/run-tests.py --test ui_theme
```

Run the same test with `QT_SCALE_FACTOR=1.25` and `1.5` in separate processes,
and use separate snapshot directories when comparing output. Unset these
environment variables before launching the interactive application. The test
runner is also supported from other shells using their normal environment
variable syntax.

These previews cover the Program, Vision, Calibration, Drawing, device, and
main shell forms, including settings categories and the image filter dialog.
They also verify navigation icon colors after live theme/selection changes and
readable foreground colors on the settings color swatches. They do not instantiate the
production workspace controllers. They cannot verify dynamic plugin canvases,
camera streams, native title bars, multiple-monitor placement, interactive
splitters, or physical jogging. Validate those manually with hardware outputs
disconnected before approving a release.

## Drawing regression suite

`python tools/run-tests.py --test drawing --jobs 4` covers mm coordinates,
mouse-drag completion, undo/redo, view transforms, document validation,
PNG/SVG conversion, raster row separation, sloped-plane clearance, G-code
feed rates, laser-off ordering, settings round-trips and panel geometry.
These tests never connect to or move a robot.
