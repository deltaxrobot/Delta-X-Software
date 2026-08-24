# Plugin system

Delta X Software supports native Qt plugins for cameras, devices, operator
panels, G-Script primitives, inspection logic, MES/PLC connectors, telemetry,
and other cell integrations. The core application starts normally when no
optional plugin is installed.

> Native plugins execute in the application process with the same operating
> system identity as Delta X Software. Host permissions protect application
> services; they are not an operating-system sandbox. Install only plugins
> whose source, publisher, build, and dependencies you trust.

## Install and inspect a plugin

1. Obtain a plugin compiled for the same operating system, architecture,
   compiler ABI, Qt compatibility, and build mode as the application. A Windows
   DLL cannot run on Linux or macOS.
2. Open **Modules > Plugins**.
3. Select **Open Built-in Folder** and copy the plugin library into it. Typical
   extensions are `.dll`, `.so`, and `.dylib`.
4. Restart Delta X Software.
5. Confirm that the plugin state is `loaded`. Review its API, semantic version,
   capabilities, requested permissions, path, and diagnostics.
6. For API v3, select the plugin, choose **Permissions...**, grant only the
   documented permissions, and restart again.

Discovery is non-recursive and scans only explicit directories. Symlinks that
resolve outside a selected directory are ignored. Enable the per-user plugin
directory explicitly if it is needed. Administrators may add controlled paths
through `PluginSystem/AdditionalDirectories`.

Enable/disable changes and permission changes apply at the next restart.
Disabled IDs are stored in `PluginSystem/DisabledPluginIds`. Grants are stored
per stable plugin ID in `PluginSystem/GrantedPermissions/<plugin-id>`.

Plugin settings are isolated by project and stable ID under:

```text
PluginSystem/Projects/<project>/<plugin-id>/
```

Renaming a library does not change settings identity. Duplicate IDs are
rejected deterministically.

## States and diagnostics

| State | Meaning | Action |
|---|---|---|
| `loaded` | Metadata, ABI, runtime contract, and lifecycle passed. | Review capabilities and grants before operation. |
| `disabled` | The stable ID is disabled. | Enable it and restart if needed. |
| `rejected` | Metadata, identity, dependency, lifecycle, or extension registration failed. | Read **Details**, correct the plugin, then restart. |
| `unloaded` | The library was cleanly released. | No action required. |
| `unload-failed` | Qt or the OS retained the library. | Stop plugin work, close dependent UI, inspect logs, and restart. |

Common rejection causes include a newer API, wrong IID, invalid semantic
version, capability/interface mismatch, duplicate extension names, missing Qt
or vendor libraries, and compiler/debug/architecture mismatch.

Camera vendor runtimes remain optional. The industrial camera v2 plugin reports
backend availability without preventing startup. See [GigE and USB3
cameras](camera-gige-usb3.md).

## API generations

- **v1** is the frozen legacy camera/panel contract. Missing `apiVersion` means
  v1.
- **v2** introduced stable identity, semantic versioning, capabilities, panels,
  and structured commands. Existing v2 binaries remain supported.
- **v3** is the current target. It adds permission-checked host access,
  lifecycle, G-Script primitives, plugin devices, and service discovery.

New plugins should implement `DeltaXPluginV3` and list both
`DeltaXPluginV2` and `DeltaXPluginV3` in `Q_INTERFACES`, because v3 extends the
v2 identity/settings surface.

## API v3 lifecycle

The host uses this order:

1. inspect metadata without executing plugin code;
2. load and validate runtime identity, version, capabilities, and interfaces;
3. load project settings;
4. call `initialize(DeltaXHostContext*)`;
5. call `start()`;
6. register extension interfaces whose permissions were granted;
7. on shutdown, call `stop()`, unregister extensions, invalidate the context,
   and unload libraries in reverse order.

`initialize()` and `start()` must return an error instead of leaving a partially
started plugin. `stop()` must finish threads, timers, device I/O, callbacks, and
panel-owned activity before returning. A plugin must never delete its root or
the host context.

## Permission reference

| Permission | Host operation |
|---|---|
| `variables.read` | Read project-scoped variables. |
| `variables.write.runtime` | Write/remove session variables. |
| `variables.write.persistent` | Write persistent project variables. |
| `events.read` | Poll the bounded host/plugin event stream. |
| `events.publish` | Publish a namespaced event. |
| `devices.command` | Submit a command through the device broker. |
| `devices.provide` | Register namespaced plugin devices and complete responses. |
| `vision.submit` | Submit correlated conveyor-coordinate detections. |
| `tracking.read` | Read copy-based tracking snapshots. |
| `tracking.claim` | Claim, release, or complete tracked objects atomically. |
| `gscript.register` | Register G-Script primitives. |
| `services.provide` | Register versioned plugin services. |
| `services.consume` | Invoke services registered by another plugin. |
| `health.report` | Publish plugin health under `PluginSystem.<id>.Health.*`. |
| `telemetry.publish` | Publish metrics under `PluginSystem.<id>.Telemetry.*`. |
| `cell.control` | Request a supervised controlled stop/fault. |

