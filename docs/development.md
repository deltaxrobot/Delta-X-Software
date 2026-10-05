# Development guide

## Canonical commands

For a clean clone, use the cross-platform bootstrap first:

```bash
python tools/bootstrap.py doctor
python tools/bootstrap.py all
```

This is the same path exercised on Windows, Ubuntu, and macOS CI. Full setup and
packaging details are in [`platform-setup.md`](platform-setup.md).

Run all automated tests:

```bash
python tools/run-tests.py
```

Run a focused test:

```bash
python tools/run-tests.py --test control_plane --test gscript_runtime
```

Validate repository policy, including canonical English content:

```bash
python tools/check-repository.py
python tools/check-english.py
```

Build the application with CMake from an out-of-source directory:

```bash
cmake --preset developer-release
cmake --build --preset developer-release --parallel 2
```

Set `CMAKE_PREFIX_PATH` to the Qt kit when CMake cannot discover Qt. On Windows,
run from an MSVC 2022 x64 environment. The qmake project remains supported for
legacy kits.

## Dependencies

- C++17 compiler
- Qt 6.2+ with Serial Port, Multimedia, SVG/SVG Widgets, Network, and Concurrent
- OpenCV 4
- Python 3.10+

`cmake/DeltaXOpenCV.cmake` is the CMake discovery point. Set `OpenCV_DIR` for a
normal OpenCV package. `DELTA_X_OPENCV_ROOT` remains available only for an
ignored local legacy tree and is not suitable for a clean clone or public
release. `config/opencv.pri` provides equivalent qmake discovery through
`OPENCV_DIR`.

The industrial camera plugin is off by default. Enable it only with external
Basler/Hikrobot SDK roots; follow
[`plugin/IndustrialCamera/BUILD_INSTRUCTIONS.md`](../plugin/IndustrialCamera/BUILD_INSTRUCTIONS.md).

## Release packages

On Windows, create portable artifacts with `tools/package-release.ps1`. The
script packages only a built executable supplied through `-BuildDirectory`; an
industrial-camera plugin must be supplied explicitly through
`-IndustrialCameraPluginPath`. A clean Git tree is required unless
`-AllowDirtySource` is used for a development-only package.

Every package contains source/build metadata, SHA-256 checksums, Apache-2.0
notices and the third-party inventory. Run `tools/install-qt-licenses.ps1` once
to fetch the checksum-pinned LGPL/GPL texts from the official Qt source; pass
`-QtLicenseDirectory` only for an equivalent reviewed source. Vendor camera runtimes may be copied only
with `-VendorRuntimeDirectory -AcknowledgeVendorRuntimeLicense`. Neural-network
models, tokens, settings and logs are deliberately excluded.

The packager runs `tools/verify-release.ps1` before reporting success. The
verifier can also be run independently against an extracted artifact:

```powershell
.\tools\verify-release.ps1 -PackageDirectory .\dist\DeltaRobotSoftware-<stamp>
```

## Versions and plugins

`VERSION.txt` is the application release source of truth. Keep `version.json`
aligned; the repository check enforces this. Plugin binary compatibility is
versioned separately through `apiVersion`. API v3 is the target for new work;
v1/v2 remain compatibility surfaces. See [`sdk/README.md`](../sdk/README.md)
and the [plugin system guide](plugin-system.md).

## Adding a module

1. Put interfaces in `include/` and implementations in `src/`.
2. Give the QObject a clear owner/thread affinity.
3. Avoid global singletons unless adapting an existing boundary.
4. Add a focused test project under `tests/<module>/` and register it in
   `tools/run-tests.py` and `tests/tests.pro`.
5. Document runtime variables, commands, timeout behavior, and fault behavior.

## Definition of done

- Release build succeeds.
- Unified test runner passes.
- No direct device-command bypass is introduced.
- New queues are bounded and cancellation-safe.
- User-visible changes have operator documentation.
- Hardware-sensitive changes state their simulator/HIL coverage.
