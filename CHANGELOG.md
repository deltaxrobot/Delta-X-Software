# Changelog

All notable changes will be documented in this file. The project intends to use
semantic versioning after the first governed public release.

## Unreleased

## [2.0.0] - 2026-09-26

### Added

- Apache-2.0 first-party license, NOTICE, DCO 1.1 contribution certification,
  and explicit third-party redistribution boundaries.
- Device command broker and cell supervisor for serialized commands, controlled
  stops, fault state, and operator reset.
- G-Script analyzer/editor support, realtime tracking telemetry, external DXV1
  vision protocol, industrial camera optional-runtime handling, and calibration
  tests/documentation.
- Unified test runner, shared OpenCV qmake configuration, contributor guidance,
  repository style files, and GitHub collaboration templates.
- CMake build/presets alongside the legacy qmake build.
- Optional industrial-camera CMake target with external Pylon/MVS SDK discovery.
- Central application version and versioned plugin compatibility metadata.
- Reviewed legacy binary allowlist that prevents unreviewed artifacts entering CI.
- Audited Windows portable-package workflow with build metadata, SHA-256
  manifests, legal notices, and explicit vendor-runtime licensing gates.
- Checksum-pinned OpenCV/Qt license installers, Windows CI, dependency-isolated
  test builds, and a governed tag-to-release workflow.
- English-only repository validation covering tracked source, documentation,
  filenames, and visible DOCX content.
- Plugin API v3 with permission-checked host services, explicit lifecycle,
  dynamic G-Script primitives, namespaced plugin devices, versioned services,
  bounded events, tracking/vision access, permission UI, and a buildable
  reference inspection plugin.
- Native offline Block Programming plugin with structured drag-and-drop blocks,
  versioned project files, G-Script generation and validation, starter vision
  and multi-robot pick templates, and supervised worker load/run/stop controls.
- Adaptive mouse robot control with continuous relative Windows input, XY and Z
  scaling, bounded velocity prediction, time-based G-code segmentation,
  just-in-time command refill, braking, and reusable ordered-path planning.

### Changed

- Network servers bind to loopback by default and legacy remote execution is
  disabled by default.
- Manual, tracking, and G-Script device paths are routed through the command
  broker.
- Runtime logs, IDE state, unverified models, generated plugins and vendor SDK
  snapshots are excluded from version control and release packages.
- The incomplete vendored OpenCV 4.0 header snapshot is replaced by a
  checksum-pinned external OpenCV 4.11 dependency with its Apache-2.0 notice in
  release artifacts.
- Image filtering now uses an independently tested worker with guarded
  configuration loading and UI-thread result delivery.
- Virtual encoders, their timers, and tracking state now share one worker-thread
  ownership contract; UI updates are delivered by queued signals instead of
  cross-thread timer polling.
- G-Script metadata access and the application-wide running-worker count are
  synchronized for concurrent script threads.
- Device connection, encoder, and conveyor status are exposed as thread-safe
  snapshots; querying a disconnected device no longer creates a serial port on
  the caller thread.
- English is now the canonical language for UI messages, source comments,
  examples, help resources, commissioning documentation, and release artifacts.

### Security

- Manual/remote motion is blocked while the cell is in AUTO.
- Device timeout cancels the device queue and faults the cell instead of sending
  the next command into an uncertain response stream.

## Release history

- 2.0.0 is the first governed public-release candidate.
