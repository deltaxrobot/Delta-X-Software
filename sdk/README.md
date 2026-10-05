# Delta X plugin SDK

API v3 is the current contract for new plugins. It adds an explicit lifecycle,
a permission-checked host context, dynamic G-Script primitives, plugin-provided
devices, and versioned plugin-to-plugin services. API v1 and v2 plugins remain
loadable.

Read the complete [plugin system guide](../docs/plugin-system.md) before
shipping a plugin. A buildable reference implementation is available in
[`examples/inspection-plugin`](examples/inspection-plugin/README.md).

## Minimal API v3 plugin

```cpp
#include "DeltaXHostContext.h"
#include "DeltaXPluginV3.h"

class MyPlugin final : public QObject, public DeltaXPluginV3
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV3_iid FILE "MyPlugin.json")
    Q_INTERFACES(DeltaXPluginV2 DeltaXPluginV3)

public:
    QString id() const override { return "example.myplugin"; }
    QString displayName() const override { return "My Plugin"; }
    QString version() const override { return "1.0.0"; }
    QStringList capabilities() const override { return {}; }
    void loadSettings(QSettings&) override {}
    void saveSettings(QSettings&) const override {}
    bool initialize(DeltaXHostContext* context, QString*) override
    {
        m_context = context;
        return context != nullptr;
    }
    bool start(QString*) override { return true; }
    void stop() override { m_context = nullptr; }

private:
    DeltaXHostContext* m_context = nullptr; // Host-owned; never delete it.
};
```

Metadata is validated before plugin code is instantiated:

```json
{
  "apiVersion": 3,
  "pluginVersion": "1.0.0",
  "name": "example.myplugin",
  "capabilities": [],
  "permissions": []
}
```

Runtime ID, version, and capabilities must exactly match metadata. IDs are
stable lowercase identifiers and versions use semantic versioning. Every
permission must be a known SDK permission and is denied until the operator
grants it under **Modules > Plugins > Permissions**.

## Extension interfaces

- `DeltaXPanelProvider`: persistent native Qt operator panel (`panel`).
- `DeltaXCommandProvider`: structured commands and results (`commands`).
- `DeltaXGScriptProvider`: typed descriptors and synchronous primitives
  (`gscript.primitives`, permission `gscript.register`).
- `DeltaXDeviceProvider`: namespaced asynchronous devices
  (`devices.provider`, permission `devices.provide`).
- `DeltaXServiceProvider`: versioned service methods for other plugins
  (`services.provider`, permission `services.provide`).

List each implemented interface in `Q_INTERFACES`. The host checks capability,
interface, and permission consistency before registering an extension.

`DeltaXHostContext` exposes project variables, a bounded event stream, the
device command broker, correlated vision submissions, tracking snapshots and
claims, service calls, health, telemetry, logging, and controlled cell stop.
Every state-changing call is permission checked. Plugins never receive raw
pointers to the application's managers. Consumers can use `serviceCatalog()`
to discover service IDs, semantic versions, methods, and provider plugin IDs
before invoking a service.

## Lifecycle and ABI policy

The host calls methods in this order:

1. construct and validate the plugin;
2. `loadSettings()` in the plugin's project-specific settings group;
3. `initialize(context)`;
4. `start()`;
5. register granted extension interfaces;
6. `stop()` during reverse-order shutdown;
7. invalidate the context and unload the library.

Release all threads, timers, devices, panels, and callbacks before `stop()`
returns. Never delete the plugin root or host context.

`DeltaXPlugin` v1 and `DeltaXPluginV2` are frozen compatibility surfaces. Do
not add, remove, reorder, or change virtual methods in a published interface;
publish a new IID for a breaking change. New plugins should target v3.
