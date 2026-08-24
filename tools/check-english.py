#!/usr/bin/env python3
"""Enforce English as the canonical language for tracked project content."""

from __future__ import annotations

from pathlib import Path
import re
import subprocess
import sys
import unicodedata
import zipfile


BINARY_SUFFIXES = {
    ".bmp",
    ".dll",
    ".doc",
    ".exe",
    ".exp",
    ".gif",
    ".ico",
    ".jpeg",
    ".jpg",
    ".lib",
    ".obj",
    ".onnx",
    ".pdf",
    ".pdb",
    ".png",
    ".pt",
    ".pyc",
    ".svgz",
    ".user",
    ".webp",
}

POLICY_IMPLEMENTATION_PATH = "tools/check-english.py"

LEGACY_FILENAME_PATTERN = re.compile(
    r"(?:\.vi\.|huong[-_ ]?dan|cai[-_ ]?dat|hieu[-_ ]?chuan|van[-_ ]?hanh)",
    re.IGNORECASE,
)

# This catches unaccented Vietnamese that would otherwise contain only ASCII.
# Multi-word phrases keep the signal specific enough for source and examples.
VIETNAMESE_ASCII_PATTERN = re.compile(
    r"\b(?:huong dan|cai dat|hieu chuan|van hanh|khong the|kiem tra|"
    r"nhan dien|bang tai|phan mem|tham so|trang thai|du lieu|doi tuong|"
    r"ket noi|thoi gian|toc do|vi tri|toa do|gioi han|luu y|nguyen nhan|"
    r"hanh dong|gia tri|yeu cau|muc luc|quy trinh)\b",
    re.IGNORECASE,
)


def tracked_files(root: Path) -> list[str]:
    output = subprocess.run(
        ["git", "ls-files", "-z"],
        cwd=root,
        check=True,
        capture_output=True,
    ).stdout
    return [item.decode("utf-8") for item in output.split(b"\0") if item]


def first_non_ascii_letter(text: str) -> tuple[int, str] | None:
    for index, character in enumerate(text):
        if ord(character) > 127 and unicodedata.category(character).startswith("L"):
            return index, character
    return None


def line_and_excerpt(text: str, index: int) -> tuple[int, str]:
    line_number = text.count("\n", 0, index) + 1
    line_start = text.rfind("\n", 0, index) + 1
    line_end = text.find("\n", index)
    if line_end < 0:
        line_end = len(text)
    excerpt = text[line_start:line_end].strip()
    return line_number, excerpt[:180]


def inspect_text(label: str, text: str, errors: list[str]) -> None:
    non_english = first_non_ascii_letter(text)
    if non_english is not None:
        index, character = non_english
        line_number, excerpt = line_and_excerpt(text, index)
        name = unicodedata.name(character, "UNKNOWN")
        errors.append(
            f"{label}:{line_number}: non-ASCII letter {character!r} ({name}): {excerpt}"
        )

    match = VIETNAMESE_ASCII_PATTERN.search(text)
    if match:
        line_number, excerpt = line_and_excerpt(text, match.start())
        errors.append(
            f"{label}:{line_number}: Vietnamese phrase {match.group(0)!r}: {excerpt}"
        )


def inspect_docx(path: Path, relative: str, errors: list[str]) -> None:
    try:
        with zipfile.ZipFile(path) as archive:
            bad_member = archive.testzip()
            if bad_member:
                errors.append(f"{relative}: corrupt DOCX member: {bad_member}")
                return
            for member in archive.namelist():
                if not member.endswith(".xml"):
                    continue
                if member == "word/fontTable.xml" or member.startswith("word/theme/"):
                    # Office templates carry localized fallback font names in
                    # non-visible metadata. They do not affect document prose.
                    continue
                try:
                    text = archive.read(member).decode("utf-8")
                except UnicodeDecodeError as exc:
                    errors.append(f"{relative}!{member}: XML is not UTF-8: {exc}")
                    continue
                inspect_text(f"{relative}!{member}", text, errors)
    except (OSError, zipfile.BadZipFile) as exc:
        errors.append(f"{relative}: invalid DOCX package: {exc}")


def main() -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="backslashreplace")
    if hasattr(sys.stderr, "reconfigure"):
        sys.stderr.reconfigure(encoding="utf-8", errors="backslashreplace")

    root = Path(__file__).resolve().parents[1]
    errors: list[str] = []

    for relative in tracked_files(root):
        normalized = relative.replace("\\", "/")
        if normalized == POLICY_IMPLEMENTATION_PATH:
            continue
        if LEGACY_FILENAME_PATTERN.search(normalized):
            errors.append(f"non-English or locale-specific tracked filename: {relative}")

        path = root / relative
        if not path.is_file():
            continue
        suffix = path.suffix.lower()
        if suffix == ".docx":
            inspect_docx(path, relative, errors)
            continue
        if suffix in BINARY_SUFFIXES:
            continue

        try:
            data = path.read_bytes()
        except OSError as exc:
            errors.append(f"{relative}: cannot read tracked file: {exc}")
            continue
        if b"\0" in data:
            continue
        try:
            text = data.decode("utf-8")
        except UnicodeDecodeError:
            # Binary formats that are not covered by suffix are outside the
            # text-language policy and are handled by the artifact audit.
            continue
        inspect_text(relative, text, errors)

    if errors:
        print("English-only repository validation failed:")
        for error in errors[:200]:
            print(f"- {error}")
        if len(errors) > 200:
            print(f"- ... and {len(errors) - 200} more")
        return 1

    print("English-only repository validation is valid")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
