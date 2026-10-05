# Block Programming operator guide

The Block Programming plugin provides a Blockly-style visual canvas for
assembling connected blocks and generating standard Delta X G-Script without
manually typing every statement. It runs entirely inside Delta X Software and
remains usable without internet access.

## Enable the plugin

Block Programming is an **experimental, opt-in plugin**. It is included in the
normal CMake build and official packages, but it is disabled and hidden from the
Program workspace by default. Open **Modules > Plugins**, check
**Block Programming (Experimental)** in the Enabled column, and restart. The
Blocks button and Program > Blocks mode appear only while the plugin is enabled.
The retired browser-based Blockly server is also disabled by default and is not
required by this native plugin.

For a library built separately, open **Modules > Plugins > Open Built-in
Folder**, copy the matching `.dll`, `.so`, or `.dylib` into that folder, enable
it in the list, and restart.

Select `deltax.block-programming`, choose **Permissions...**, and grant:

| Permission | Why it is needed |
|---|---|
| `gscript.read` | List workers and validate generated source with the host analyzer. |
| `gscript.edit` | Load generated source into a worker editor. |
| `gscript.run` | Start or stop the selected G-Script worker. |
| `health.report` | Report plugin readiness in the plugin manager. |

The editor still supports offline block construction, save, and export when
G-Script permissions are denied. Host validation and worker controls remain
disabled until permission changes are applied by restarting the application.

## Understand the workspace

The **Block Programming** module contains five working areas:

1. **Template and file bar** creates, opens, saves, or exports a program.
2. **Worker bar** selects a G-Script worker and exposes Load, Run, and Stop.
3. **Toolbox** searches and groups the available blocks by purpose. Drag a
   block from here onto the canvas.
4. **Workspace canvas** displays puzzle-shaped execution stacks and C-shaped
   containers. Drag blocks to reorder them, drop on a container to nest, or
   use Up, Down, Nest, and Unnest. Drag empty space to pan and use Ctrl+wheel,
   +/-, or Fit to control the view.
5. **Properties and Generated G-Script** edit the selected block and show the
   exact source plus diagnostics.

Double-clicking a toolbox block, or pressing Enter on it, is a
keyboard-friendly alternative to dragging.
When a container such as **If**, **While**, or **Repeat** is selected, a new
block is inserted inside it. Otherwise it is inserted after the current block.
Press Delete to remove the selected block.

## Available block groups

| Group | Blocks | Purpose |
|---|---|---|
| Basics | Comment, Set variable, Raw G-Script | Documentation, variables, and an escape hatch for reviewed source. |
| Control | If, Else, While, Repeat, Assert, Wait until | Branching, loops, preconditions, and bounded process waits. |
| Timing and logging | Delay, Log | Cooperative delays and operator/runtime messages. |
| Devices | Send device command, Home robot, Move robot | Serialized robot, vacuum, gripper, or external device operations. |
| Conveyor | Set conveyor speed, Stop conveyor | Conveyor process control through G-Script. |
| Vision | Capture and detect, Pause camera, Resume camera | Correlated image acquisition and tracking ingestion. |
| Tracking | Claim object, Release object, Complete object | Atomic multi-robot ownership of tracked objects. |

Expressions use normal G-Script syntax. For example, enter `#Target.X` for a
tracked X coordinate, `#Target.Found == 1` for a condition, or `"robot0"` for a
string literal. The Raw G-Script block always emits a warning because its text
cannot be structurally checked as a block before host validation.
Text fields may contain single or double quotes, but not both in the same
value, because the current G-Script runtime has no escape sequence for a quote
inside its matching string delimiter. The compiler reports `BP1109` instead of
emitting ambiguous source.

## Run the software self-test

For a safe first check, select **Software self-test**. It exercises variables,
a nested Repeat block, logging, an assertion, a bounded condition wait and a
cooperative delay. The generated program contains no device, camera, conveyor,
robot or output command. A successful run prints `PASS block programming`.

The editable `.dxblocks` fixture and its generated `.gcode` are available in
`script-example/block-programming/` for regression testing and code review.

## Create a vision-and-pick program

For a first commissioning pass:

1. Create **Vision tracking loop** on a dedicated worker. Confirm that its
   tracking ID matches the calibrated camera/tracking pipeline.
2. Create **Robot conveyor pick worker** on another worker. Set its robot,
   device, owner, safe Z, pick Z, and process expressions to match the cell.
3. Confirm that claim ownership is unique for each robot worker. Never let two
   workers pick from an unclaimed snapshot.
4. Add explicit assertions for calibrated limits and tool readiness.
5. Resolve every error, then choose **Load into editor** and review the source.
6. Test with motion power disabled or in an approved simulation/dry-run mode.
7. Enable one subsystem and one robot at a time before multi-robot operation.

The templates are starting points, not cell configuration. Placement rules,
class routing, approach/retract motion, failure recovery, reject behavior, and
tool feedback must be adapted to the physical system.

## Save, exchange, and recover programs

Use `.dxblocks` as the editable source of truth. It is versioned JSON and is
suitable for source control and code review. Exported G-Script is a generated
artifact: review it before use, but edit the block program when changes must be
preserved.

The last in-memory workspace and selected worker are saved in project-scoped
plugin settings. Use **Save...** for an explicit, portable project file rather
than relying only on automatic settings.

## Validation and execution

Validation occurs in two stages:

1. the block compiler checks unknown blocks, required fields, nesting,
   `else` placement, leaf children, size limits, and unsafe raw-source usage;
2. the host G-Script analyzer checks the generated statements and registered
   primitives.

**Load into editor** never starts a worker. **Run** displays an automation
warning, then asks the host to validate again and enforce the cell supervisor.
The host rejects an invalid worker index, a running worker, or a cell state that
does not permit automation. **Stop** is a controlled worker stop request; the
hardware E-stop remains the independent emergency control.

## Pre-run safety checklist

- E-stop, guards, interlocks, and safe torque controls are tested.
- Robot, camera, conveyor, encoder, TCP/tool, and conveyor-coordinate
  calibrations are current and versioned.
- Safe Z, pick Z, placement coordinates, workspace limits, speeds, and
  accelerations are verified for every robot.
- Vacuum/gripper feedback and loss-of-part recovery are tested.
- Detection class, angle convention, confidence rules, encoder direction, and
  latency compensation are verified at production speed.
- Pick windows do not overlap unsafely, and object claims expire/recover as
  intended after a fault.
- The generated G-Script has been reviewed and dry-run at reduced speed.

## Troubleshooting

- **No workers or disabled buttons:** grant the required G-Script permissions,
  restart, and press **Refresh workers**.
- **Plugin is rejected:** use a plugin built for the same OS, architecture,
  compiler ABI, Qt major/build mode, and API v3 host.
- **Cannot load:** stop the selected worker; running worker source cannot be
  replaced.
- **Cannot run:** fix diagnostics and confirm that the cell supervisor permits
  automation. Home the robot when requested.
- **Tracking fields are empty:** run the correlated capture/detection pipeline
  and verify the tracking ID before the pick worker.
- **Program opens as unsupported:** the file is not a version-1
  `deltax-block-program` document or exceeds parser limits.

See [G-Script runtime](gscript-runtime.md),
[multi-robot conveyor sorting](multi-robot-conveyor-sorting.md), and the
[plugin system](plugin-system.md) for the underlying runtime contracts.
