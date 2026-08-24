# Third-party notices

The root Apache-2.0 license covers only material that Delta X Software
copyright holders and contributors have authority to license. It does not
replace the terms of the components below.

## Redistributable components with notices present

| Component | Location | Version/license evidence | Required action |
|---|---|---|---|
| QJoysticks | `3rd-party/QJoysticks/` | MIT; copyright WinT 3794; see its `LICENSE.md` | Preserve its license |
| SDL | `3rd-party/QJoysticks/lib/SDL/` | zlib-style SDL license; see `include/SDL_copying.h` | Preserve the notice |
| OpenCV | External dependency; legacy local snapshots are ignored | Governed Windows version 4.11.0, Apache-2.0; see `licenses/OpenCV-notice.md` | Preserve Apache-2.0 and distribution-specific notices |
| Qt code-editor examples | `include/highlighter.h`, `src/codeeditor.cpp` and related example code | BSD-3-Clause text is retained in the source headers | Preserve the complete source notices; reproduce them with binary distributions |

Qt itself is a build/runtime dependency and is not relicensed by this project.
See `licenses/Qt-runtime-notice.md`. Packagers must comply with the license
applicable to the Qt distribution they choose; the Windows packager copies the
checksum-pinned LGPL/GPL documents from the official Qt source into binary
artifacts.

## Quarantined legacy material

The following files may remain in existing developers' ignored local worktrees,
but are no longer tracked. Their redistribution has not been approved. They must
not be included in a public source archive, installer, container, or release
artifact until their exact origin and applicable vendor terms are recorded:

- Basler Pylon material under `plugin/IndustrialCamera/3rd-party/pylon/`;
- Hikrobot MVS material under `plugin/IndustrialCamera/3rd-party/mvs/`;
- the generated `plugin/IndustrialCameraPlugin.dll`;
- `models/yolov8n.pt` (6,534,387 bytes, SHA-256
  `31E20DDE3DEF09E2CF938C7BE6FE23D9150BBBE503982AF13345706515F2EF95`).

Use locally installed camera SDKs for development. Release automation must build
the first-party adapter without copying SDK headers, import libraries, vendor
sample executables, or vendor runtime DLLs into source-control artifacts.
