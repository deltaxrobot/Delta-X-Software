# Third-party redistribution audit

The exact legacy binary baseline is recorded in
[`config/tracked-artifacts.allowlist`](../config/tracked-artifacts.allowlist).
`python tools/check-repository.py` rejects any newly tracked binary or IDE-user
artifact that has not been explicitly reviewed and added to that file. An
allowlist entry records review status only; it does not establish redistribution
rights.

This is an engineering inventory, not a legal determination. The current tree
contains vendored code, SDK material, binaries, and a model that must be reviewed
before a governed open-source release.

| Area | Current repository state | Release action |
|---|---|---|
| QJoysticks | Source plus `LICENSE.md`; bundled SDL includes license/copying files | Preserve notices and confirm versions |
| OpenCV | Incomplete 4.0 snapshot removed from Git; ignored local copies may remain; Windows CI pins 4.11.0 | Use a package/system installation and preserve its Apache-2.0/distribution notices |
| Hikrobot MVS | Removed from Git; ignored local copies may remain | Build against a user-installed SDK; verify terms before packaging its runtime |
| Basler Pylon | Removed from Git; ignored local copies may remain | Build against a user-installed SDK; verify terms before packaging its runtime |
| YOLO model | Removed from Git and ignored pending provenance | Record source, exact version, license, and redistribution terms before publishing |
| Industrial camera plugin DLL | Removed from Git; reproducible CMake/qmake builds are documented | Publish only as a CI-generated release artifact after dependency review |

The repository now retains only five reviewed SDL link/runtime binaries in the
legacy allowlist. The Qt Creator `.pro.user` file, camera SDK trees, duplicate
plugin/root OpenCV snapshots, generated plugin DLL, runtime log, and unverified
model have been removed from Git while local ignored copies may remain for
migration work.

First-party material is now Apache-2.0. The selected license does not change the
quarantine status of unverified vendor SDK/model material; see the root
`THIRD_PARTY_NOTICES.md`.

## Cleanup migration

1. Record checksums and origins for every vendor package/model used in a release.
2. Publish application/plugin binaries only as CI-generated release artifacts.
3. Decide whether to replace the remaining SDL binaries with package discovery.
4. Add confirmed vendor runtime notices before producing a camera-enabled bundle.
