# Delta X Software

Delta X Software is a comprehensive control and programming platform for Delta robots.

## Prerequisites

- Windows 10/11 64-bit
- Visual Studio 2019 (MSVC v142) with Desktop development workload
- Qt 5.15.2 for MSVC 2019 64-bit (`C:\Qt\5.15.2\msvc2019_64`)
- CMake 3.16+ (optional, for auxiliary tooling)
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
2. In the application, open *Settings > General* and set `pythonPath` to the virtual environment's `python.exe`.
3. Verify external scripts (for example `script-example\yolov8_detect.py --headless`) can load the models shipped in `models/`.

## Troubleshooting

- **Missing MSVC runtime**: run `vc_redist.x64.exe` (bundled in the deploy folder and installers) or install the Microsoft VC++ Redistributable 2015-2022 manually.
- **Industrial camera plugins**: install the vendor runtime (Basler Pylon, Hikvision MVS) prior to launching the app.
- **Installer cache issues**: if Qt IFW reports a cache error, delete `%LocalAppData%\cache\qt-installer-framework` and rerun the installer.

## Contributing

Pull requests are welcome. Ensure new features include appropriate documentation and testing, and follow the existing code style.
