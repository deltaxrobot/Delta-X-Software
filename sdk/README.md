# Delta X plugin SDK

Plugins implement `DeltaXPlugin`, use `Q_INTERFACES(DeltaXPlugin)`, and publish
metadata with the shared IID:

```cpp
Q_PLUGIN_METADATA(IID DeltaXPlugin_iid FILE "MyPlugin.json")
```

The metadata file must declare the host API it targets:

```json
{
  "apiVersion": 1,
  "pluginVersion": "1.0.0",
  "name": "myplugin"
}
```

`apiVersion` is the binary/API contract. The host rejects a different or invalid
version before instantiating the plugin. Plugins without this field are treated
as legacy API v1 for backward compatibility. `pluginVersion` is the plugin's own
release version and should follow semantic versioning.

Do not add, remove, or reorder virtual methods in `DeltaXPlugin` within an API
version. A breaking interface change requires a new IID/API version, a migration
note, and loader support for the desired compatibility window.
