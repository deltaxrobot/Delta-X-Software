#!/usr/bin/env python3
"""Validate the version/changelog contract for a governed release."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--tag",
        help="Git tag to validate; governed tags must be exactly v<VERSION.txt>",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    root = Path(__file__).resolve().parents[1]
    version = (root / "VERSION.txt").read_text(encoding="utf-8").strip()
    if not re.fullmatch(r"\d+\.\d+\.\d+", version):
        raise SystemExit("VERSION.txt must contain one semantic version")

    manifest = json.loads((root / "version.json").read_text(encoding="utf-8"))
    if manifest.get("latest") != version:
        raise SystemExit("version.json latest does not match VERSION.txt")

    if args.tag:
        expected_tag = f"v{version}"
        if args.tag != expected_tag:
            raise SystemExit(
                f"release tag {args.tag!r} does not match expected {expected_tag!r}"
            )
        changelog = (root / "CHANGELOG.md").read_text(encoding="utf-8")
        release_heading = re.compile(
            rf"^## \[?{re.escape(version)}\]? - \d{{4}}-\d{{2}}-\d{{2}}\s*$",
            re.MULTILINE,
        )
        if not release_heading.search(changelog):
            raise SystemExit(
                f"CHANGELOG.md needs a dated '## [{version}] - YYYY-MM-DD' heading"
            )

    print(f"Release contract is valid for Delta X Software {version}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
