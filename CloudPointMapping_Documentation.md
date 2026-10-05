# Cloud Point Mapping

Cloud Point Mapping converts camera/image coordinates into calibrated machine coordinates by interpolating a set of measured point pairs. It complements the simple two-point mapping when residual distortion, an oblique view, or a large field of view makes one global rotation/scale transform insufficient.

## Architecture

```text
CloudPointMapper
  +-- calibration point store
  +-- grid/interpolation engine
  +-- validation and error estimates
  +-- JSON persistence
  +-- VariableManager integration

CloudPointToolController
  +-- Point Tool controls
  +-- point table and test transform
  +-- save/load and import/export
```

Each calibration record contains image XYZ, real XYZ, confidence, label, timestamp, and validation error. A mapping requires at least three valid points; a distributed grid is strongly preferred.

## Point Tool workflow

1. Fix camera resolution, focus, exposure, crop, resize, and perspective correction.
2. Place a measured reference at several positions covering the complete usable ROI.
3. Add each image coordinate and its corresponding real coordinate.
4. Assign lower confidence only when a measurement is known to be less reliable.
5. Select an interpolation method and grid resolution.
6. Build the grid and run validation.
7. Test points that were not used for fitting, especially at ROI edges.
8. Save the mapping and record maximum/RMS error in the commissioning report.

Recommended starting densities:

| Use case | Suggested points |
|---|---:|
| Basic planar check | 3-9 |
| Normal conveyor ROI | 9-25 |
| High-accuracy or distorted ROI | 50-100 |

Use a representative distribution. Adding many clustered points does not compensate for an unmeasured edge or corner.

## Interpolation methods

| Method | ID | Use |
|---|---:|---|
| Linear | 0 | Fast coarse interpolation using nearby points |
| Bilinear | 1 | Default balance for regular planar grids |
| Cubic spline | 2 | Smooth surfaces with enough calibration density |
| Radial basis | 3 | Irregular point distributions and local distortion |
| Kriging | 4 | Spatial data requiring statistical modelling |

Start with bilinear interpolation. Change methods only after comparing validation error on withheld points. A more complex method cannot repair inaccurate references, belt slip, camera movement, or poor point coverage.

## G-Script API

### Calibration

```gcode
#index = #cloudPointAddCalibration(imageX,imageY,imageZ,realX,realY,realZ,confidence,"label")
#ok = #cloudPointRemove(index)
#ok = #cloudPointUpdate(index,imageX,imageY,imageZ,realX,realY,realZ,confidence)
```

### Transformation and quality

```gcode
#realX = #cloudPointTransformX(imageX,imageY,imageZ,method)
#realY = #cloudPointTransformY(imageX,imageY,imageZ,method)
#realZ = #cloudPointTransformZ(imageX,imageY,imageZ,method)
#confidence = #cloudPointGetConfidence(imageX,imageY,imageZ,method)
#estimatedError = #cloudPointGetError(imageX,imageY,imageZ,method)
```

### Lifecycle and persistence

```gcode
#count = #cloudPointGetCount()
#valid = #cloudPointIsValid()
#averageError = #cloudPointValidate(0.2)
#ok = #cloudPointBuildGrid(10.0)
#ok = #cloudPointSave("mapping.json")
#ok = #cloudPointLoad("mapping.json")
#ok = #cloudPointExport("CloudMapping")
#ok = #cloudPointImport("CloudMapping")
#ok = #cloudPointClear()
```

### Point inspection

```gcode
#imageX = #cloudPointGetImageX(index)
#imageY = #cloudPointGetImageY(index)
#imageZ = #cloudPointGetImageZ(index)
#realX = #cloudPointGetRealX(index)
#realY = #cloudPointGetRealY(index)
#realZ = #cloudPointGetRealZ(index)
#confidence = #cloudPointGetPointConfidence(index)
#error = #cloudPointGetPointError(index)
```

## Example

```gcode
#cloudPointImport("PickPlaceMapping")

IF #cloudPointIsValid() == 0
    #cloudPointClear()
    #cloudPointAddCalibration(100,100,0,10.5,20.3,-150,1.0,"P00")
    #cloudPointAddCalibration(200,100,0,30.2,20.1,-150,1.0,"P10")
    #cloudPointAddCalibration(100,200,0,10.2,40.1,-150,1.0,"P01")
    #cloudPointAddCalibration(200,200,0,30.1,40.3,-150,1.0,"P11")
    #cloudPointBuildGrid(5.0)
    #AverageError = #cloudPointValidate(0.25)
    M98 Passert(#AverageError >= 0, "Cloud mapping validation failed")
    #cloudPointExport("PickPlaceMapping")
ENDIF

#RealX = #cloudPointTransformX(#Detection.X,#Detection.Y,0,1)
#RealY = #cloudPointTransformY(#Detection.X,#Detection.Y,0,1)
#Error = #cloudPointGetError(#Detection.X,#Detection.Y,0,1)
M98 Passert(#Error <= #MaxMappingError, "Mapping error exceeds the process limit")
```

## Validation and maintenance

- Do not validate with every point used for fitting; reserve 20-30% as check points.
- Record average, maximum, and RMS error, and compare them with the end-effector capture radius.
- Recalibrate after moving the camera, lens, lighting mount, belt plane, or resize/crop/warp settings.
- Check one known reference at shift start and run a fuller validation on the maintenance schedule.
- Store a versioned mapping per camera, resolution, ROI, and mechanical setup.
- Reject a production run when the mapping is invalid or its measured error exceeds the accepted process budget.

Cloud Point Mapping improves geometric calibration but does not compensate for encoder scale error, belt slip, motion blur, inaccurate robot-to-conveyor mapping, or timing error. Validate the entire camera-to-pick chain on the physical cell.
