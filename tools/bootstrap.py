#!/usr/bin/env python3
"""Check, build, test, run, and package Delta X Software on desktop platforms."""

from __future__ import annotations

import argparse
from dataclasses import dataclass
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
from typing import Iterable


MINIMUM_CMAKE = (3, 21, 0)
MINIMUM_QT = (6, 2, 0)
MINIMUM_OPENCV = (4, 0, 0)


@dataclass(frozen=True)
class Dependency:
    name: str
    available: bool
    detail: str


@dataclass(frozen=True)
class QtInstallation:
    root: Path
    bin_dir: Path
    version: tuple[int, ...]


@dataclass(frozen=True)
class OpenCvInstallation:
    cmake_dir: Path | None
    version: tuple[int, ...]
    description: str


def parse_version(value: str) -> tuple[int, ...] | None:
    match = re.search(r"(?<!\d)(\d+)(?:\.(\d+))?(?:\.(\d+))?", value)
    if not match:
        return None
    return tuple(int(part or 0) for part in match.groups())


def version_at_least(actual: tuple[int, ...], minimum: tuple[int, ...]) -> bool:
    width = max(len(actual), len(minimum))
    return actual + (0,) * (width - len(actual)) >= minimum + (0,) * (width - len(minimum))


def version_text(value: tuple[int, ...]) -> str:
    return ".".join(str(part) for part in value)


def capture(command: list[str], env: dict[str, str] | None = None) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        command,
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        env=env,
    )


def run_checked(command: list[str], cwd: Path, env: dict[str, str]) -> None:
    command = command.copy()
    resolved = executable(command[0], env)
    if resolved:
        command[0] = resolved
    print("+", subprocess.list2cmdline(command), flush=True)
    completed = subprocess.run(command, cwd=cwd, env=env, check=False)
    if completed.returncode:
        raise RuntimeError(
            f"Command failed with exit code {completed.returncode}: "
            f"{subprocess.list2cmdline(command)}"
        )


def executable(name: str, env: dict[str, str] | None = None) -> str | None:
    return shutil.which(name, path=(env or os.environ).get("PATH"))


def msvc_environment(base_env: dict[str, str]) -> dict[str, str]:
    if os.name != "nt" or executable("cl", base_env):
        return base_env

    program_files_x86 = base_env.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
    vswhere = Path(program_files_x86) / "Microsoft Visual Studio/Installer/vswhere.exe"
    installation = ""
    if vswhere.is_file():
        result = capture(
            [
                str(vswhere),
                "-latest",
                "-products",
                "*",
                "-requires",
                "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
                "-property",
                "installationPath",
            ],
            base_env,
        )
        if result.returncode == 0:
            installation = result.stdout.strip()

    for fallback in (
        Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
        Path(r"C:\Program Files\Microsoft Visual Studio\2022\BuildTools"),
        Path(r"C:\Program Files\Microsoft Visual Studio\2022\Professional"),
        Path(r"C:\Program Files\Microsoft Visual Studio\2022\Enterprise"),
    ):
        if not installation and fallback.is_dir():
            installation = str(fallback)

    if not installation:
        raise RuntimeError("MSVC 2022 with the x64 C++ tools was not found")

    developer_command = Path(installation) / "Common7/Tools/VsDevCmd.bat"
    result = subprocess.run(
        f'call "{developer_command}" -arch=x64 -host_arch=x64 >nul && set',
        shell=True,
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        env=base_env,
    )
    if result.returncode:
        raise RuntimeError("MSVC was found but its build environment could not be initialized")

    environment = base_env.copy()
    for line in result.stdout.splitlines():
        if "=" in line:
            key, value = line.split("=", 1)
            environment[key] = value
    return environment


def command_version(
    command: list[str], env: dict[str, str] | None = None
) -> tuple[int, ...] | None:
    result = capture(command, env)
    if result.returncode:
        return None
    return parse_version(result.stdout + result.stderr)


def qt_from_qmake(qmake: Path) -> QtInstallation | None:
    version_result = capture([str(qmake), "-query", "QT_VERSION"])
    root_result = capture([str(qmake), "-query", "QT_INSTALL_PREFIX"])
    version = parse_version(version_result.stdout)
    root_value = root_result.stdout.strip()
    if version_result.returncode or root_result.returncode or not version or not root_value:
        return None
    return QtInstallation(Path(root_value).expanduser().resolve(), qmake.parent.resolve(), version)


def qmake_candidates(root: Path) -> Iterable[Path]:
    for name in ("qmake6.exe", "qmake.exe", "qmake6", "qmake"):
        yield root / "bin" / name
    for name in ("qmake6", "qmake"):
        yield root / "libexec" / name


