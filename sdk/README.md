# Delta X plugin SDK

API v2 is the current plugin contract. It keeps the base interface limited to
Qt Core types and exposes UI and command handling as optional capabilities.
See the [plugin system guide](../docs/plugin-system.md) for installation,
operations, security, troubleshooting, and v1 migration.

## Minimal v2 plugin

Implement `DeltaXPluginV2` and publish the v2 IID:

```cpp
class MyPlugin final : public QObject, public DeltaXPluginV2
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DeltaXPluginV2_iid FILE "MyPlugin.json")
    Q_INTERFACES(DeltaXPluginV2)

public:
    QString id() const override { return "example.myplugin"; }
    QString displayName() const override { return "My Plugin"; }
    QString version() const override { return "1.0.0"; }
    QStringList capabilities() const override { return {}; }
    void loadSettings(QSettings&) override {}
    void saveSettings(QSettings&) const override {}
};
```

The matching metadata is validated before plugin code is instantiated:

```json
{
  "apiVersion": 2,
  "pluginVersion": "1.0.0",
  "name": "example.myplugin",
  "capabilities": []
}
```

The runtime `id`, `version`, and capability list must exactly match metadata.
IDs are stable lowercase identifiers. Versions use semantic versioning.

## Optional capabilities

- `panel`: implement `DeltaXPanelProvider` and return a persistent `QWidget`.
- `commands`: implement `DeltaXCommandProvider` for structured commands and
  results.
- Domain capabilities such as `camera.capture` declare host integration. A
  domain interface should be introduced before adding domain-specific types to
  the base API.

List every implemented interface in `Q_INTERFACES`. The host rejects a plugin
that declares `panel` or `commands` without implementing its interface.

## Compatibility policy

`DeltaXPlugin` and `DELTA_X_PLUGIN_V1_IID` are frozen compatibility surfaces.
Plugins with missing `apiVersion` are treated as v1. New plugins must use v2.
Do not add, remove, reorder, or change virtual methods within a published API or
capability interface; publish a new IID for a breaking change.
