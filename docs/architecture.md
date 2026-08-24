# Architecture

## System context

Delta X Software coordinates cameras, image processing, conveyor tracking,
multiple Delta robots, encoders, conveyors, sliders, generic I/O, and G-Script.
Firmware performs low-level motion; certified safety remains outside the desktop
application.

```text
UI / Operator tools
        |
Application controllers and CellSupervisor
        |
G-Script ---- Tracking ---- Vision pipeline ---- VariableManager
        |          |                |
        +----------+----------------+
                   |
          DeviceCommandBroker
                   |
             DeviceManager
                   |
      Robot / Conveyor / Encoder / I/O
```

## Dependency rules

1. UI may call application controllers, not hardware implementations directly.
2. Every actuator command is submitted to `DeviceCommandBroker` with an owner and
   origin. Responses return only to that owner.
3. `CellSupervisor` owns cell-level software state and initiates controlled stops.
4. `TrackingManager` owns object lifecycle, UID association, health, claim leases,
   release, and completion.
5. `VariableManager` is the scoped state exchange; runtime telemetry must not be
   persisted unless explicitly classified as configuration.
6. Camera vendor SDKs remain behind optional plugins and runtime-loaded adapters.
7. External detectors use framed DXV1 messages with frame/request/tracking IDs.

## Threading model

- Qt GUI objects remain on the GUI thread.
- Devices, G-Script workers, camera capture, and tracking may run on worker threads.
- Cross-thread calls use queued Qt signals or `QMetaObject::invokeMethod`.
- A `Tracking` instance must be transferred with `Tracking::MoveToThread()` so
  its virtual encoder and timer move to the same worker; UI code must use its
  queued configuration slots and immutable/thread-safe getters.
- Serial/socket objects are created and operated only on their device worker.
  Other threads consume atomic state/position snapshots and submit mutations
  through `DeviceManager` queued slots.
- Mutable collections shared across threads require an owner thread, lock, or
  immutable snapshot; direct widget access from a worker is forbidden.

## Safety and fault policy

A timeout, stale encoder/vision state, rejected ownership transition, or G-Script
fault must terminate the automation path deterministically. A controlled stop
clears pending commands, emits device-specific stop commands, stops active scripts,
and requires operator acknowledgement. It is a process-control safeguard, not a
certified safety function.

## Migration direction

`RobotWindow` and `GcodeScript` are legacy monoliths. New work should extract
cohesive services behind QObject interfaces and tests. Refactoring should be
incremental: preserve behavior, add characterization tests, move one responsibility,
then remove the old path.