def qt_roots(explicit: Path | None, repo_root: Path) -> Iterable[Path]:
    if explicit:
        yield explicit.expanduser()
    if os.environ.get("QT_ROOT_DIR"):
        yield Path(os.environ["QT_ROOT_DIR"]).expanduser()
    for entry in os.environ.get("CMAKE_PREFIX_PATH", "").split(os.pathsep):
        if entry:
            yield Path(entry).expanduser()

    if os.name == "nt":
        roots = list(Path("C:/Qt").glob("*/msvc2022_64"))
        roots.sort(key=lambda item: parse_version(item.parent.name) or (0,), reverse=True)
        yield from roots
    elif sys.platform == "darwin":
        for command in (("brew", "--prefix", "qt"), ("brew", "--prefix", "qt@6")):
            if executable(command[0]):
                result = capture(list(command))
                if result.returncode == 0 and result.stdout.strip():
                    yield Path(result.stdout.strip())
        roots = list((Path.home() / "Qt").glob("*/macos"))
        roots.sort(key=lambda item: parse_version(item.parent.name) or (0,), reverse=True)
        yield from roots

    # Keep this last so an explicit or repository-local toolchain wins.
    yield repo_root / "build/dependencies/qt"


def find_qt(explicit: Path | None, repo_root: Path) -> QtInstallation | None:
    seen: set[Path] = set()
    for root in qt_roots(explicit, repo_root):
        normalized = root.resolve()
        if normalized in seen:
            continue
        seen.add(normalized)
        for qmake in qmake_candidates(normalized):
            if qmake.is_file():
                installation = qt_from_qmake(qmake)
                if installation:
                    return installation

    for name in ("qmake6", "qmake"):
        value = executable(name)
        if value:
            installation = qt_from_qmake(Path(value))
            if installation:
                return installation
    return None


def opencv_config_candidates(root: Path) -> Iterable[Path]:
    if root.name.lower() == "opencvconfig.cmake":
        yield root.parent
    yield root
    yield root / "lib/cmake/opencv4"
    yield root / "build"
    yield from root.glob("x64/vc*/lib")


def opencv_version_from_config(cmake_dir: Path) -> tuple[int, ...] | None:
    for filename in ("OpenCVConfig-version.cmake", "OpenCVConfigVersion.cmake"):
        path = cmake_dir / filename
        if not path.is_file():
            continue
        version = parse_version(path.read_text(encoding="utf-8", errors="replace"))
        if version:
            return version
    config = cmake_dir / "OpenCVConfig.cmake"
    if config.is_file():
        return parse_version(config.read_text(encoding="utf-8", errors="replace"))
    return None


def normalized_opencv_cmake_dir(candidate: Path) -> Path:
    if os.name != "nt" or (candidate / "include/opencv2/core.hpp").is_file():
        return candidate
    for parent in candidate.parents:
        if (parent / "OpenCVConfig.cmake").is_file() and (
            parent / "include/opencv2/core.hpp"
        ).is_file():
            return parent
    return candidate


def find_opencv(explicit: Path | None, repo_root: Path) -> OpenCvInstallation | None:
    roots: list[Path] = []
    if explicit:
        roots.append(explicit.expanduser())
    if os.environ.get("OpenCV_DIR"):
        roots.append(Path(os.environ["OpenCV_DIR"]).expanduser())
    if os.name == "nt":
        roots.extend(sorted(repo_root.glob("build/dependencies/opencv-*/opencv/build"), reverse=True))
    elif sys.platform == "darwin" and executable("brew"):
        result = capture(["brew", "--prefix", "opencv"])
        if result.returncode == 0 and result.stdout.strip():
            roots.append(Path(result.stdout.strip()))

    seen: set[Path] = set()
    for root in roots:
        for candidate in opencv_config_candidates(root.resolve()):
            if candidate in seen:
                continue
            seen.add(candidate)
            if (candidate / "OpenCVConfig.cmake").is_file():
                normalized = normalized_opencv_cmake_dir(candidate)
                version = opencv_version_from_config(normalized) or (4, 0, 0)
                return OpenCvInstallation(normalized, version, str(normalized))

    pkg_config = executable("pkg-config")
    if pkg_config:
        result = capture([pkg_config, "--modversion", "opencv4"])
        version = parse_version(result.stdout)
        if result.returncode == 0 and version:
            return OpenCvInstallation(None, version, "pkg-config:opencv4")
    return None


