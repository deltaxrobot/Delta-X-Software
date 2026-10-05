# Dependency and redistribution policy

## Rules for new dependencies

Every dependency proposal must record its exact name, version, source URL,
license/SPDX identifier, checksum or lockfile identity, purpose, update owner,
and whether it is linked, loaded as a plugin, executed as a process, or used only
for development.

Do not commit vendor SDKs, installers, import libraries, runtime binaries, trained
models, or generated plugins. Prefer one of these mechanisms:

1. system/package-manager discovery for open-source libraries;
2. a user-installed vendor SDK discovered through a cache variable/environment
   variable;
3. a documented, checksum-verified download step that runs outside Git and is
   permitted by the vendor terms;
4. CI-generated release artifacts for first-party binaries.

## Review gates

A dependency is acceptable only when:

- its license is compatible with the distribution being produced;
- all required notices are included in `THIRD_PARTY_NOTICES.md`;
- optional hardware runtimes remain optional at application startup;
- removal/update instructions and supported versions are documented;
- CI and a clean machine build do not rely on an untracked developer path.

The repository validator blocks newly tracked binary/user artifacts. Existing
legacy items are a quarantine baseline, not precedent for adding more.

The Windows packager follows the same boundary. Vendor camera runtimes are
excluded by default and require both an explicit directory and the
`-AcknowledgeVendorRuntimeLicense` switch. This acknowledgement records an
operator decision; it does not grant redistribution rights.
