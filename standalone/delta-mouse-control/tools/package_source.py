"""Build a clean standalone source handoff using an explicit inclusion list."""

from pathlib import Path
import hashlib
import zipfile


def main():
    root = Path(__file__).resolve().parents[1]
    name = "delta-mouse-control-1.0.0"
    destination = root / "dist"
    destination.mkdir(exist_ok=True)
    archive = destination / f"{name}-source.zip"
    files = [root / filename for filename in (
        "pyproject.toml", "requirements.txt", "README.md", "AI_INTEGRATION.md",
        "LICENSE", "NOTICE", "THIRD_PARTY_NOTICES.md", ".gitignore", "run.py", "launch.ps1", "MANIFEST.in",
    )]
    for directory, suffix in (("src", ".py"), ("tests", ".py"), ("examples", ".py"),
                               ("docs", ".md"), ("tools", ".py")):
        files.extend(p for p in (root / directory).rglob(f"*{suffix}") if "__pycache__" not in p.parts)
    if any(not path.is_file() for path in files):
        raise FileNotFoundError("Required package file is missing")
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as bundle:
        for path in sorted(files):
            entry = zipfile.ZipInfo(f"{name}/{path.relative_to(root).as_posix()}", (2026, 1, 1, 0, 0, 0))
            entry.compress_type = zipfile.ZIP_DEFLATED
            entry.external_attr = 0o644 << 16
            bundle.writestr(entry, path.read_bytes())
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    checksum = archive.with_suffix(".zip.sha256")
    checksum.write_text(f"{digest}  {archive.name}\n", encoding="ascii")
    print(archive)
    print(f"{len(files)} files; SHA256 {digest}")


if __name__ == "__main__":
    main()
