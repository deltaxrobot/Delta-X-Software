#!/usr/bin/env python3
"""Validate files that define the contributor-facing repository contract."""

from pathlib import Path
import json
import re
import subprocess
import sys
import xml.etree.ElementTree as ET


REQUIRED_FILES = (
    ".editorconfig",
    ".gitattributes",
    ".gitignore",
    ".clang-format",
    ".clang-tidy",
    ".github/workflows/ci.yml",
    ".github/workflows/release.yml",
    "CMakeLists.txt",
    "CMakePresets.json",
    "VERSION.txt",
    "LICENSE",
    "NOTICE",
    "DCO",
    "THIRD_PARTY_NOTICES.md",
    "README.md",
    "CONTRIBUTING.md",
    "CODE_OF_CONDUCT.md",
    "SECURITY.md",
    "CHANGELOG.md",
    "GOVERNANCE.md",
    "docs/architecture.md",
    "docs/Delta-X-Multi-Robot-Installation-Calibration-Operation-Guide.docx",
    "docs/camera-gige-usb3.md",
    "docs/development.md",
    "docs/dependency-policy.md",
    "docs/external-vision.md",
    "docs/gscript-design.md",
    "docs/gscript-runtime.md",
    "docs/licensing-decision.md",
    "docs/multi-robot-conveyor-sorting.md",
    "docs/platform-setup.md",
    "docs/releasing.md",
    "docs/third-party-audit.md",
    "docs/variable-manager.md",
    "config/version.pri",
    "config/dependencies.json",
    "cmake/DeltaXOpenCV.cmake",
    "plugin/IndustrialCamera/CMakeLists.txt",
    "plugin/IndustrialCamera/BUILD_INSTRUCTIONS.md",
    "licenses/OpenCV-notice.md",
    "licenses/Qt-runtime-notice.md",
    "config/tracked-artifacts.allowlist",
    "sdk/DeltaXPluginMetadata.h",
    "sdk/DeltaXVersion.h",
    "sdk/README.md",
    "resources/macos/Info.plist",
    "tests/device_state/device_state.pro",
    "tests/device_state/tst_device_state.cpp",
    "tests/filter_worker/filter_worker.pro",
    "tests/filter_worker/tst_filter_worker.cpp",
    "tests/tests.pro",
    "tests/tooling/test_bootstrap.py",
    "tools/bootstrap.py",
    "tools/package-release.ps1",
    "tools/check-release.py",
    "tools/check-english.py",
    "tools/install-opencv.ps1",
    "tools/install-qt-licenses.ps1",
    "tools/run-tests.py",
    "tools/verify-release.ps1",
)

BINARY_SUFFIXES = {".dll", ".exe", ".lib", ".exp", ".obj", ".pdb", ".user"}
NON_TEXT_REQUIRED_SUFFIXES = {".docx"}

# These files are installed locally by developers or supplied by hardware/model
# vendors.  Keeping the rule here prevents a future contributor from bypassing
# .gitignore with `git add -f` and accidentally redistributing them.
QUARANTINED_TRACKED_PATHS = {
    "DeltaRobotSoftware.pro.user",
    "coordinates.txt",
    "customUI.ini",
    "models/yolov8n.pt",
    "mylog.txt",
    "plugin/IndustrialCameraPlugin.dll",
    "settings.ini",
    "token.txt",
}
QUARANTINED_TRACKED_ROOTS = (
    "3rd-party/opencv/",
    "plugin/IndustrialCamera/3rd-party/mvs/",
    "plugin/IndustrialCamera/3rd-party/opencv/",
    "plugin/IndustrialCamera/3rd-party/pylon/",
)


def read_allowlist(path: Path) -> set[str]:
    entries: set[str] = set()
    for line_number, raw_line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        entry = raw_line.strip().replace("\\", "/")
        if not entry or entry.startswith("#"):
            continue
        if entry in entries:
            raise ValueError(f"duplicate entry at line {line_number}: {entry}")
        entries.add(entry)
    return entries