def install_windows_opencv(repo_root: Path, environment: dict[str, str]) -> None:
    powershell = executable("pwsh", environment) or executable("powershell", environment)
    if not powershell:
        raise RuntimeError("PowerShell is required to install the pinned Windows OpenCV package")
    run_checked(
        [
            powershell,
            "-NoProfile",
            "-ExecutionPolicy",
            "Bypass",
            "-File",
            str(repo_root / "tools/install-opencv.ps1"),
        ],
        repo_root,
        environment,
    )


def dependency_hint() -> str:
    if os.name == "nt":
        return (
            "Install Visual Studio 2022 C++ Build Tools, CMake, Ninja, and Qt 6.2+ "
            "for MSVC 2022 x64 (Serial Port, Multimedia, and SVG modules). Set "
            "QT_ROOT_DIR to the Qt kit if it is outside C:\\Qt. OpenCV is installed "
            "from the checksum-pinned package when a build is requested."
        )
    if sys.platform == "darwin":
        return (
            "Run 'xcode-select --install', install Homebrew, then run "
            "'brew install cmake ninja qt opencv python'."
        )
    return (
        "Install Qt 6.2+ and the build dependencies on Ubuntu 22.04+: "
        "sudo apt update && sudo apt install build-essential cmake "
        "ninja-build pkg-config qt6-base-dev qt6-base-dev-tools qt6-multimedia-dev "
        "libqt6serialport6-dev libqt6svg6-dev libopencv-dev libgl1-mesa-dev python3"
    )


def collect_dependencies(
    environment: dict[str, str], qt: QtInstallation | None, opencv: OpenCvInstallation | None
) -> list[Dependency]:
    cmake = executable("cmake", environment)
    ninja = executable("ninja", environment)
    cmake_version = command_version([cmake, "--version"], environment) if cmake else None
    ninja_version = command_version([ninja, "--version"], environment) if ninja else None
    compiler = "cl" if os.name == "nt" else ("clang++" if sys.platform == "darwin" else "c++")
    return [
        Dependency("Python", version_at_least(sys.version_info[:3], (3, 10, 0)), platform.python_version()),
        Dependency(
            "CMake",
            bool(cmake_version and version_at_least(cmake_version, MINIMUM_CMAKE)),
            version_text(cmake_version) if cmake_version else "not found",
        ),
        Dependency("Ninja", bool(ninja_version), version_text(ninja_version) if ninja_version else "not found"),
        Dependency("C++ compiler", bool(executable(compiler, environment)), executable(compiler, environment) or "not found"),
        Dependency(
            "Qt",
            bool(qt and version_at_least(qt.version, MINIMUM_QT)),
            f"{version_text(qt.version)} at {qt.root}" if qt else "not found",
        ),
        Dependency(
            "OpenCV",
            bool(opencv and version_at_least(opencv.version, MINIMUM_OPENCV)),
            f"{version_text(opencv.version)} via {opencv.description}" if opencv else "not found",
        ),
    ]


def print_doctor(dependencies: list[Dependency]) -> bool:
    print(f"Delta X platform: {platform.system()} {platform.machine()}")
    print(f"Minimum versions: CMake {version_text(MINIMUM_CMAKE)}, Qt {version_text(MINIMUM_QT)}, OpenCV 4.x")
    print()
    for item in dependencies:
        print(f"[{'OK' if item.available else 'MISSING'}] {item.name}: {item.detail}")
    healthy = all(item.available for item in dependencies)
    if not healthy:
        print("\nInstall hint:")
        print(dependency_hint())
    return healthy


def default_build_dir(repo_root: Path, build_type: str) -> Path:
    return repo_root / "build" / f"bootstrap-{build_type.lower()}"


def configure(
    repo_root: Path,
    build_dir: Path,
    build_type: str,
    qt: QtInstallation,
    opencv: OpenCvInstallation,
    environment: dict[str, str],
) -> None:
    command = [
        "cmake",
        "-S",
        str(repo_root),
        "-B",
        str(build_dir),
        "-G",
        "Ninja",
        f"-DCMAKE_BUILD_TYPE={build_type}",
        f"-DCMAKE_PREFIX_PATH={qt.root}",
    ]
    if opencv.cmake_dir:
        command.append(f"-DOpenCV_DIR={opencv.cmake_dir}")
    run_checked(command, repo_root, environment)


def build(build_dir: Path, jobs: int, environment: dict[str, str]) -> None:
    run_checked(["cmake", "--build", str(build_dir), "--parallel", str(jobs)], build_dir, environment)


