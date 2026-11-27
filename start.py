#!/usr/bin/env python3
"""Build and open the current checkout with its matching runtime dependencies."""

from pathlib import Path
import subprocess
import sys


def main() -> int:
    root = Path(__file__).resolve().parent
    return subprocess.run(
        [sys.executable, str(root / "tools" / "bootstrap.py"), "run", *sys.argv[1:]],
        cwd=root,
        check=False,
    ).returncode


if __name__ == "__main__":
    raise SystemExit(main())
