# Delta X UI Style Guide

Delta X uses the **Industrial Workstation** visual style: a neutral,
medium-density interface designed for long-running machine operation. Blue is
reserved for primary actions and selection, while green, amber, and red carry
machine-state and safety meaning.

One application-level theme is implemented in `UiTheme`. New windows, dialogs,
and plugin panels inherit this theme automatically. Do not add a second
window-level stylesheet.

## Design tokens

The shared palette defines four surface levels (`window`, `surface`, `raised`,
and `input`), two border levels, primary and muted text, one blue accent, and
semantic success, warning, and error colors. Dark, Light, and Auto modes use the
same component geometry and only replace these tokens.

## Component rules

- Keep visible text minimal: short functional labels, units and actionable
  status only. Put usage instructions in tooltips or Help, not permanent
  explanatory paragraphs. Do not remove critical fault or safety warnings.
- Use layouts rather than fixed coordinates. Use 6 px spacing for compact tool
  rows, 8 px for normal forms, and 12 px between major sections.
- Use the application font for controls and labels. Reserve a monospace font for
  G-Script, logs, variable values, and protocol data.
- Let standard buttons, inputs, tabs, views, headers, scrollbars, and splitters
  inherit `UiTheme`. Do not restyle them in `.ui` files.
- Use a widget property for a semantic variation instead of a color stylesheet.
  Supported examples are `navigationSelected`, `statusRole` (`success`,
  `warning`, `danger`, or `info`), `controlRole` (`primary`, `success`,
  `warning`, `danger`, or `quiet`), `settingsLabel`, and `previewField`.
- Keep safety actions recognizable: start is success, stop/reset is error,
  restore is warning, and the primary commit action uses the accent color.
- Every icon-only control needs a tooltip and an accessible name.
- Controls must remain readable in normal, hover, focus, pressed, checked, and
  disabled states in both Dark and Light themes.
- Standard buttons and single-line inputs have a 30 logical-pixel baseline;
  text, fonts, and layouts may increase it. Do not add a smaller fixed height.
  Icon-only controls use `iconOnly=true` with at least 30 x 30 logical pixels.
- Jogging is a separate component: step buttons are 48 x 48 and continuous
  motion strips keep their narrow hit regions. Do not apply toolbar padding to
  `Func=Jogging` controls or change their motion signal bindings during styling.
- Navigation artwork is monochrome and follows the palette, including selected
  and disabled states. Preserve colors in domain-specific camera/robot artwork.
- Checkboxes, mixed-state checkboxes, radio buttons, combo arrows, and spin-box
  arrows have explicit theme resources. Always test their checked/unchecked
  states after changing global styles.
- `UiTheme::prepareForm()` removes legacy Designer styles and normalizes old
  control/layout height limits. Only pass visual canvases as preserved roots;
  preserving an entire control panel will prevent it from following the theme.
- Scrollable forms must derive their minimum height from their layout, not a
  hardcoded 2000/4000 px content height. Text and controls must remain reachable
  by scrolling when the workspace is narrow.
- Prefer `isHidden()` for explicit panel visibility state. `isVisible()` also
  reflects hidden ancestors and can misreport panels in an inactive project tab.
- Collapsible groups use `collapsibleSection=true` and explicit right/down
  chevrons. An unchecked native group indicator can be invisible under a custom
  stylesheet; do not rely on native indicator rendering.
- The Program editor gets the remaining vertical space. Problems, Watch,
  Threads, and Console share the optional **Details** pane. Software cell faults
  remain visible even when Details is closed; G-Script errors open Problems.
- The Robot connection header remains visible above **Control / I/O / Setup**.
  Model/DOF selection belongs in Setup, not in the always-visible header.

## Robot panel

`RobotPanelLayout::setup()` arranges the generated Robot form without creating
device/controller objects or emitting commands. It reuses widget identities and
existing command bindings. Do not reparent individual I/O controls out of their
bank: the runtime resolves input options by `sender()->parent()`.

- **Control:** coordinates with Enter-to-move tooltips, Home, Motor
  hold, Refresh, Copy, XYZ jogging, optional rotary jogging, step size and feed
  rate. Motor hold is not an emergency stop.
- **I/O:** model-specific output and input banks, expanded on their own page.
  Output changes are immediate. Input options retain their existing M07/M08
  behavior; the UI does not infer firmware timing units.
- **Setup:** model, controlled axes, acceleration, jerk, start and end speeds.
  Changing configuration or pressing Enter in parameter fields can send commands.

Unsupported rotary controls are disabled according to the selected DOF; the
rotary jogging row is hidden for 3-axis robots. This is a UI affordance, not a
replacement for command validation or hardware safety interlocks.

The layout uses vertical scrolling on narrow docks, not compressed controls.
Keep continuous-jog press/release signals and the 48px step-button / 10px strip
geometry unchanged. Automated tests cover 380/480/720px docks, Dark/Light, 3/6
axes, child containment, and zero command-control activations during setup and
tab navigation. Native runtime verification is still required for a release.

## Plugin UI

Plugin panels are children of the host application and inherit the application
theme. A plugin may color domain-specific content such as Blockly blocks or a
camera health indicator, but it should not redefine common Qt controls. Prefer
dynamic properties and object names that the host theme can target.

## Review checklist

1. Test at 100%, 125%, and 150% display scaling.
2. Test Dark and Light, plus Auto on at least one supported operating system.
3. Resize the main window through the 1380 px responsive breakpoint.
4. Verify keyboard focus, tab order, tooltips, and icon-only accessible names.
5. Check that status meaning is not conveyed by color alone.
6. Run `python tools/bootstrap.py build --build-type Release` and the repository
   test suite before submitting a change.

## Automated visual regression checks

Run `python tools/run-tests.py --test ui_theme` for palette contrast, live syntax
theme switching, icon resources, jogging geometry, navigation width, and form
layout checks. See [the test guide](../tests/README.md#ui-regression-checks) for
offscreen preview and scaling commands. Rendered form previews are diagnostic
artifacts, not proof of live device interaction or native window behavior.
