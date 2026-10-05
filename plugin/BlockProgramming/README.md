# Block Programming plugin

Block Programming is an offline, native Qt Blockly-style editor that builds
validated G-Script from connected visual blocks. It does not load a browser,
CDN, JavaScript runtime, or remote execution endpoint.

This plugin is experimental and disabled by default. Delta X Software keeps
G-Script as the primary programming interface until the visual workflow is
ready for general production use.

The plugin provides:

- a searchable toolbox and zoomable, pannable block canvas;
- puzzle-shaped stack blocks and C-shaped containers with drag-and-drop nesting;
- nested control-flow blocks for `if`, `else`, `while`, and `repeat`;
- robot, conveyor, device, vision, tracking, timing, assertion, logging, and
  variable blocks;
- editable block properties and a live generated G-Script preview;
- block-structure diagnostics followed by host G-Script validation;
- `.dxblocks` JSON import/export and G-Script export;
- explicit load, run, and stop controls for a selected G-Script worker;
- reusable `catalog`, `template`, and `compile` plugin commands;
- starter templates for vision capture and conveyor pick workers.

## Build

The root CMake build includes this plugin by default:

```bash
cmake --preset developer-release
cmake --build --preset developer-release --parallel 2
```

Disable it only when producing a minimal host build:

```bash
cmake --preset developer-release -DDELTA_X_BUILD_BLOCK_PROGRAMMING_PLUGIN=OFF
```

It can also be built independently with qmake:

```bash
mkdir build-block-programming
cd build-block-programming
qmake ../plugin/BlockProgramming/block-programming.pro
nmake                 # Windows
# make                # Linux or macOS
```

The compiler and Qt ABI must match the host application. Copy the resulting
library into the application's built-in plugin folder if it was built
separately.

## First use

1. Start Delta X Software and open **Modules > Plugins**.
2. Check **Block Programming (Experimental)** in the Enabled column.
3. Select `deltax.block-programming`, open **Permissions...**, and grant
   `gscript.read`, `gscript.edit`, `gscript.run`, and `health.report`.
4. Restart the application, then open **Program > Blocks**.
5. Drag blocks from the toolbox onto the canvas, press Enter on a selected
   toolbox block, or select a starter template.
6. Connect blocks into a stack. Drop on a C-shaped container to nest, or use
   **Nest** and **Unnest**. Select a block to edit its properties.
7. Resolve every error in **Diagnostics** and review **Generated G-Script**.
8. Choose a G-Script worker. Use **Load into editor** for review without
   starting motion, or **Run** after completing the cell safety checklist.
9. Save the editable program as `.dxblocks`; optionally export the generated
   `.gcode` or `.dtgc` file.

Read the complete [operator guide](../../docs/block-programming.md), including
the safety boundary, block reference, templates, and troubleshooting.

## Command API

Other host integrations can invoke this plugin through
`PluginManager::executeCommand()`:

- `catalog`: returns block definitions and template names;
- `template` with `{ "name": "Robot conveyor pick worker" }`: returns the
  document, generated script, diagnostics, and validity;
- `compile` with `{ "document": <dxblocks object> }`: validates and compiles
  an in-memory document without opening the panel.

The `.dxblocks` format has an explicit `format` identifier and version. Input
is bounded to 2,000 blocks and 32 nesting levels before compilation.
Text containing both single and double quotes is rejected because the current
G-Script runtime does not define an escaped-quote representation.

## Safety boundary

Generated code is automation source code, not a safety function. The plugin
does not replace guarding, E-stop circuits, safe motion limits, commissioning,
tool checks, calibration, dry runs, or operator authorization. The host still
applies G-Script validation and cell-supervisor checks before execution.
