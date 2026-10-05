# Reference inspection plugin

This API v3 example is intentionally small enough to audit while demonstrating
the complete extension lifecycle:

- permission-checked host initialization and reversible start/stop;
- a native operator panel;
- the structured `inspect` command;
- `M98 PinspectionCount(result, trackingId, minimumConfidence)`;
- the versioned `inspection.quality/evaluate` plugin service;
- tracking snapshot access, health reporting, and event publication.

Build out of source with qmake or CMake, copy the resulting library into the
Delta X Software plugin directory, restart, select it under **Modules >
Plugins**, grant the requested permissions, and restart again. It is a
reference contract implementation, not a certified quality-inspection model.
