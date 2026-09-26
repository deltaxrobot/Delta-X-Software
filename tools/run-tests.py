#!/usr/bin/env python3
"""Build and run the Delta X automated test suite with one command."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
from dataclasses import dataclass


@dataclass(frozen=True)
class TestProject:
    name: str
    target: str
    project: str
    requires_plugin: bool = False
    executable_subdir: str = ""


TEST_PROJECTS = (
    TestProject("mouse_jog", "tst_mouse_jog", "tests/mouse_jog/mouse_jog.pro"),
    TestProject("phone_camera", "tst_phone_camera", "tests/phone_camera/phone_camera.pro"),
    TestProject("drawing", "tst_drawing", "tests/drawing/drawing.pro"),
    TestProject("cli_transport", "tst_cli_transport", "tests/cli_transport/cli_transport.pro"),
    TestProject("cli_integration", "tst_cli_integration", "tests/cli_integration/cli_integration.pro"),
    TestProject("ui_theme", "tst_ui_theme", "tests/ui_theme/ui_theme.pro"),
    TestProject("control_plane", "tst_control_plane", "tests/control_plane/control_plane.pro"),
    TestProject("device_state", "tst_device_state", "tests/device_state/device_state.pro"),
    TestProject("gscript_analyzer", "tst_gscript_analyzer", "tests/gscript_analyzer/gscript_analyzer.pro"),
    TestProject("block_programming", "tst_block_programming", "tests/block_programming/block_programming.pro"),
    TestProject("variable_manager", "tst_variable_manager", "tests/variable_manager/variable_manager.pro"),
    TestProject("tracking_claim", "tst_tracking_claim", "tests/tracking_claim/tracking_claim.pro"),
    TestProject("vision_pipeline", "tst_vision_pipeline", "tests/vision_pipeline/vision_pipeline.pro"),
    TestProject("filter_worker", "tst_filter_worker", "tests/filter_worker/filter_worker.pro"),
    TestProject("calibration_core", "tst_calibration_core", "tests/calibration_core/calibration_core.pro"),
    TestProject(
        "socket_vision_protocol",
        "tst_socket_vision_protocol",
        "tests/socket_vision_protocol/socket_vision_protocol.pro",
    ),
    TestProject("gscript_runtime", "tst_gscript_runtime", "tests/gscript_runtime/gscript_runtime.pro"),
    TestProject("plugin_contract", "tst_plugin_contract", "tests/plugin_contract/plugin_contract.pro"),
    TestProject(
        "plugin_manager",
        "tst_plugin_manager",
        "tests/plugin_manager/plugin_manager.pro",
        executable_subdir="test",
    ),
    TestProject(
        "industrial_camera_optional_runtime",
        "tst_industrial_camera_optional_runtime",
        "tests/industrial_camera_optional_runtime/industrial_camera_optional_runtime.pro",
        requires_plugin=True,
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--qt-bin", type=Path, help="Directory containing qmake")
    parser.add_argument(
        "--opencv-dir",
        type=Path,
        help="Windows OpenCV build root containing include/ and x64/vc*/",
    )
    parser.add_argument(
        "--opencv-world-version",
        help="Windows opencv_world suffix (inferred from the runtime when omitted)",
    )
    parser.add_argument(
        "--build-root",
        type=Path,
        help="Out-of-source test build directory (default: <repo>/build-tests)",
    )
    parser.add_argument(
        "--test",
        action="append",
        choices=[project.name for project in TEST_PROJECTS],
        help="Run only the named test project; may be repeated",
    )
    parser.add_argument("--jobs", type=int, default=max(1, os.cpu_count() or 1))
    parser.add_argument("--plugin-path", type=Path, help="Industrial camera plugin to test")
    parser.add_argument(
        "--require-industrial-plugin",
        action="store_true",
        help="Fail instead of skipping when the industrial camera plugin is absent",
    )
    parser.add_argument("--build-only", action="store_true")
    parser.add_argument("--verbose", action="store_true", help="Show successful compiler output")
    return parser.parse_args()


def find_qmake(explicit_qt_bin: Path | None, env: dict[str, str]) -> Path:
    candidates: list[Path] = []
    if explicit_qt_bin:
        candidates.extend(explicit_qt_bin / name for name in ("qmake.exe", "qmake6", "qmake"))
    if env.get("QT_ROOT_DIR"):
        qt_root = Path(env["QT_ROOT_DIR"])
        candidates.extend(qt_root / "bin" / name for name in ("qmake.exe", "qmake6", "qmake"))
    for name in ("qmake6", "qmake"):
        resolved = shutil.which(name, path=env.get("PATH"))
        if resolved:
            candidates.append(Path(resolved))
    if os.name == "nt":
        candidates.extend(
            sorted(Path("C:/Qt").glob("*/msvc2022_64/bin/qmake.exe"), reverse=True)
        )
    for candidate in candidates:
        if candidate.is_file():
            return candidate.resolve()
    raise RuntimeError("qmake was not found; pass --qt-bin or set QT_ROOT_DIR")


def msvc_environment(base_env: dict[str, str]) -> dict[str, str]:
    if os.name != "nt" or shutil.which("cl", path=base_env.get("PATH")):
        return base_env

    program_files_x86 = base_env.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
    vswhere = Path(program_files_x86) / "Microsoft Visual Studio/Installer/vswhere.exe"
    installation = ""
    if vswhere.is_file():
        result = subprocess.run(
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
            check=True,
            capture_output=True,
            text=True,
        )
        installation = result.stdout.strip()
    if not installation:
        fallback = Path(
            r"C:\Program Files\Microsoft Visual Studio\2022\Community"
        )
        if fallback.is_dir():
            installation = str(fallback)
    if not installation:
        raise RuntimeError("MSVC 2022 was not found; run from an x64 Native Tools prompt")

    developer_command = Path(installation) / "Common7/Tools/VsDevCmd.bat"
    command = f'call "{developer_command}" -arch=x64 -host_arch=x64 >nul && set'
    result = subprocess.run(
        command,
        shell=True,
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        env=base_env,
    )
    if result.returncode:
        raise RuntimeError(
            "Failed to initialize the MSVC environment:\n"
            + (result.stderr or result.stdout).strip()
        )
    environment = base_env.copy()
    for line in result.stdout.splitlines():
        if "=" in line:
            key, value = line.split("=", 1)
            environment[key] = value
    return {key.upper(): value for key, value in environment.items()}


def run(command: list[str], cwd: Path, env: dict[str, str], capture: bool = False):
    print("+", subprocess.list2cmdline(command), flush=True)
    return subprocess.run(
        command,
        cwd=cwd,
        env=env,
        check=False,
        capture_output=capture,
        text=True,
        encoding="utf-8",
        errors="replace",
    )


def test_executable(build_dir: Path, project: TestProject) -> Path:
    if project.executable_subdir:
        build_dir = build_dir / project.executable_subdir
    if os.name == "nt":
        return build_dir / "release" / f"{project.target}.exe"
    return build_dir / project.target


def print_process_output(result: subprocess.CompletedProcess[str]) -> None:
    if result.stdout:
        print(result.stdout)
    if result.stderr:
        print(result.stderr, file=sys.stderr)


def find_opencv_world_version(opencv_dir: Path) -> str | None:
    for runtime_dir in sorted(opencv_dir.glob("x64/vc*/bin"), reverse=True):
        for runtime in sorted(runtime_dir.glob("opencv_world*.dll")):
            match = re.fullmatch(r"opencv_world(\d+)\.dll", runtime.name)
            if match:
                return match.group(1)
    return None


def find_opencv_pkgconfig(environment: dict[str, str]) -> tuple[str, str] | None:
    """Return the supported Unix OpenCV pkg-config package and version."""
    pkg_config = shutil.which("pkg-config", path=environment.get("PATH"))
    if not pkg_config:
        return None
    for package in ("opencv5", "opencv4", "opencv"):
        result = subprocess.run(
            [pkg_config, "--modversion", package],
            env=environment,
            check=False,
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
        )
        version = result.stdout.strip()
        match = re.match(r"(\d+)", version)
        if result.returncode == 0 and match and int(match.group(1)) >= 4:
            return package, version
    return None


def main() -> int:
    args = parse_args()
    repo_root = Path(__file__).resolve().parents[1]
    build_root = (args.build_root or repo_root / "build-tests").resolve()
    build_root.mkdir(parents=True, exist_ok=True)

    environment = msvc_environment(os.environ.copy())
    qmake = find_qmake(args.qt_bin, environment)
    environment["PATH"] = str(qmake.parent) + os.pathsep + environment.get("PATH", "")
    environment.setdefault("QT_QPA_PLATFORM", "offscreen")

    opencv_value = args.opencv_dir
    if opencv_value is None:
        opencv_value = Path(
            environment.get("OPENCV_DIR", repo_root / "3rd-party/opencv/build")
        )
    opencv_dir = opencv_value.resolve()
    opencv_world_version = args.opencv_world_version or environment.get(
        "OPENCV_WORLD_VERSION"
    )
    if os.name == "nt":
        if not (opencv_dir / "include/opencv2/core.hpp").is_file():
            raise RuntimeError(
                f"OpenCV headers were not found below {opencv_dir}. "
                "Pass --opencv-dir or run tools/install-opencv.ps1."
            )
        opencv_world_version = opencv_world_version or find_opencv_world_version(
            opencv_dir
        )
        if not opencv_world_version:
            raise RuntimeError(
                f"An opencv_world release runtime was not found below {opencv_dir}"
            )
        for runtime_dir in sorted(opencv_dir.glob("x64/vc*/bin"), reverse=True):
            if runtime_dir.is_dir():
                environment["PATH"] = str(runtime_dir) + os.pathsep + environment["PATH"]

    # Vendor plugins must be selected explicitly. A developer may have a stale
    # or ABI-incompatible ignored DLL at the historical repository path; using
    # it automatically makes an otherwise clean core test run non-reproducible.
    plugin_path = args.plugin_path

    selected = [
        project
        for project in TEST_PROJECTS
        if not args.test or project.name in args.test
    ]
    opencv_pkgconfig = (
        find_opencv_pkgconfig(environment) if os.name != "nt" else None
    )
    build_fingerprint = {
        "platform": sys.platform,
        "qmake": str(qmake),
        "configuration": "release",
        "opencvDir": (
            str(opencv_dir)
            if os.name == "nt"
            else "pkg-config:"
            + (
                f"{opencv_pkgconfig[0]}@{opencv_pkgconfig[1]}"
                if opencv_pkgconfig
                else "not-found"
            )
        ),
        "opencvWorldVersion": opencv_world_version if os.name == "nt" else "",
    }
    build_variant = hashlib.sha256(
        json.dumps(build_fingerprint, sort_keys=True).encode("utf-8")
    ).hexdigest()[:12]
    print(f"Build variant: {build_variant} ({build_fingerprint})", flush=True)
    failures: list[str] = []
    skipped: list[str] = []
    passed: list[str] = []

    for project in selected:
        if project.requires_plugin and not plugin_path:
            if args.require_industrial_plugin:
                failures.append(f"{project.name} (plugin missing)")
            else:
                skipped.append(f"{project.name} (plugin not built)")
            continue

        build_dir = build_root / project.name / build_variant
        build_dir.mkdir(parents=True, exist_ok=True)
        qmake_command = [
            str(qmake),
            str(repo_root / project.project),
            "CONFIG+=release",
            "CONFIG-=debug",
        ]
        if os.name == "nt":
            qmake_command[2:2] = ["-spec", "win32-msvc"]
            qmake_command.extend(
                [
                    f"OPENCV_DIR={opencv_dir.as_posix()}",
                    f"OPENCV_WORLD_VERSION={opencv_world_version}",
                ]
            )
        configured = run(qmake_command, build_dir, environment, capture=not args.verbose)
        if configured.returncode:
            print_process_output(configured)
            failures.append(f"{project.name} (qmake)")
            continue

        if os.name == "nt":
            nmake = shutil.which("nmake", path=environment.get("PATH"))
            if not nmake:
                raise RuntimeError("nmake was not found after initializing MSVC")
            build_command = [nmake, "/NOLOGO", "release"]
        else:
            make = shutil.which("make", path=environment.get("PATH"))
            if not make:
                raise RuntimeError("make was not found")
            build_command = [make, f"-j{args.jobs}"]
        built = run(build_command, build_dir, environment, capture=not args.verbose)
        if built.returncode:
            print_process_output(built)
            failures.append(f"{project.name} (build)")
            continue
        if args.build_only:
            passed.append(f"{project.name} (built)")
            continue

        executable = test_executable(build_dir, project)
        result_file = build_dir / "test-result.txt"
        if result_file.exists():
            result_file.unlink()
        test_env = environment.copy()
        if project.requires_plugin and plugin_path:
            test_env["DELTA_X_INDUSTRIAL_PLUGIN"] = str(plugin_path.resolve())
        if project.name == "plugin_manager":
            test_env["DELTA_X_TEST_PLUGIN_DIR"] = str(build_dir / "plugins-v2")
            test_env["DELTA_X_TEST_PLUGIN_V3_DIR"] = str(build_dir / "plugins-v3")
            test_env["DELTA_X_BLOCK_PLUGIN_DIR"] = str(build_dir / "plugins-block")
        completed = run(
            [str(executable), "-o", f"{result_file},txt"],
            build_dir,
            test_env,
            capture=True,
        )
        output = result_file.read_text(encoding="utf-8", errors="replace") if result_file.exists() else ""
        total_line = next((line for line in output.splitlines() if line.startswith("Totals:")), "")
        print(f"[{project.name}] {total_line or 'no QtTest summary'}")
        if completed.returncode:
            print(output or completed.stdout or completed.stderr)
            failures.append(project.name)
        else:
            passed.append(project.name)

    if not args.build_only:
        python_test = run(
            [sys.executable, str(repo_root / "tests/vision_protocol/test_dxv1.py"), "-v"],
            repo_root,
            environment,
            capture=True,
        )
        print(python_test.stdout or python_test.stderr)
        if python_test.returncode:
            failures.append("vision_protocol_python")
        else:
            passed.append("vision_protocol_python")

    print(f"PASS: {', '.join(passed) if passed else '-'}")
    print(f"SKIP: {', '.join(skipped) if skipped else '-'}")
    print(f"FAIL: {', '.join(failures) if failures else '-'}")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
