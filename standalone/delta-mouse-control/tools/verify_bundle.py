"""Verify the archive can run its core example outside this repository."""

from pathlib import Path
import subprocess
import sys
import tempfile
import zipfile


def main():
    root = Path(__file__).resolve().parents[1]
    archive = root / "dist" / "delta-mouse-control-1.0.0-source.zip"
    with tempfile.TemporaryDirectory(prefix="delta-mouse-bundle-") as temporary:
        unpacked = Path(temporary).resolve()
        with zipfile.ZipFile(archive) as bundle:
            for entry in bundle.infolist():
                target = (unpacked / entry.filename).resolve()
                if not target.is_relative_to(unpacked):
                    raise ValueError("Archive entry escaped extraction directory")
            bundle.extractall(unpacked)
        package = unpacked / "delta-mouse-control-1.0.0"
        source = str(package / "src")
        example = str(package / "examples" / "headless_mouse.py")
        script = (f"import sys, runpy; sys.path.insert(0, {source!r}); "
                  f"runpy.run_path({example!r}, run_name='__main__'); "
                  "assert not any(n.startswith(('PySide6', 'serial')) for n in sys.modules)")
        # -I -S excludes user environment and site packages, including editable installs.
        subprocess.run([sys.executable, "-I", "-S", "-c", script], cwd=unpacked, check=True)
    print("Isolated source bundle verified without Qt, pyserial or repository dependencies.")


if __name__ == "__main__":
    main()
