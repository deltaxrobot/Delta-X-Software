# Cross-platform setup and deployment

This guide is the canonical path from a clean clone to a tested desktop build.
The same `tools/bootstrap.py` entry point is exercised by CI on Windows, Ubuntu,
and macOS.

## Supported desktop platforms

| Platform | Core application | CI | Contributor package | Industrial camera plugin |
| --- | --- | --- | --- | --- |
| Windows 10/11 x64 | Supported | Build and tests | ZIP; audited public packager is separate | Basler/Hikrobot SDK build supported |
| Ubuntu 22.04+ x64 | Supported | Build, tests, and TGZ | System-dependent TGZ | Not currently supported |
| macOS | Supported target | Build, tests, and DMG | Unsigned DMG | Not currently supported |

The core application includes serial devices, G-Script, tracking, USB/UVC
cameras, and the external DXV1 vision protocol. Vendor camera SDK support is an
optional plugin and never prevents the core application from starting.

Android, iOS, and BSD are not supported targets.

## Common workflow

Clone the repository and enter it:

```bash
git clone https://github.com/deltaxrobot/Delta-X-Software.git
cd Delta-X-Software
```

Inspect the local toolchain without changing the machine:

```bash
python tools/bootstrap.py doctor
```

After installing any reported dependencies, build the application and run all
automated tests:

```bash
python tools/bootstrap.py all
```

Run the application from the build tree:

```bash
python tools/bootstrap.py run
```

Create a contributor package under `dist/`:

```bash
python tools/bootstrap.py package
```

Use `python3` instead of `python` on systems where that is the configured
command. Run `python tools/bootstrap.py --help` for Qt, OpenCV, build-directory,
configuration, and parallel-job overrides.

## Windows

Install:

- Visual Studio 2022 or Build Tools 2022 with **Desktop development with C++**;
- CMake 3.21+ and Ninja;
- Python 3.10+;
- Qt 6.2+ for **MSVC 2022 64-bit**, including Qt Serial Port, Qt Multimedia,
  Qt SVG, and Qt SVG Widgets.

The bootstrap tool detects normal `C:\Qt\<version>\msvc2022_64` installations
and initializes the MSVC environment even from a regular PowerShell window. If
Qt is elsewhere, use either form:

```powershell
$env:QT_ROOT_DIR = 'D:\Qt\6.10.1\msvc2022_64'
python tools/bootstrap.py all
```

```powershell
python tools/bootstrap.py all --qt-root D:\Qt\6.10.1\msvc2022_64
```

When OpenCV is absent, a build request runs `tools/install-opencv.ps1`. That
script downloads the version pinned in `config/dependencies.json`, verifies its
SHA-256 checksum, and caches it below the ignored `build/dependencies/` tree.
Pass `--no-auto-opencv` to prohibit downloads, or `--opencv-dir` to select an
existing OpenCV CMake package.

Official public Windows artifacts continue to use the audited
`tools/package-release.ps1` workflow. The CPack ZIP produced by the bootstrap
tool is intended for contributor validation.

## Ubuntu Linux

Ubuntu 22.04 and newer provide the minimum Qt 6.2 toolchain through the normal
package repositories:

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build pkg-config \
  qt6-base-dev qt6-base-dev-tools qt6-multimedia-dev \
  libqt6serialport6-dev libqt6svg6-dev \
  libopencv-dev libgl1-mesa-dev python3
```

Then run:

```bash
python3 tools/bootstrap.py all
python3 tools/bootstrap.py run
```

The TGZ created by a distribution Qt 6.2 installation is system-dependent: the
target machine should install the same Qt and OpenCV runtime packages. Newer
shared Qt versions can use Qt's CMake deployment API to copy supported runtime
dependencies into the package.

Serial and camera devices may require local permissions:

```bash
sudo usermod -aG dialout,video "$USER"
```

Sign out and back in after changing groups. Production machines should use
reviewed udev rules with the exact robot, encoder, and camera vendor/product IDs
instead of broad device permissions.

Other Linux distributions can build the same CMake project when they provide a
C++17 compiler, CMake 3.21+, Ninja, Qt 6.2+ development modules, OpenCV 4
development files, Python 3.10+, and `pkg-config`. Ubuntu is the Linux reference
environment validated by CI.

## macOS

Install Xcode Command Line Tools and Homebrew dependencies:

```bash
xcode-select --install
brew install cmake ninja qt opencv python
```

The bootstrap tool asks Homebrew for the Qt and OpenCV prefixes, so keg-only Qt
installations do not need to be added globally to `PATH`. An installation from
the Qt online installer can be selected explicitly:

```bash
python3 tools/bootstrap.py all --qt-root "$HOME/Qt/6.11.2/macos"
```

The first camera use triggers the normal macOS camera permission prompt. If
access was denied, enable it under **System Settings > Privacy & Security >
Camera**.

`python3 tools/bootstrap.py package` produces a DMG for contributor testing. It
is not code-signed or notarized. Public macOS distribution requires a project
signing identity, hardened-runtime review, notarization credentials, and a
release-policy update.

## Focused actions

| Command | Purpose |
| --- | --- |
| `python tools/bootstrap.py doctor` | Detect the compiler, CMake, Ninja, Qt, and OpenCV |
| `python tools/bootstrap.py configure` | Generate the out-of-source CMake build |
| `python tools/bootstrap.py build` | Configure and compile the application |
| `python tools/bootstrap.py test` | Build and run the Qt/Python test suites |
| `python tools/bootstrap.py all` | Build the application and run all tests |
| `python tools/bootstrap.py run` | Build and launch the application |
| `python tools/bootstrap.py package` | Build and create the platform CPack artifact |

Build outputs default to `build/bootstrap-release/`. Override them without
editing a preset:

```bash
python tools/bootstrap.py all --build-dir build/my-kit --build-type Debug --jobs 4
```

## Troubleshooting

### Qt is installed but not found

Pass the installation prefix, not its `bin` directory:

```bash
python tools/bootstrap.py doctor --qt-root /path/to/Qt/6.x/<desktop-kit>
```

`QT_ROOT_DIR` and `CMAKE_PREFIX_PATH` are also recognized.

### OpenCV is installed but not found

On Linux/macOS, verify `pkg-config --modversion opencv4`. Set `PKG_CONFIG_PATH`
when the package is in a non-standard prefix. For CMake packages, pass the
directory containing `OpenCVConfig.cmake`:

```bash
python tools/bootstrap.py all --opencv-dir /path/to/opencv/lib/cmake/opencv4
```

### The core application starts without an industrial camera

This is expected. The plugin is off by default and is loaded only when its
vendor SDK/runtime is available. See
[`plugin/IndustrialCamera/BUILD_INSTRUCTIONS.md`](../plugin/IndustrialCamera/BUILD_INSTRUCTIONS.md).

### A package builds but hardware is unavailable

Build portability does not prove hardware compatibility. Record the OS,
architecture, Qt/OpenCV versions, USB/GigE driver, robot firmware, encoder mode,
and camera SDK version during hardware-in-the-loop commissioning.
