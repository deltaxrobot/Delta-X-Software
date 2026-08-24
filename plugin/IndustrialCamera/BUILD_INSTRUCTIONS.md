# Industrial camera plugin build guide

The plugin is an optional first-party adapter for Basler Pylon and Hikrobot MVS.
Vendor SDK files are not part of the project's Apache-2.0 grant and must be
installed/accepted separately.

## Supported build contract

- Windows x64 with MSVC 2022
- Qt 6.8+ Widgets
- OpenCV 4
- Basler Pylon 9 Development package
- Hikrobot MVS x64 Development package

The SDK directories must use these layouts:

```text
<pylon>/include/pylon/PylonIncludes.h
<pylon>/lib/x64/PylonBase_v9.lib
<mvs>/Includes/MvCameraControl.h
<mvs>/Libraries/win64/MvCameraControl.lib
```

The DLLs are delay-loaded. A built plugin can therefore load and report a clear
"backend unavailable" status on a machine where either vendor runtime is absent.

## CMake build

From an x64 MSVC environment:

```cmd
set CMAKE_PREFIX_PATH=C:\Qt\6.10.1\msvc2022_64
cmake --preset developer-release ^
  -DDELTA_X_BUILD_INDUSTRIAL_CAMERA_PLUGIN=ON ^
  -DDELTA_X_PYLON_ROOT="C:\Program Files\Basler\pylon\Development" ^
  -DDELTA_X_MVS_ROOT="C:\Program Files (x86)\MVS\Development"
cmake --build --preset developer-release --parallel 2
```

The output is `build/cmake-release/plugin/IndustrialCameraPlugin.dll`, beside
the application in the layout expected by `RobotWindow`.

## qmake build

Use an out-of-source directory and pass the same roots:

```cmd
qmake path\to\IndustrialCamera.pro -spec win32-msvc CONFIG+=release ^
  DELTA_X_PYLON_ROOT="C:\Program Files\Basler\pylon\Development" ^
  DELTA_X_MVS_ROOT="C:\Program Files (x86)\MVS\Development"
nmake
```

The plugin is written to `<build>/plugin/`, never into the source tree.

## Legacy migration mode

The historical checkout still contains quarantined SDK snapshots. They may be
used only to verify migration on a local machine:

```cmd
qmake path\to\IndustrialCamera.pro CONFIG+=release CONFIG+=legacy_vendor_sdks
```

For CMake, use `-DDELTA_X_ALLOW_LEGACY_VENDOR_SDKS=ON`. Do not publish the SDK
files or produce public artifacts from this mode. See the root
`THIRD_PARTY_NOTICES.md`.

## Runtime validation

Run the optional-runtime test with the exact built plugin:

```cmd
python tools\run-tests.py --test industrial_camera_optional_runtime ^
  --plugin-path build\cmake-release\plugin\IndustrialCameraPlugin.dll ^
  --require-industrial-plugin
```