def run_tests(
    repo_root: Path,
    qt: QtInstallation,
    opencv: OpenCvInstallation,
    jobs: int,
    environment: dict[str, str],
) -> None:
    command = [
        sys.executable,
        str(repo_root / "tools/run-tests.py"),
        "--qt-bin",
        str(qt.bin_dir),
        "--jobs",
        str(jobs),
    ]
    if opencv.cmake_dir and os.name == "nt":
        command.extend(["--opencv-dir", str(opencv.cmake_dir)])
    run_checked(command, repo_root, environment)


def runtime_environment(
    environment: dict[str, str], qt: QtInstallation, opencv: OpenCvInstallation
) -> dict[str, str]:
    result = environment.copy()
    path_entries = [str(qt.bin_dir)]
    if opencv.cmake_dir and os.name == "nt":
        for runtime in opencv.cmake_dir.rglob("opencv_world*.dll"):
            path_entries.append(str(runtime.parent))
            break
    result["PATH"] = os.pathsep.join(path_entries + [result.get("PATH", "")])
    return result


def run_application(
    build_dir: Path,
    environment: dict[str, str],
) -> None:
    if os.name == "nt":
        command = [str(build_dir / "DeltaRobotSoftware.exe")]
    elif sys.platform == "darwin":
        command = ["open", "-n", str(build_dir / "DeltaRobotSoftware.app")]
    else:
        command = [str(build_dir / "DeltaRobotSoftware")]
    run_checked(command, build_dir, environment)


def package(build_dir: Path, repo_root: Path, environment: dict[str, str]) -> None:
    output_dir = repo_root / "dist"
    output_dir.mkdir(parents=True, exist_ok=True)
    previous = {
        path: path.stat().st_mtime_ns for path in output_dir.iterdir() if path.is_file()
    }
    run_checked(
        ["cpack", "--config", str(build_dir / "CPackConfig.cmake"), "-B", str(output_dir)],
        build_dir,
        environment,
    )
    artifacts = sorted(
        path
        for path in output_dir.iterdir()
        if path.is_file() and previous.get(path) != path.stat().st_mtime_ns
    )
    print("Packages:")
    for artifact in artifacts:
        print(f"  {artifact}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "action",
        nargs="?",
        choices=("doctor", "configure", "build", "test", "all", "run", "package"),
        default="doctor",
    )
    parser.add_argument("--qt-root", type=Path, help="Qt installation prefix")
    parser.add_argument("--opencv-dir", type=Path, help="Directory containing OpenCVConfig.cmake")
    parser.add_argument("--build-dir", type=Path, help="Out-of-source CMake build directory")
    parser.add_argument("--build-type", choices=("Debug", "Release"), default="Release")
    parser.add_argument("--jobs", type=int, default=max(1, os.cpu_count() or 1))
    parser.add_argument(
        "--no-auto-opencv",
        action="store_true",
        help="Do not install the checksum-pinned OpenCV package automatically on Windows",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    repo_root = Path(__file__).resolve().parents[1]
    build_dir = (args.build_dir or default_build_dir(repo_root, args.build_type)).resolve()

    try:
        environment = msvc_environment(os.environ.copy())
    except RuntimeError as error:
        environment = os.environ.copy()
        if args.action != "doctor":
            print(f"ERROR: {error}", file=sys.stderr)
            print(dependency_hint(), file=sys.stderr)
            return 1

    qt = find_qt(args.qt_root, repo_root)
    opencv = find_opencv(args.opencv_dir, repo_root)
    if args.action != "doctor" and os.name == "nt" and not opencv and not args.no_auto_opencv:
        try:
            install_windows_opencv(repo_root, environment)
            opencv = find_opencv(args.opencv_dir, repo_root)
        except RuntimeError as error:
            print(f"ERROR: {error}", file=sys.stderr)
            return 1

    dependencies = collect_dependencies(environment, qt, opencv)
    healthy = print_doctor(dependencies)
    if args.action == "doctor":
        return 0 if healthy else 1
    if not healthy or not qt or not opencv:
        return 1

    try:
        if args.action in ("configure", "build", "all", "run", "package"):
            configure(repo_root, build_dir, args.build_type, qt, opencv, environment)
        if args.action in ("build", "all", "run", "package"):
            build(build_dir, args.jobs, environment)
        if args.action in ("test", "all"):
            run_tests(repo_root, qt, opencv, args.jobs, environment)
        if args.action == "run":
            run_application(build_dir, runtime_environment(environment, qt, opencv))
        if args.action == "package":
            package(build_dir, repo_root, environment)
    except RuntimeError as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 1

    if args.action in ("configure", "build", "all"):
        print(f"Build directory: {build_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
