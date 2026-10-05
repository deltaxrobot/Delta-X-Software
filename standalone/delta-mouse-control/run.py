"""Source-tree launcher; works regardless of the current working directory."""

from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent / "src"))
from delta_mouse.app import main

if __name__ == "__main__":
    raise SystemExit(main())
