# Delta X Software

Delta X Software is a comprehensive control and programming platform for Delta robots.

## Prerequisites

### Windows
- Windows 10/11 64-bit
- Visual Studio 2019 (MSVC v142) with Desktop development workload
- Qt 5.15.2 for MSVC 2019 64-bit (`C:\Qt\5.15.2\msvc2019_64`). Qt 6.10+ kits (MSVC) are also supported—install the same add-on modules: Qt Serial Port, Qt Multimedia, Qt Svg, and Qt Svg Widgets.
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

## Build from Source (Windows)

1. Open *x64 Native Tools Command Prompt for VS 2019* (or launch from PowerShell via `vcvars64.bat`).
2. Generate and build the release target with Qt qmake:
   ```cmd
   cd "E:\Professional\Developer Role\Project Type\Work\Delta X Software\Delta-X-Software"
   "C:\Qt\5.15.2\msvc2019_64\bin\qmake.exe" DeltaRobotSoftware.pro -spec win32-msvc CONFIG+=release
   nmake release
   ```
3. The release binary is produced at `release\DeltaRobotSoftware.exe`.

> **Tip:** You can also build inside Qt Creator. Configure a kit that uses Qt 5.15.2 (MSVC) and the VS2019 compiler, then build the *Release* configuration.

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

## Build with Qt 6 Kits

The project now builds with Qt 6.10+ as well as Qt 5.15.2. To use a Qt 6 kit:

1. Install Qt 6 with the **Qt Serial Port**, **Qt Multimedia**, **Qt Svg**, and **Qt Svg Widgets** components. (Qt 5 compatibility modules such as `Qt Core 5 Compatibility` are optional now that the remaining code paths use native Qt 6 APIs.)
2. In Qt Creator (or the CLI), select the Qt 6 qmake/kit before running `qmake`. All Qt 5/Qt 6 specific differences (QMatrix, QSvgWidget, camera APIs, wheel events) are handled automatically in the source.
3. Build as usual (`qmake` + `ninja`/`make`). The generated UI headers now come from your active kit, so switching between kits simply requires re-running `qmake` to regenerate them.

## Running from the Build Tree

The debug and release outputs live in `debug/` and `release/`. Running from Qt Creator is fine for development, but distributing those folders directly will miss Qt/OpenCV runtime libraries. Follow the deploy steps below to package a self-contained build.

## Create a Portable Deploy Folder

1. Ensure the release build exists (`release/DeltaRobotSoftware.exe`).
2. Run `windeployqt` to gather Qt runtime files:
   ```cmd
   set PATH=C:\Qt\5.15.2\msvc2019_64\bin;%PATH%
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
