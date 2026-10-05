# Contributing to Delta X Software

Thank you for helping improve Delta X Software. Changes to motion, tracking,
vision, device communication, or safety behavior can affect physical equipment;
review and test them accordingly.

## Before contributing

1. Search existing issues and pull requests before starting duplicate work.
2. For architectural changes, open a design issue describing the use case,
   interfaces, migration plan, and hardware assumptions.
3. Never include credentials, camera SDK installers, proprietary models, customer
   recipes, machine logs, or generated build artifacts.
4. Contributions are accepted under Apache-2.0 and must be certified under the
   [Developer Certificate of Origin 1.1](DCO).

## Development setup

`master` is the default integration branch. Start new work on a feature branch
from an up-to-date `master`, and target pull requests at `master`. Do not commit
directly to the integration branch for routine feature development.

Follow the [cross-platform setup guide](docs/platform-setup.md) for Qt, compiler,
Python, and OpenCV installation. Check a clean machine and build out of source:

```bash
python tools/bootstrap.py doctor
python tools/bootstrap.py all
```

The lower-level canonical test command remains:

```bash
python tools/run-tests.py
```

On Windows the runner locates MSVC 2022 and Qt automatically. Override Qt with
`--qt-bin` or `QT_ROOT_DIR`. Use the CMake presets documented in
[`docs/development.md`](docs/development.md) for application builds.

## Change rules

- Keep UI code in views/controllers. Do not add new device, tracking, vision, or
  G-Script business logic directly to `RobotWindow`.
- Send physical-device commands through `DeviceCommandBroker`; do not connect a
  new producer directly to `DeviceManager::SendGcode`.
- Publish cross-module runtime data through `VariableManager` with an explicit
  project scope and persistence policy.
- Keep hardware SDKs optional at runtime. Missing Basler/Hikrobot libraries must
  not prevent the base application from starting.
- Add timeouts and bounded queues to all asynchronous hardware/network flows.
- A software stop does not replace E-stop, STO, safety PLCs, or guarded motion.

## Code style

- C++17 and Qt signal/slot conventions are the baseline.
- Use UTF-8, LF, four spaces, and the repository `.clang-format` file.
- New classes use `CamelCase`; functions follow the surrounding Qt API; private
  data members use the `m_` prefix.
- Avoid drive-letter paths and developer-specific SDK paths in source files.
- Prefer focused modules and tests over extending existing monolithic files.

Existing code predates these conventions. Do not combine a feature change with a
repository-wide formatting rewrite. Format only new code and directly edited
regions until a dedicated migration is approved.

## Project language

English is the canonical language for tracked filenames, source comments,
operator-visible UI and logs, documentation, tests, and examples. Run
`python tools/check-english.py` before submitting a change. Locale-specific
translations must use a separately reviewed localization workflow and must not
replace or mix with the canonical English source.

## Tests and pull requests

Every pull request should include:

- a concise problem statement and scope;
- tests for normal, timeout, cancellation, and fault paths where relevant;
- UI screenshots for visible changes;
- documentation updates for operator-facing behavior;
- hardware/firmware versions used for HIL testing, or an explicit “not tested on
  hardware” statement;
- confirmation that `python tools/run-tests.py` passes.

Keep commits reviewable. Do not commit generated binaries or build directories.
Reviewers may require a simulator test before accepting hardware-dependent code.

Sign every commit with `git commit -s`. The sign-off certifies the DCO; it is not
a claim that hardware testing was performed. Pull requests containing unsigned
commits may be returned for correction.

Project roles and decision-making are described in [GOVERNANCE.md](GOVERNANCE.md).