Declaring a permission does not grant it. Without a grant, the context returns a
permission error and related G-Script/device/service extensions are not
registered. Plugins should degrade gracefully when optional permissions are
denied.

## G-Script primitives

Implement `DeltaXGScriptProvider`, declare capability `gscript.primitives`, and
request `gscript.register`. Each descriptor contains:

```cpp
QVariantMap{
    {"name", "inspectioncount"},
    {"signature", "M98 PinspectionCount(result, trackingId, confidence)"},
    {"description", "Count accepted tracked objects"},
    {"minArgs", 3},
    {"maxArgs", 3},
    {"resultArgument", 0}
}
```

Names are lowercase alphanumeric identifiers, start with a letter, and cannot
replace a built-in primitive. Separators are intentionally rejected because
G-Script normalizes legacy underscore spellings.
The result argument is a G-Script variable name; it is removed before evaluated
arguments are passed to the provider. The returned `QVariant` is stored in that
variable. Registered primitives participate in preflight validation,
autocomplete, signature help, runtime fault handling, and unload cleanup.

Example:

```gcode
M98 PinspectionCount(#Accepted, 0, 0.85)
M98 Passert(#Accepted > 0, "No acceptable parts in the pick window")
```

Primitive execution is synchronous on the plugin object's owning thread. Keep
it bounded and non-blocking; move long inference or network work to a worker and
return a result already prepared by that worker.

## Plugin-provided devices

Implement `DeltaXDeviceProvider`, declare `devices.provider`, and request
`devices.provide`. Device IDs must be namespaced lowercase IDs such as
`vendor.plc0`; they cannot silently replace built-in robot or conveyor names.

Commands submitted with `M98 Psend(vendor.plc0, "...")` pass through the same
serialized device broker and cell-state rules as built-in devices. Accept the
command quickly, perform asynchronous I/O, then call
`DeltaXHostContext::completeDeviceCommand()`. The broker correlates the active
request and resumes its owner. A plugin using `devices.command` can poll
`devices.response`, `devices.rejected`, and `devices.timeout` host events by
sequence number.

## Vision and tracking

With `vision.submit`, a plugin can submit a `QVariantMap` containing `frameId`,
`requestId`, `trackingId`, `coordinateSpace: "conveyor"`, and an `objects` list.
Each object provides numeric `x`, `y` and optional `z`, `type`, `width`,
`height`, `angle`, `confidence`, `label`, and `externalId`. The frame must match
a pending capture/detection correlation slot; direct uncorrelated frames are
rejected by the tracking pipeline.

`trackingSnapshot()` returns copies, never mutable internal object pointers.
`claimObject()`, `releaseObject()`, and `completeObject()` preserve the same
atomic ownership and lease rules used by multi-robot G-Script workers. Claim
owners are scoped as `plugin/<plugin-id>/<owner>` so one plugin cannot release
another worker's claim through the host API.

## Versioned services and events

`DeltaXServiceProvider` publishes descriptors with a namespaced ID, semantic
version, and method list. Duplicate service IDs are rejected. Consumers invoke
services through `DeltaXHostContext::invokeService()`; calls are delivered on
the provider object's owning thread. `serviceCatalog()` exposes the registered
ID, semantic version, methods, and provider plugin ID for discovery and version
negotiation.

The event stream is bounded to the latest 1,024 events. Every record contains a
monotonic sequence, publisher ID, topic, UTC timestamp, and payload. Consumers
must persist only their last processed sequence for the current session and
handle older events being evicted.

## Build the reference plugin

The reference inspection plugin demonstrates lifecycle, permissions, tracking,
panel UI, commands, a G-Script primitive, health/events, and a service.

With qmake:

```bash
mkdir build-inspection-plugin
cd build-inspection-plugin
qmake ../sdk/examples/inspection-plugin/inspection-plugin.pro
nmake        # Windows, or make on Linux/macOS
```

Or enable `DELTA_X_BUILD_REFERENCE_PLUGIN=ON` in a CMake build. Copy the result
to the plugin directory, grant its requested permissions, restart, and run:

```gcode
M98 PinspectionCount(#GoodParts, 0, 0.80)
```

The example is a contract reference, not a certified inspection model.

## Migration and testing

Keep v1/v2 interfaces only while old host integrations still require them.
Move new host interactions into v3, change metadata/IID to v3, add an explicit
permission array, and implement reversible lifecycle methods.

Run the contract and real-library lifecycle suites:

```bash
python tools/run-tests.py --test plugin_contract --test plugin_manager \
  --test gscript_analyzer --test gscript_runtime
```

Tests cover v1/v2 compatibility, v3 metadata, permissions, settings order,
activation, extension collisions, commands, services, events, dynamic G-Script
execution, device dispatch, stop, unregister, and unload.

## Remaining security boundary

API v3 controls access to supported host services but cannot stop malicious or
defective native code from reading process memory, blocking the UI, or crashing
the process. Plugins from an untrusted marketplace require a separately designed
out-of-process host, signed packages, and OS-level sandboxing.
