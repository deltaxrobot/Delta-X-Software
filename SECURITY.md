# Security policy

Delta X Software can control physical machinery. Treat command injection,
authentication bypass, stale tracking data, unsafe recovery, and denial of safety
actions as security-sensitive issues.

## Supported versions

Security fixes currently target the latest development branch. A formal supported
release matrix will be added when versioned public releases begin.

## Reporting a vulnerability

Use GitHub's private vulnerability reporting/security advisory feature when it is
enabled. Otherwise contact a maintainer privately through the contact information
on the repository owner profile. Do not publish exploit details, machine network
addresses, credentials, or customer data in a public issue.

Include:

- affected commit/version and platform;
- impact and required access level;
- minimal reproduction steps;
- whether real hardware was involved;
- suggested mitigation, if known.

Maintainers should acknowledge a report within seven days and provide a status
update within fourteen days. These targets are best effort until a dedicated
security team exists.

## Deployment boundary

- Keep control endpoints on loopback or an isolated trusted machine network.
- Do not expose DXV1 or legacy remote-control ports directly to the Internet.
- Keep `Network.AllowLegacyRemoteControl` disabled unless compatibility requires
  it and the deployment has an independent access-control layer.
- E-stop, STO, guards, and safety PLC functions must remain independent from this
  application.
