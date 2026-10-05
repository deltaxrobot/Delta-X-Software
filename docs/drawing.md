# Drawing

Drawing creates planar pen/laser paths and sends a G-Script program to the
Program editor. Loading, converting and exporting never move the robot.

## Quick start

1. Open **Drawing**. Set **Width / Height** in millimetres.
2. Select **Line**, **Rectangle**, **Circle** or **Arc** and drag on the canvas.
   Circle: drag from centre to rim. Arc: drag the diameter of a counterclockwise
   semicircle. **Pan**, **+ / −**, and **Fit** change only the view.
3. Teach three separated, non-collinear points on the physical drawing surface.
   Copy robot coordinates, then use **Paste** beside A, B and C, or type
   `X, Y, Z`. The tool tip must touch the surface at each taught point.
4. Set **Travel Z** to an absolute robot Z above the entire drawing and any
   obstacles, but still inside the robot's reachable workspace. For example,
   a horizontal surface at Z = −350 and Travel Z = −340 gives 10 mm clearance.
   The exporter requires at least 0.5 mm above every path vertex; this minimum
   is input validation, not a physical safety guarantee.
5. Choose **Pen** and conservative speeds/acceleration for the installed tool.
   **Send to G-code Editor** generates code and asks before replacing existing
   editor contents. Editor Undo can recover the previous text.
6. Inspect the generated program. Home the robot separately, verify the work
   envelope and fixture clearance, and make an elevated/low-speed trial with
   the tool inactive before touching the surface. Run from the Program editor.

## Coordinates and drawing plane

- Origin is robot X=0, Y=0; +X is right, +Y is up. Units are mm.
- A/B/C define only surface Z as a function of robot X/Y. They do **not**
  rotate, translate, or scale the artwork, and they do not define a clipping
  triangle. Points outside that triangle extrapolate the plane.
- Width/Height define the displayed canvas and the size of the next converted
  image. Existing paths keep their physical coordinates when these values,
  the window size, or zoom change. Both image dimensions are applied; set their
  ratio explicitly if you need to preserve the original image aspect ratio.
- The dashed canvas border is a size reference, **not** a robot workspace limit.
  Robot-specific reachability and collision checking are not implemented here.

## Import native vector artwork

Use **Import SVG / DXF…** when artwork comes from Inkscape, Illustrator,
CorelDRAW, Affinity Designer or CAD software. This path does not rasterize the
artwork and does not use Threshold or Spacing.

- SVG keeps its physical `width` / `height`, `viewBox`, nested transforms and
  the geometry of line, rectangle, circle, ellipse, polyline, polygon and path
  elements. Path commands M/L/H/V/C/S/Q/T/A/Z are supported. Curves are
  flattened to short robot line segments only after all transforms are applied.
- Export SVG with a physical page size in `mm`, `cm` or `in`. Unitless SVG
  dimensions are interpreted at the SVG standard 96 DPI and reported after
  import. The page centre becomes robot X=0, Y=0.
- Convert text to paths in the authoring application. SVG text, embedded images,
  clones (`use`), clipping and masks are skipped and reported rather than being
  silently rasterized.
- ASCII DXF supports LINE, LWPOLYLINE/POLYLINE (including bulge arcs), CIRCLE,
  ARC and ELLIPSE. `$INSUNITS` is converted to millimetres; missing units are
  treated as millimetres and reported. DXF geometry keeps its dimensions and is
  centred from its bounds on robot X=0, Y=0. Binary DXF is not supported.

The imported result is normal editable Drawing geometry. Undo restores the
previous canvas, and **Save Drawing…** stores a portable `.dxdraw` copy. Always
check the displayed dimensions before G-code export, especially for files from
third-party CAD software. Ready-to-import examples are in
`script-example/drawing/vector-import-sample.svg` and
`script-example/drawing/vector-import-sample.dxf`.

## Trace an image

Use **Load Image…** for PNG, JPEG or BMP. Set Threshold and Invert,
then select:

- **Threshold / Line**: connected black runs, with a lift between runs/rows.
- **Threshold / Dot**: one surface touch per black sample. No timed dwell is
  inserted; dot intensity/ink deposition depends on the physical tool.
- **Vectorize**: closed contours of black regions, including holes.

**Spacing** controls the maximum raster sampling interval in mm. Dense inputs
are rejected with an actionable error instead of generating unbounded code.
Use **Convert to Paths** to replace the current paths (Undo is available).
The preview is the thresholded source; the canvas is the actual exported path.
Changing image parameters does not silently replace existing paths.

Raster images are bounded to 1600 pixels on their longest side for processing.
Grayscale power modulation is not supported. Use **Import SVG / DXF…** for
lossless vector dimensions instead of image tracing.

## Editing and files

- **Undo / Redo** work for drawing, clear, conversion and opening documents.
  Ctrl+Z / Ctrl+Y work while the canvas has focus. Esc cancels a drag.
- **Save Drawing…** writes a portable, versioned `.dxdraw` JSON document
  containing mm paths and canvas size. Saving is atomic.
- **Open Drawing…** validates the complete document before changing the canvas.
- Geometry must be saved explicitly before closing the application. The source
  image is not embedded. Project settings save image-conversion parameters,
  motion values and plane points separately. Recheck taught points after moving
  a tool, robot, fixture or project to another machine.

## Generated motion and laser limits

The program uses G90, M204 and G01. It first lifts at the current XY, travels at
Travel Z, descends at drawing speed, follows plane-compensated paths and lifts
before the next XY travel. It does not auto-home, select a tool, or run itself.
The initial lift also needs physical clearance at the robot's starting XY.

Laser mode retains the existing M03 S0 / M03 S255 protocol and requests an
explicit warning acknowledgement on export. It switches off before motion,
switches on only after reaching a stroke's start and switches off before lifting.
It does **not** configure the laser head, prove firmware compatibility, implement
interlocks, or guarantee laser shutdown after interruption. Use only after
verifying the firmware/tool mapping, hardware interlocks and protective measures.
Default tool is Pen. No laser or robot movement is part of the automated tests.

## Developer notes

`DrawingProgram` is a UI-independent validation/raster/G-code core.
`DrawingWidget` owns mm geometry, view transforms, undo history and documents.
`DrawingExporter` binds image processing and the compact panel to the core.
Run `python tools/run-tests.py --test drawing --jobs 4` for regression tests.
