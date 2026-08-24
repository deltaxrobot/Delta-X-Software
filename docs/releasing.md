# Release process

Public releases are produced only by `.github/workflows/release.yml`. A release
artifact is a clean, traceable output; it is not a copy of a developer's
`release/`, `plugin/`, or `models/` directory.

## Prepare a version

1. Choose a semantic version and update `VERSION.txt`, `version.json`, and the
   changelog. Repository validation checks the other version surfaces.
2. Move relevant `Unreleased` entries under a dated heading such as
   `## [1.4.0] - 2026-09-15`.
3. Run `python tools/check-repository.py`, `python tools/run-tests.py`, and a
   Release build.
4. Record simulator and hardware-in-the-loop status for motion, encoder,
   conveyor, camera, vacuum, and E-stop-related changes.
5. Verify a candidate tag locally:

   ```bash
   python tools/check-release.py --tag v1.4.0
   ```

6. Merge through the protected release branch, then create and push the matching
   `v<version>` tag. The release workflow repeats Windows tests before publishing.

## Public artifact boundary

The public Windows package contains the application, Qt/OpenCV/MSVC runtimes,
operator documentation, build metadata, legal notices, and SHA-256 manifests.
It deliberately excludes:

- Basler Pylon and Hikrobot MVS SDK/runtime files;
- the Industrial Camera plugin until redistribution terms are approved;
- neural-network models without recorded provenance;
- tokens, settings, logs, calibration results, and machine/customer data.

UVC cameras and external DXV1 vision remain available without the proprietary
camera plugin. A camera-enabled artifact must be a separately reviewed release
with exact SDK/runtime versions, vendor terms, and hardware validation evidence.

## Failure and rollback

Never replace files attached to an existing version tag. If an artifact is
wrong, mark the release as withdrawn, document the reason, fix the source, and
issue a new patch version. Preserve failed artifact hashes and the incident
record for traceability.
