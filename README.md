# Delta X Software

Delta X Software is a comprehensive control and programming platform for Delta robots.

## Prerequisites

### Windows
- Windows 10/11 64-bit
- Visual Studio 2022 (MSVC v143) **Desktop development with C++** workload (Build Tools 2022 also works)
- Qt 6.10.1 for MSVC 2022 64-bit (`C:\Qt\6.10.1\msvc2022_64`) with modules: Qt Serial Port, Qt Multimedia, Qt Svg, Qt Svg Widgets.  
  Qt 5.15.2 MSVC kits still work if you need legacy builds.
- CMake 3.16+ (optional, for auxiliary tooling)

### macOS
- macOS 13 Ventura or newer (Intel or Apple Silicon)
- Xcode Command Line Tools (`xcode-select --install`)
- Qt 5.15.2 for macOS (clang_64). When using Homebrew install `qt@5` and export `PATH="/opt/homebrew/opt/qt@5/bin:$PATH"` (use `/usr/local` on Intel Macs). Qt 6.10+ kits (clang_64) are fully supported as well; install the Qt Serial Port, Qt Multimedia, Qt Svg, and Qt Svg Widgets components.
- OpenCV 4.x (`brew install opencv`). The qmake project auto-detects Homebrew in `/opt/homebrew` and `/usr/local`, or you can run `qmake OPENCV_DIR=/custom/opencv` to point to a different install.

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

## Build from Source (Windows, CLI with Qt 6.10)

1. Open *x64 Native Tools Command Prompt for VS 2022* (or call `vcvars64.bat` from PowerShell).
2. Create a clean build folder and run qmake + nmake:
   ```cmd
   cd E:\Working\Source\Delta-X-Software
   rmdir /s /q build_cli_qt6_release 2>nul
   mkdir build_cli_qt6_release
   cd build_cli_qt6_release
   "C:\Qt\6.10.1\msvc2022_64\bin\qmake.exe" ..\DeltaRobotSoftware.pro -spec win32-msvc CONFIG+=release
   nmake
   ```
3. The release binary is at `build_cli_qt6_release\release\DeltaRobotSoftware.exe`.  
   To run locally, ensure `C:\Qt\6.10.1\msvc2022_64\bin` and `3rd-party\opencv\build\x64\vc15\bin` are on `PATH`.

## Build with Qt Creator (Windows)

1. Kit: select `Qt 6.10.1 (msvc2022_64)` and MSVC 2022 x64 compiler.  
2. “Run qmake” (Reconfigure) after switching kits.  
3. Build the *Release* configuration (Debug is possible but heavier on memory).  
4. Output lives under the build directory Qt Creator creates (e.g. `build/Desktop_Qt_6_10_1_MSVC2022_64bit-Release/release/DeltaRobotSoftware.exe`).

## Build from Source (macOS)

1. Install dependencies with Homebrew (Qt 5 + OpenCV) and ensure the Qt 5 `qmake` is first in `PATH`:
   ```bash
   brew install qt@5 opencv
   export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"   # /usr/local/... on Intel Macs
   ```
2. Configure and build with qmake/clang:
   ```bash
   qmake DeltaRobotSoftware.pro CONFIG+=release
   make -j"$(sysctl -n hw.ncpu)"
   ```
   If OpenCV lives outside the default Homebrew folders, pass `OPENCV_DIR=/path/to/opencv` to qmake so the project can locate headers and libraries.
3. The release bundle is produced at `release/DeltaRobotSoftware.app`. Bundle Qt frameworks with `macdeployqt` when you need a redistributable folder:
   ```bash
   macdeployqt release/DeltaRobotSoftware.app
   ```

## Build with Qt 6 Kits (general notes)

- Supported: Qt 6.10+ (MSVC/clang_64). Install modules: Qt Serial Port, Qt Multimedia, Qt Svg, Qt Svg Widgets.  
- Re-run `qmake` whenever you switch kits (Qt 5 ↔ Qt 6) so UI headers regenerate correctly.  
- No Qt5Compat dependency is required for the main build; code paths use native Qt 6 APIs.

## Running from the Build Tree

The debug and release outputs live in `debug/` and `release/`. Running from Qt Creator is fine for development, but distributing those folders directly will miss Qt/OpenCV runtime libraries. Follow the deploy steps below to package a self-contained build.

