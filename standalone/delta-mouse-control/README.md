# Delta Mouse Control

Standalone Python mouse controller for **Delta X 3**, derived from the Adaptive
Follower v2 in Delta X Software 2.0.0. The complete project lives in this folder;
it does not import the C++ application or require its build outputs.

- Hold LEFT and move: X/Y displacement follows mouse displacement.
- Hold LEFT and scroll: Z changes by the selected mm per notch.
- Adjust **XY sensitivity** to change robot travel per mouse count/pixel.
- Windows continuous capture uses Raw Input, without screen-edge limits.
- Release, Esc, loss of focus or a stalled UI stops new input and brakes.
- The default Simulator runs the same protocol/session/planner without hardware.

## Run

Python 3.10 or later is required. Tested on Windows with Python 3.12.10,
PySide6 6.9.1 and pyserial 3.5. GUI code is optional; the motion core uses only
the Python standard library.

In PowerShell, from this folder:

```powershell
.\launch.ps1 -Simulate
```

The launcher creates a local `.venv` and installs `requirements.txt` on first
use. If script execution is restricted, use the equivalent commands:

```powershell
python -m venv .venv
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
.\.venv\Scripts\python.exe run.py --simulate
```

Alternatively, install as a normal Python package:

```powershell
python -m pip install ".[gui]"
delta-mouse-control --simulate
```

`python run.py` works from another current directory when given an absolute
path. On Linux/macOS use the same Python commands with the appropriate virtual
environment interpreter; only pad mode is provided there. Those platforms have
not been hardware-validated.

## Operate

1. For a first check choose **Simulator**, then **Connect**. Use **Home robot**
   or check **Already homed** and click **Enable mouse**.
2. For hardware, disconnect the robot in other software, select **Serial**,
   choose its COM port and baudrate, and connect. Baudrate is actually passed
   to pyserial; 115200 is the Delta X 3 baseline.
3. Establish the home using **Home robot**. If already physically homed and idle,
   the checkbox plus **Enable mouse** adopts the current reported position.
   Reading `PositionOffset` by itself does not prove a successful physical home.
4. Hold LEFT inside the pad, move for XY and scroll for Z. Keep holding after a
   fast gesture if the remaining distance has not yet reached the target.
5. Release to cancel the unsent target. Wait for queued movement/braking to
   finish before starting another hold. **Disconnect** and window close drain
   movement and wait for `M205 S0` before closing the connection.

Default mapping: **0.15 mm/count**, **1 mm/notch**, **100 mm/s** speed limit;
100 raw counts requests 15 mm. In pad mode the unit is screen pixels. Raw counts
depend on mouse DPI, so they are not physical millimetres of mouse travel.
Sensitivity, wheel step, speed, port and baudrate are remembered using QSettings.
The connection is never reopened automatically on launch.

Acknowledged coordinates are completed commanded endpoints, not encoder
measurements. Motion + braking time is a host estimate. Prediction may aim up to
3 mm ahead; stopping/reversing may temporarily overshoot. Motion cannot keep up
when mapped mouse speed exceeds the speed limit. This control is not an
emergency stop. A communication fault latches the session: establish an empty
controller queue and a valid position before restarting the application.

## Project layout

```text
delta-mouse-control/
  pyproject.toml          Installable package, optional GUI/serial/test extras
  requirements.txt       Tested desktop dependency versions
  run.py / launch.ps1    Source launchers
  src/delta_mouse/       Independent core + optional desktop frontend
  examples/              Headless mouse, ordered path, existing connection adapter
  tests/                 Planner, protocol, lifecycle and UI regressions
  docs/                  Architecture, protocol, integration and validation
  AI_INTEGRATION.md       Starting point for the integrating AI/developer
  tools/package_source.py
  LICENSE / NOTICE / THIRD_PARTY_NOTICES.md
```

Start at [AI_INTEGRATION.md](AI_INTEGRATION.md) for reuse in another application.
GUI users need not modify Python code to operate the example application.

## Verify and package

```powershell
python -m pip install -e ".[gui,test]"
python -m pytest -q
python examples/headless_mouse.py
python examples/ordered_path.py
python run.py --smoke-test
python tools/package_source.py
python tools/verify_bundle.py
```

The packaging command creates `dist/delta-mouse-control-1.0.0-source.zip` and its
SHA-256 file. The ZIP includes source, docs, examples, tests and first-party
license notices, excluding environments, secrets, logs, caches and third-party
installed packages. It is a **source handoff**, not a frozen Windows executable.
The verification command extracts it to a temporary folder and runs the
headless example in isolated Python without any installed third-party packages.

For a GUI-free installation use `python -m pip install .` or `.[serial]`.
See [validation](docs/VALIDATION.md) for coverage and remaining hardware checks.
