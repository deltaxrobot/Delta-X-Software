# Project governance

Delta X Software currently uses a maintainer-led model.

## Roles

- **Contributors** report issues, improve documentation, submit code, and review
  changes.
- **Reviewers** provide domain review for motion, tracking, vision, devices,
  G-Script, UI, build, or security.
- **Maintainers** triage work, protect architectural and safety boundaries, merge
  changes, manage releases, and enforce community policies.

Roles are earned through sustained, technically sound, respectful contributions.
Maintainers may grant or revoke review/merge responsibilities in the interest of
project safety and continuity.

## Decisions

Routine changes are decided through pull request review. Cross-module protocols,
public SDK changes, persistent project formats, safety behavior, and breaking
G-Script changes require a design issue before implementation. Maintainers seek
consensus; when consensus is not practical, the responsible maintainer documents
the decision and rationale.

## Releases

A release requires:

- a green supported CI matrix;
- an updated changelog and version;
- no unresolved release-blocking security or motion-safety defect;
- packaging smoke tests;
- explicit status of simulator and hardware-in-the-loop validation.

Governed public artifacts are created by the tag-driven release workflow. See
`docs/releasing.md`; proprietary camera runtimes/plugins require a separate
redistribution and hardware-validation review.

## Conflict of interest

Reviewers must disclose when a contribution affects their employer, customer,
commercial product, or proprietary integration. A different maintainer should make
the final merge decision when practical.

## Licensing

First-party contributions are Apache-2.0 and use DCO 1.1 sign-off. Maintainers
must preserve third-party notices and may not approve release artifacts containing
quarantined vendor material without documented redistribution authority. See
`docs/licensing-decision.md` and `THIRD_PARTY_NOTICES.md`.