## Create a Portable Deploy Folder

1. Ensure the release build exists (`release/DeltaRobotSoftware.exe` or `build_cli_qt6_release\release\DeltaRobotSoftware.exe`).
2. Run `windeployqt` to gather Qt runtime files:
   ```cmd
   set PATH=C:\Qt\6.10.1\msvc2022_64\bin;%PATH%
   windeployqt --release --compiler-runtime --dir deploy\DeltaRobotSoftware --qmldir . release\DeltaRobotSoftware.exe
   ```
3. Copy additional assets into `deploy\DeltaRobotSoftware`:
   - `3rd-party/opencv/build/x64/vc15/bin/opencv_world400.dll`
   - `3rd-party/opencv/build/x64/vc15/bin/opencv_ffmpeg400_64.dll`
   - `customUI.ini`, `GScript_Documentation.html`, `token.txt`, `version.json`
   - Entire folders: `models/`, `script-example/`, `plugin/python/`
   - Plugin DLL: `plugin/IndustrialCameraPlugin.dll`
4. Create an empty `gcode` folder inside the deploy directory (the app expects it).
5. Optional launch helpers:
   - `deploy\DeltaRobotSoftware\LaunchDeltaRobotSoftware.ps1` checks and installs `vc_redist.x64.exe` before starting the app.
   - `deploy\DeltaRobotSoftware\LaunchDeltaRobotSoftware.cmd` wraps the PowerShell script for double-click usage.

The `deploy\DeltaRobotSoftware` folder is now portable. Zip it or copy it to target machines and instruct users to run the launcher so the VC++ Redistributable is installed automatically.

## Build a Qt Installer Framework Package

Qt IFW is available at `C:\Qt\Tools\Tools\QtInstallerFramework\4.7`. Project assets live in `installer/ifw/`:

- `config/config.xml`: global installer metadata.
- `packages/com.deltax.software/data`: the payload copied from `deploy/`.
- `packages/com.deltax.software/meta/package.xml`: component metadata.
- `packages/com.deltax.software/meta/installscript.qs`: runs `vc_redist.x64.exe` and creates shortcuts.

To regenerate the installer:

```cmd
cd installer\ifw
"C:\Qt\Tools\Tools\QtInstallerFramework\4.7\bin\binarycreator.exe" -c config\config.xml -p packages DeltaXSoftwareInstaller.exe
```

The resulting `DeltaXSoftwareInstaller.exe` installs prerequisites, copies files to the target directory, and creates Start Menu/Desktop shortcuts.

## Build an NSIS Installer (Optional)

An NSIS script is provided in `installer/nsis/DeltaXSoftware.nsi`. After installing [NSIS](https://nsis.sourceforge.io/), run:

```cmd
cd installer\nsis
makensis DeltaXSoftware.nsi
```

The generated `DeltaXSoftwareSetup.exe` checks the VC++ redistributable (using registry keys), runs `vc_redist.x64.exe` if needed, deploys the payload, and registers an uninstaller entry.

## Python and YOLO Setup on Target Machines

1. Install Python 3.10 64-bit and create a virtual environment (recommended):
   ```cmd
   py -3.10 -m venv %LOCALAPPDATA%\DeltaX\py
   %LOCALAPPDATA%\DeltaX\py\Scripts\pip install ultralytics==8.0.200 opencv-python==4.9.0.80 numpy==1.26.4
   ```
2. In the application, open *Settings > General* and set `pythonPath` to the interpreter in that environment (`python.exe` on Windows, typically `/usr/bin/python3` or the virtualenv's `bin/python3` on macOS/Linux). The field now defaults to the first `python3` found on your `PATH`.
3. Verify external scripts (for example `script-example\yolov8_detect.py --headless`) can load the models shipped in `models/`.

## Troubleshooting

- **Missing MSVC runtime**: run `vc_redist.x64.exe` (bundled in the deploy folder and installers) or install the Microsoft VC++ Redistributable 2015-2022 manually.
- **Industrial camera plugins**: install the vendor runtime (Basler Pylon, Hikvision MVS) prior to launching the app.
- **Installer cache issues**: if Qt IFW reports a cache error, delete `%LocalAppData%\cache\qt-installer-framework` and rerun the installer.

## Contributing

Pull requests are welcome. Ensure new features include appropriate documentation and testing, and follow the existing code style.
