# Delta X Software

Delta X Software is a comprehensive control and programming platform for Delta robots.

[![CI](https://github.com/deltaxrobot/Delta-X-Software/actions/workflows/ci.yml/badge.svg)](https://github.com/deltaxrobot/Delta-X-Software/actions/workflows/ci.yml)

> **License:** first-party source and documentation are Apache-2.0. Historical
> camera SDK/model files retained in some local worktrees are quarantined and
> must not be included in public release artifacts until their redistribution terms are verified. See
> [third-party notices](THIRD_PARTY_NOTICES.md) and the
> [redistribution audit](docs/third-party-audit.md).

Contributor entry points: [contribution guide](CONTRIBUTING.md),
[architecture](docs/architecture.md), [development guide](docs/development.md),
[cross-platform setup](docs/platform-setup.md), [plugin system](docs/plugin-system.md),
[block programming](docs/block-programming.md), [Drawing](docs/drawing.md), [UI style guide](docs/ui-style-guide.md),
[release process](docs/releasing.md), [security policy](SECURITY.md), and
[governance](GOVERNANCE.md).

## Quick start

The repository provides one entry point for Windows, Ubuntu, and macOS:

```bash
python tools/bootstrap.py doctor
python tools/bootstrap.py all
python tools/bootstrap.py run
```

The doctor reports missing dependencies and platform-specific installation
instructions. See the [cross-platform setup guide](docs/platform-setup.md) for
clean-machine setup, packaging, device permissions, and platform limitations.

Run a G-code file through an open project's connected devices with
`delta-x-cli run program.gcode --project project0 --thread 0`.
`delta-x-cli status` lists projects, workers, cell state and robot connection.
Use `connect-robot` for UI-equivalent auto-connect and `reset-fault --confirm-safe`
after an operator safety check. See the [CLI guide](docs/cli.md)
for Windows commands, results, Stop and build instructions.

Learn and test the built-in language with the [G-Script command tour](docs/gscript-command-tour.md):
software-only examples, isolated device-contract tests, and a read-only robot probe.

Use [Mouse control](docs/mouse-robot-control.md) in the Robot tab to hold-drag X/Y
and adjust Z with the wheel, with configurable sensitivity. The shared
[G-code motion engine](docs/gcode-motion-engine.md) provides look-ahead speed
planning, a two-command transmission window, and an ordered-path API.

## Prerequisites

### Windows
- Windows 10/11 64-bit
- Visual Studio 2022 (MSVC v143) **Desktop development with C++** workload (Build Tools 2022 also works)
- Qt 6.2+ for MSVC 2022 64-bit with modules: Qt Serial Port, Qt Multimedia,
  Qt SVG, and Qt SVG Widgets. Qt 5.15 qmake kits remain a legacy path.
- OpenCV 4.x development package with CMake configuration and matching runtime.
- CMake 3.21+

### Ubuntu Linux
- Ubuntu 22.04 or newer
- GCC with C++17 support, CMake 3.21+, and Ninja
- Qt 6.2+ development packages and OpenCV 4 development packages

### macOS
- macOS 13 Ventura or newer (Intel or Apple Silicon)
- Xcode Command Line Tools (`xcode-select --install`)
- Qt 6.2+ (clang_64) with Qt Serial Port, Qt Multimedia, Qt SVG, and Qt SVG
  Widgets components.
- OpenCV 4.x (`brew install opencv`).

### Common
- Python 3.10+ (for external scripts and YOLO integration)
- Git

Optional runtime SDKs:
- Basler Pylon Runtime (for Basler cameras)
- Hikvision MVS Runtime (for Hikvision cameras)

## Clone the Repository

```bash
git clone https://github.com/yourusername/Delta-X-Software.git
cd Delta-X-Software
```

## Project Layout

- `src/`: application implementation files (`.cpp`), including `src/device/` for hardware-specific sources.
- `include/`: public/internal headers (`.h`), including `include/device/` for device interfaces.
- `ui/`: Qt Designer forms (`.ui`).
- `resource.qrc`: central Qt resource manifest used by the forms and application runtime.
- `sdk/`: stable plugin interface, metadata contract, and SDK guide.
- `resources/`: platform-specific packaging assets such as `resources/macos/Info.plist`.
- `models/`, `script-example/`, `plugin/`, `docs/`: runtime models, example scripts, plugins, and documentation kept outside the core app tree.

Operator documentation is available directly in **G-Script -> Help** and from the
relevant workspaces. The main commissioning guides are
`docs/gscript-runtime.md`, `docs/point-tool-calibration.md`,
`docs/multi-robot-conveyor-sorting.md`, `docs/camera-gige-usb3.md`,
[Phone Camera setup](docs/phone-camera.md), and
`docs/external-vision.md`. The source-derived controller baseline and hardware
inspection checklist for this firmware snapshot are in the
[Delta X 3 firmware reference](docs/robot-firmware-delta-x-3.md); other robot
models require their own branch-specific profiles.

The versioned plugin SDK supports permission-checked host services, dynamic
G-Script primitives, namespaced devices, tracking/vision access, operator
panels, and plugin-to-plugin services. Start with the buildable
[`sdk/examples/inspection-plugin`](sdk/examples/inspection-plugin/README.md).
The bundled, opt-in experimental
[Block Programming plugin](plugin/BlockProgramming/README.md)
provides an offline block editor, live G-Script generation, validation, and
supervised worker controls. It includes a no-hardware **Software self-test**
template and matching editable fixture under `script-example/block-programming/`.

## Build from Source with CMake

On Windows, open an *x64 Native Tools Command Prompt for VS 2022* and point
CMake at the selected Qt kit:

```cmd
set CMAKE_PREFIX_PATH=C:\Qt\6.10.1\msvc2022_64
cmake --preset developer-release -DOpenCV_DIR=C:\opencv\build
cmake --build --preset developer-release --parallel 2
```

On Linux/macOS, install Qt and OpenCV through the system package manager, then
run the same two `cmake` commands. The output is under
`build/cmake-release/`. Pass `-DOpenCV_DIR=/path/to/opencv/cmake` during
configuration when OpenCV is in a non-standard location.

## Build with Qt Creator (Windows)

1. Open the root `CMakeLists.txt` and select a Qt 6.2+ desktop kit.
2. Configure with the `developer-debug` or `developer-release` preset.
3. Build the `DeltaRobotSoftware` target.

## Legacy qmake Build

`DeltaRobotSoftware.pro` remains available for existing Qt Creator/Qt 5 setups.
Run qmake from an out-of-source directory, followed by `nmake` on Windows or
`make` on Unix. `config/opencv.pri` documents `OPENCV_DIR` overrides.

## Running from the Build Tree

The debug and release outputs live in `debug/` and `release/`. Running from Qt Creator is fine for development, but distributing those folders directly will miss Qt/OpenCV runtime libraries. Follow the deploy steps below to package a self-contained build.

## Run Automated Tests

The canonical cross-platform command builds every test out of source and runs the
Qt and Python suites:

```bash
python tools/run-tests.py
```

The industrial-camera runtime test runs automatically when a built plugin is
available. See [tests/README.md](tests/README.md) for filtering and release options.

## Create a Portable Deploy Folder

Build with the CMake Release preset, then run the audited packaging script from
PowerShell:

```powershell
cmake --preset developer-release
cmake --build --preset developer-release --parallel 2
.\tools\package-release.ps1 `
  -BuildDirectory .\build\cmake-release `
  -OpenCvRuntimePath C:\opencv\build\x64\vc16\bin\opencv_world4xx.dll
```

The script discovers Qt from `CMakeCache.txt`, runs `windeployqt`, includes the
OpenCV/MSVC runtime, the Block Programming plugin, operator documentation and
legal notices, and writes
`BUILD-METADATA.json` plus `SHA256SUMS.txt`. It refuses to package a dirty source
tree unless `-AllowDirtySource` is explicitly supplied. Run
`tools/install-qt-licenses.ps1` once so the checksum-pinned LGPL/GPL texts can
be included with the deployed Qt DLLs.

Industrial-camera support is opt-in and must come from a reproducible plugin
build rather than a DLL stored in the source tree:

```powershell
.\tools\package-release.ps1 `
  -BuildDirectory .\build\cmake-camera `
  -OpenCvRuntimePath C:\opencv\build\x64\vc16\bin\opencv_world4xx.dll `
  -IndustrialCameraPluginPath .\build\cmake-camera\plugin\IndustrialCameraPlugin.dll
```

Install Basler/Hikrobot runtimes separately. Supplying
`-VendorRuntimeDirectory` requires `-AcknowledgeVendorRuntimeLicense`; use it
only after confirming that the target release may redistribute those files.
Models, tokens, machine settings and runtime logs are never copied automatically.
Every package is checked automatically; rerun the audit later with
`tools/verify-release.ps1 -PackageDirectory <path>`.

## Python and YOLO Setup on Target Machines

1. Install Python 3.10 64-bit and create a virtual environment (recommended):
   ```cmd
   py -3.10 -m venv %LOCALAPPDATA%\DeltaX\py
   %LOCALAPPDATA%\DeltaX\py\Scripts\pip install ultralytics==8.0.200 opencv-python==4.9.0.80 numpy==1.26.4
   ```
2. In the application, open *Settings > General* and set `pythonPath` to the interpreter in that environment (`python.exe` on Windows, typically `/usr/bin/python3` or the virtualenv's `bin/python3` on macOS/Linux). The field now defaults to the first `python3` found on your `PATH`.
3. Obtain a model from a source whose license and provenance you have verified,
   place it under `models/`, and verify that the external script can load it.

Operator UI settings are created on first save in `customUI.ini`; they do not need to be shipped as a repository asset.

## Troubleshooting

- **Missing MSVC runtime**: rebuild the portable package with
  `tools/package-release.ps1`; it discovers and verifies the Visual C++ x64
  redistributable files independently of the current shell environment.
- **Industrial camera plugins**: install the vendor runtime (Basler Pylon, Hikvision MVS) prior to launching the app.

## Contributing

Pull requests are welcome. Read [CONTRIBUTING.md](CONTRIBUTING.md) before starting;
all changes must include appropriate tests, documentation, and an explicit
hardware/safety validation statement when physical equipment is affected.
