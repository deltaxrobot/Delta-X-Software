# Delta X Variable Manager

## Purpose

`VariableManager` is the shared data store used by the UI, devices, G-Script, vision, and tracking. It does not use a mutable global prefix or expose live pointers to tracking object lists. Every window and project reads and writes through an isolated namespace; for example, `project0.robot0.X` and `project1.robot0.X` are independent variables.

## Naming rules

- In G-Script and project-owned components, use relative names such as `#Objects.0.X`, `#Target.UID`, or `robot0.X`. The application adds `projectN` automatically.
- Project-owned components must use the `...Scoped(project, key, ...)` APIs.
- Legacy `getVar`, `updateVar`, and `removeVar` APIs accept absolute keys only. They remain available for administration screens and compatibility code.
- Leading `#`, whitespace, and redundant separators are normalized automatically.
- Removing `project1` never removes `project10`.

## Data lifetimes

| Lifetime | Examples | Stored in `settings.ini` |
|---|---|---|
| `Persistent` | Calibration, setpoints, COM ports, matrices, recipes | Yes |
| `Runtime` | Current robot pose, tracks, UIDs, claims, frame state | No |

High-frequency runtime data therefore does not grow the configuration file or restore stale tracks after the application restarts.

## Atomic batch updates

Related values are written with `updateBatchScoped`. The complete batch holds the write lock only once, and a reader calling `snapshot()` observes either the state before or the state after the batch, never a partially updated state.

```cpp
QHash<QString, QVariant> values;
values.insert("robot0.X", x);
values.insert("robot0.Y", y);
values.insert("robot0.Z", z);

VariableManager::instance().updateBatchScoped(
    ProjectName, values, VariableManager::Persistence::Runtime);
```

## Tracking variables

Each tracking worker publishes a copied snapshot as one runtime batch:

```text
project0.Objects.Count
project0.Objects.0.UID
project0.Objects.0.Type
project0.Objects.0.X / Y / Z
project0.Objects.0.W / L / A
project0.Objects.0.State
project0.Objects.0.IsPicked
project0.Objects.0.IsClaimed
project0.Objects.0.ClaimOwner
project0.Objects.0.ClaimExpiresAt
project0.Objects.0.Confirmed
project0.Objects.0.HitCount
project0.Objects.0.MissedFrames
project0.Objects.0.LastSeenAt
```

`State` is one of `TENTATIVE`, `CONFIRMED`, `LOST`, `CLAIMED`, or `PICKED`. When several robots share a conveyor, G-Script must use claim, release, and complete primitives instead of writing `IsPicked` directly.

### Publication rate and telemetry

Tracking updates its internal pose for every encoder sample, but copies snapshots into `VariableManager` at `PublishIntervalMs` (50 ms by default). Association and claims always use the newest pose inside the tracking thread while the UI and G-Script avoid thousands of batches per second. Frame commits, claims, releases, completions, and forced publication commands still publish immediately.

Runtime variables under `Tracking.N.*` expose state, pending frame and encoder queues, encoder and vision age, overflow counters, latency, and publication statistics. Persistent settings use `trackingN.Realtime.*`; telemetry under `Tracking.N.*` is never stored in `settings.ini`.

## Thread-safety contract

- Reads use a read lock, allowing concurrent readers.
- Writes and batches use a write lock.
- Signals are emitted only after the lock is released, preventing read-back callbacks from deadlocking.
- Object lists are copied into snapshots; no component retains a `QVector<ObjectInfo>*` owned by the tracking thread.
- The variable tree model is held through `QPointer`, so closing a window cannot leave a dangling model pointer.

## Compatibility and storage

Legacy files beside the executable are copied to the application data directory when required. New storage uses a manifest with typed metadata and preserves `QVector3D`, `QPointF`, `QRectF`, `QPolygonF`, `QTransform`, `QMatrix`, JSON maps/lists, and basic Qt types. Unsupported values are skipped with a warning instead of invalidating the entire save operation.

## Tests

`tests/variable_manager` covers namespaces, deletion boundaries, persistent/runtime classification, signal re-entry, snapshot copies, and atomic concurrent reads and writes. `tests/tracking_claim` covers multi-robot ownership, leases, lifecycle, association, and frame/encoder synchronization.