def main() -> int:
    root = Path(__file__).resolve().parents[1]
    errors: list[str] = []
    for relative in REQUIRED_FILES:
        path = root / relative
        if not path.is_file():
            errors.append(f"missing required file: {relative}")
            continue
        if path.suffix.lower() in NON_TEXT_REQUIRED_SUFFIXES:
            continue
        try:
            path.read_text(encoding="utf-8")
        except UnicodeDecodeError:
            errors.append(f"not valid UTF-8: {relative}")

    try:
        license_text = (root / "LICENSE").read_text(encoding="utf-8")
        if "Apache License" not in license_text or "Version 2.0" not in license_text:
            errors.append("LICENSE must contain the standard Apache-2.0 text")
        if "Apache-2.0" not in (root / "THIRD_PARTY_NOTICES.md").read_text(
            encoding="utf-8"
        ):
            errors.append("THIRD_PARTY_NOTICES.md must state the first-party scope")
    except (OSError, UnicodeDecodeError) as exc:
        errors.append(f"invalid licensing files: {exc}")

    try:
        version = (root / "VERSION.txt").read_text(encoding="utf-8").strip()
        if not re.fullmatch(r"\d+\.\d+\.\d+", version):
            errors.append("VERSION.txt must contain one semantic version (x.y.z)")
    except (OSError, UnicodeDecodeError) as exc:
        errors.append(f"invalid VERSION.txt: {exc}")
        version = ""
    try:
        release_manifest = json.loads(
            (root / "version.json").read_text(encoding="utf-8")
        )
        if release_manifest.get("latest") != version:
            errors.append("version.json latest must match VERSION.txt")
    except (OSError, UnicodeDecodeError, json.JSONDecodeError) as exc:
        errors.append(f"invalid version.json: {exc}")

    try:
        json.loads((root / "CMakePresets.json").read_text(encoding="utf-8"))
        dependencies = json.loads(
            (root / "config/dependencies.json").read_text(encoding="utf-8")
        )
        if dependencies.get("schemaVersion") != 1:
            errors.append("config/dependencies.json must use schemaVersion 1")
        opencv = dependencies.get("opencv", {})
        opencv_windows = opencv.get("windows", {})
        opencv_version = opencv.get("version", "")
        if not re.fullmatch(r"\d+\.\d+\.\d+", opencv_version):
            errors.append("pinned OpenCV version must be semantic")
        if opencv.get("license") != "Apache-2.0":
            errors.append("pinned OpenCV 4.11 dependency must declare Apache-2.0")
        expected_opencv_url = (
            "https://github.com/opencv/opencv/releases/download/"
            f"{opencv_version}/opencv-{opencv_version}-windows.exe"
        )
        if opencv_windows.get("url") != expected_opencv_url:
            errors.append("pinned OpenCV URL must be the matching official release")
        if not re.fullmatch(r"[0-9a-f]{64}", opencv_windows.get("sha256", "")):
            errors.append("pinned OpenCV package must have a lowercase SHA-256")
        if not re.fullmatch(r"\d+", opencv_windows.get("worldVersion", "")):
            errors.append("pinned OpenCV worldVersion must be numeric")

        qt = dependencies.get("qt", {})
        qt_version = qt.get("ciVersion", "")
        if not re.fullmatch(r"\d+\.\d+\.\d+", qt_version):
            errors.append("pinned Qt CI version must be semantic")
        qt_licenses = qt.get("licenses", [])
        expected_qt_licenses = {"LGPL-3.0-only.txt", "GPL-3.0-only.txt"}
        if {item.get("name") for item in qt_licenses} != expected_qt_licenses:
            errors.append("Qt dependency must pin LGPL-3.0 and GPL-3.0 texts")
        for item in qt_licenses:
            expected_prefix = (
                f"https://raw.githubusercontent.com/qt/qtbase/v{qt_version}/LICENSES/"
            )
            if item.get("url") != expected_prefix + item.get("name", ""):
                errors.append(f"invalid official Qt license URL: {item.get('name', '')}")
            if not re.fullmatch(r"[0-9a-f]{64}", item.get("sha256", "")):
                errors.append(f"Qt license must have a lowercase SHA-256: {item.get('name', '')}")

        plugin_metadata = json.loads(
            (root / "plugin/IndustrialCamera/IndustrialCameraPlugin.json").read_text(
                encoding="utf-8"
            )
        )
        if plugin_metadata.get("apiVersion") != 1:
            errors.append("industrial camera plugin must target plugin API v1")
    except (OSError, UnicodeDecodeError, json.JSONDecodeError) as exc:
        errors.append(f"invalid JSON configuration: {exc}")

    try:
        ci_text = (root / ".github/workflows/ci.yml").read_text(encoding="utf-8")
        release_text = (root / ".github/workflows/release.yml").read_text(
            encoding="utf-8"
        )
        if "windows-build-test:" not in ci_text:
            errors.append("CI must include a Windows build/test job")
        if "linux-build-test:" not in ci_text:
            errors.append("CI must include a Linux build/test job")
        if "macos-build-test:" not in ci_text:
            errors.append("CI must include a macOS build/test job")
        if ci_text.count("tools/bootstrap.py") < 3:
            errors.append("each desktop CI path must exercise the bootstrap tool")
        if "install-opencv.ps1" not in ci_text:
            errors.append("Windows CI must install the checksum-pinned OpenCV package")
        if "6.8.*" in ci_text or "6.8.*" in release_text:
            errors.append("CI Qt versions must be exact, not wildcards")
        if "check-release.py" not in release_text:
            errors.append("release workflow must validate the version/tag contract")
        if "package-release.ps1" not in release_text:
            errors.append("release workflow must use the audited packager")
        if "IndustrialCameraPluginPath" in release_text:
            errors.append("public release workflow must not package the vendor camera plugin")
    except (OSError, UnicodeDecodeError) as exc:
        errors.append(f"invalid CI workflow: {exc}")

    try:
        plist_root = ET.parse(root / "resources/macos/Info.plist").getroot()
        plist_dictionary = plist_root.find("dict")
        plist_items = list(plist_dictionary) if plist_dictionary is not None else []
        plist_values = {
            plist_items[index].text: plist_items[index + 1].text
            for index in range(0, len(plist_items) - 1, 2)
            if plist_items[index].tag == "key"
        }
        if plist_values.get("CFBundleShortVersionString") != version:
            errors.append("macOS bundle version must match VERSION.txt")
    except (OSError, ET.ParseError) as exc:
        errors.append(f"invalid resources/macos/Info.plist: {exc}")

    tracked = subprocess.run(
        ["git", "ls-files"],
        cwd=root,
        check=True,
        capture_output=True,
        text=True,
        encoding="utf-8",
    ).stdout.splitlines()

    english_check = subprocess.run(
        [sys.executable, str(root / "tools/check-english.py")],
        cwd=root,
        capture_output=True,
        text=True,
        encoding="utf-8",
    )
    if english_check.returncode != 0:
        output = (english_check.stdout + english_check.stderr).strip()
        errors.append(f"English-only policy failed:\n{output}")
    generated_roots = ("build/", "build-tests/", "debug/", "release/", "dist/")
    for relative in tracked:
        normalized = relative.replace("\\", "/")
        if normalized.startswith(generated_roots):
            errors.append(f"tracked generated artifact: {relative}")
        if normalized in QUARANTINED_TRACKED_PATHS or normalized.startswith(
            QUARANTINED_TRACKED_ROOTS
        ):
            errors.append(f"tracked quarantined dependency/artifact: {relative}")
        filename = Path(normalized).name
        if (
            filename.startswith("ui_")
            and filename.endswith(".h")
            and (root / relative).exists()
        ):
            errors.append(f"tracked generated Qt UI header: {relative}")

    allowlist_path = root / "config/tracked-artifacts.allowlist"
    try:
        allowed_artifacts = read_allowlist(allowlist_path)
    except (OSError, UnicodeDecodeError, ValueError) as exc:
        errors.append(f"invalid tracked-artifacts allowlist: {exc}")
        allowed_artifacts = set()

    tracked_artifacts = {
        relative.replace("\\", "/")
        for relative in tracked
        if Path(relative).suffix.lower() in BINARY_SUFFIXES
    }
    unexpected_artifacts = sorted(tracked_artifacts - allowed_artifacts)
    stale_allowlist_entries = sorted(allowed_artifacts - tracked_artifacts)
    for relative in unexpected_artifacts:
        errors.append(f"tracked binary/user artifact is not reviewed: {relative}")
    for relative in stale_allowlist_entries:
        errors.append(f"stale tracked-artifacts allowlist entry: {relative}")

    if tracked_artifacts:
        print(
            f"WARNING: {len(tracked_artifacts)} reviewed legacy binary/user artifacts remain tracked; "
            "see docs/third-party-audit.md"
        )

    if errors:
        print("Repository validation failed:")
        for error in errors:
            print(f"- {error}")
        return 1
    print("Repository foundation is valid")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
