# Camera-to-Robot Calibration Guide

The **Calibration** workspace converts camera-image coordinates into robot-workspace
coordinates and provides the supporting direction-vector, verification, and
tracking-runtime utilities used by a conveyor cell. Complete calibration with the production camera resolution,
lens settings, mounting position, and conveyor height. Changing any of these
invalidates the result.

## Before you start

1. Mount the camera and robot rigidly and level the working conveyor plane.
2. Select the production camera resolution and disable any automatic crop or
   resize that will not be used during production.
3. Home the robot, verify its tool center point, and use millimeters for robot
   positions.
4. Place reference marks across the robot picking area. Measure each robot
   position with the same tool center point and Z plane.
5. Stop automatic motion while collecting or editing reference pairs.

## Recommended workflow

Open **Calibration** and follow the four steps shown in
**Camera-to-Robot Calibration**.

### 1. Choose a mapping method

- **2-Point Similarity Transform** is the recommended starting point
  for a flat conveyor with small perspective and lens distortion. It corrects
  translation, rotation, and uniform scale.
- **4-Point Planar Homography** compensates for a camera viewing one
  flat conveyor plane at an angle. Use four non-collinear references distributed
  around the picking area.
- **Interpolated Mapping (3+ reference pairs)** is intended for residual or
  non-uniform error across a larger workspace. Three pairs can build a grid,
  four pairs are required for leave-one-out validation, and six or more
  distributed pairs are recommended for production.
- **Scaled Direction Vector (2 robot positions)** calculates a direction vector
  with a requested output magnitude. It does not replace coordinate calibration.

Select the transform model and press **Open Model**.

### 2. Collect paired points

For each reference, record both coordinate spaces:

- **Image (px):** the reference center in the unmodified camera image.
- **Robot (mm):** the measured tool-center position at the same reference.

Use references that are far apart and avoid nearly identical or collinear points.
For perspective and multi-point calibration, cover both ends and both sides of
the production picking area.

### 3. Calculate and store the mapping

Enter a descriptive variable name, calculate the mapping, and save it. Keep the
mapping name stable because tracking and G-Script programs refer to it. A
successful calculation is not sufficient evidence that calibration is accurate;
validation is mandatory.

### 4. Validate before production

Open **Apply Transform to Test Point**. Test independent reference points that
were not used to solve the transform. For each test point:

1. Enter its image coordinate and select the stored mapping variable.
2. Calculate the output robot coordinate.
3. Compare the output with the measured robot position.
4. Record X/Y error and total planar error.

Define an acceptance limit for the cell before commissioning. The limit must
include object-detection uncertainty, camera calibration error, robot repeatability,
tool-center error, conveyor tracking latency, and the mechanical pick tolerance.
Do not activate automatic picking when validation exceeds that limit.

## Supporting tools

### Position List Editor

This section appends robot positions to an object-list variable. It is useful for
place locations and recipes, but it does not calibrate the camera.

### Tracking Runtime Configuration

Configure object-list and encoder sources only after mapping validation. Start
with conservative queue and stale-data limits. Confirm that tracking rejects old
camera frames and encoder samples rather than extrapolating indefinitely.

## Recalibrate when

- camera mounting, focus, resolution, crop, or distortion correction changes;
- the conveyor plane, robot base, tool center point, or product height changes;
- validation error grows beyond the cell acceptance limit;
- a saved mapping cannot be identified or its coordinate frames are unknown.

Keep calibration files, validation measurements, camera settings, and the active
mapping variable under the same versioned machine configuration.
