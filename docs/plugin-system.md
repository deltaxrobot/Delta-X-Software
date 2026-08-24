# Plugin system

Delta X Software supports native Qt plugins for optional cameras, devices,
operator panels, command providers, and future integrations. The core
application starts normally when no optional plugin is installed.

> Native plugins execute in the application process with the same permissions
> as Delta X Software. Install only plugins whose source, publisher, build, and
> dependencies you trust. A rejected plugin is never instantiated.

## Install and inspect a plugin

1. Build or obtain a plugin compiled for the same operating system,
   architecture, compiler ABI, Qt major/minor compatibility, and build mode as
   the application. A Windows DLL cannot be used on Linux or macOS.
2. Open **Modules > Plugins** in Delta X Software.
3. Select **Open Built-in Folder** and copy the plugin library into that folder.
   The usual file type is `.dll` on Windows, `.so` on Linux, and `.dylib` on
   macOS.
4. Restart Delta X Software.
5. Return to **Modules > Plugins**. Confirm that the state is `loaded`, then
   review its API version, semantic version, capabilities, source path, and any
   diagnostic.

The application scans only explicit plugin directories. It does not fall back
to scanning the executable directory. Symlinks that resolve outside a selected
directory are ignored.

## Per-user plugins

Use **Modules > Plugins > Enable per-user plugin directory**, select **Open User
Folder**, place plugins there, and restart. The directory is disabled by
default so installing a file cannot silently expand the next startup's code
surface.

Administrators may add controlled directories with the QSettings key
`PluginSystem/AdditionalDirectories`. Paths must be individual directories;
discovery is non-recursive. Changes apply at the next startup.

## Enable or disable a plugin

Use the checkbox in the **Enabled** column and restart. Disabled IDs are stored
in `PluginSystem/DisabledPluginIds`. Plugin settings are not deleted when a
plugin is disabled.

Settings are isolated by project and stable plugin ID under:

```text
PluginSystem/Projects/<project>/<plugin-id>/
```

Renaming a plugin file does not change its settings identity. Duplicates with
the same ID are rejected deterministically.

## States and troubleshooting

| State | Meaning | Action |
|---|---|---|
| `loaded` | Contract and runtime interfaces passed validation. | Review capabilities and operate normally. |
| `disabled` | The stable plugin ID is disabled in settings. | Enable it and restart if needed. |
| `rejected` | Metadata, ABI loading, identity, capability, or dependency validation failed. | Read **Details**, correct the build/runtime, and restart. |
| `unloaded` | The plugin was cleanly released during shutdown or a test. | No action required. |
| `unload-failed` | Qt or the operating system retained the library. | Close dependent UI, inspect logs, then restart. |

Common rejection causes:

- plugin API is newer than the host;
- API v2 metadata has an invalid ID, version, or capability array;
- runtime ID/version/capabilities do not match metadata;
- `panel` or `commands` is declared without its interface;
- another discovered file already owns the same ID;
- a required Qt, compiler, OpenCV, camera-vendor, or system library is missing;
- debug/release or CPU architecture does not match the host.

Camera vendor runtimes remain optional. The industrial camera plugin reports
backend availability without preventing the core application from starting.
See [GigE and USB3 cameras](camera-gige-usb3.md) and the
[industrial camera build guide](../plugin/IndustrialCamera/BUILD_INSTRUCTIONS.md).

## Develop a plugin

Use the headers in `sdk/` and start from `DeltaXPluginV2`. Metadata is checked
before any plugin code runs, then the host verifies that runtime identity,
version, and capabilities match it.

Required base interface:

```cpp
#include "DeltaXPluginV2.h"

class ExamplePlugin final : public QObject, public DeltaXPluginV2
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV2_iid FILE "ExamplePlugin.json")
    Q_INTERFACES(DeltaXPluginV2)
    // Implement id, displayName, version, capabilities and settings methods.
};
```

To provide UI, also inherit `DeltaXPanelProvider`, list it in `Q_INTERFACES`,
return `panel` from `capabilities()`, and add `"panel"` to metadata. To accept
structured host commands, do the same with `DeltaXCommandProvider` and
`"commands"`.

The host owns the loader, not the plugin root object. Plugins must release
threads, devices, and child resources in their destructor. The host unloads
plugins in reverse load order; plugin code must never delete its own root
instance.

## Migrate API v1

API v1 remains loadable for existing third-party binaries. Its IID is frozen,
and missing `apiVersion` is interpreted as v1. For new releases:

1. Keep the existing `DeltaXPlugin` implementation temporarily if current host
   integrations still consume its legacy domain signals.
2. Also implement `DeltaXPluginV2` plus the relevant capability interfaces.
3. Change `Q_PLUGIN_METADATA` to `DeltaXPluginV2_iid` and metadata
   `apiVersion` to `2`.
4. Add a stable lowercase ID, semantic plugin version, and complete capability
   list.
5. Run `python tools/run-tests.py --test plugin_contract --test plugin_manager`.

The first-party industrial camera plugin demonstrates this dual-interface
migration.

## Automated contract tests

The cross-platform `plugin_manager` suite builds a real fake plugin and tests
discovery, API v2 capability casts, structured commands, project settings,
disabled IDs, duplicate rejection, missing paths, and unload. Run it with:

```bash
python tools/run-tests.py --test plugin_contract --test plugin_manager
```
