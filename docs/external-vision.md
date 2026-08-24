# External Vision (DXV1)

This guide explains how to use detections produced by an AI or vision process outside Delta X Software. In the application, select **Object Detection -> Algorithm -> External Script**, then click **?** to open this document.

## 1. Supported data flow

1. Delta X captures an image from a webcam, USB3 camera, or GigE camera.
2. The configured intrinsic correction, resize, warp, and crop are applied.
3. Delta X sends a JPEG image to exactly one external detector over TCP/DXV1.
4. The detector returns results with the image's `frameId`, `requestId`, and `trackingId`.
5. Image-space results pass through the camera-to-conveyor calibration.
6. Tracking associates detections, compensates encoder motion, and assigns UIDs for robots and G-Script.

Do not use `#Blobs=...`, raw image v1, or `ImageJson` for new tracking cycles. Those formats remain only for manual compatibility and do not guarantee frame correlation.

## 2. Two-minute safe smoke test

Prerequisite: Python 3 is available in `PATH`. The default sample reports an empty object list and never creates synthetic robot coordinates.

1. Open the camera and complete camera-to-conveyor calibration.
2. Select **External Script**.
3. Keep the path `script-example/receive_image_json.py`.
4. Click **Play**. State should progress through `STARTING SCRIPT`, `SCRIPT RUNNING`, and `CONNECTED`.
5. Click Capture or run G-Script containing `PcaptureAndDetect`.
6. Confirm that Activity increments `Frames sent` and `Results`, and latency appears in milliseconds.
7. Click Play again to stop.

You can also run the detector in a terminal:

```powershell
python script-example/receive_image_json.py --host 127.0.0.1 --port 8844
```

For protocol bench testing only, with robots disarmed, `--demo-boxes` deliberately returns two synthetic boxes:

```powershell
python script-example/receive_image_json.py --host 127.0.0.1 --port 8844 --demo-boxes --show-preview
```

## 3. YOLOv8

Install dependencies into the Python interpreter configured in the UI:

```powershell
python -m pip install ultralytics opencv-python numpy
```

Run directly:

```powershell
python script-example/yolov8_detect.py --host 127.0.0.1 --port 8844 --model-path models/best.pt --confidence 0.35
```

Alternatively, select `script-example/yolov8_detect.py` with the folder button beside **Detector script**, then click Play. The UI supplies host and port arguments; the model path is supplied through `DELTAX_MODEL_PATH`. If `python` is not in `PATH`, select `python.exe` in **Python executable**.

Missing Python, Ultralytics, OpenCV, or model files produce `SCRIPT ERROR/STOPPED`. The main Delta X process remains operational and does not load those AI libraries.

## 4. Integrating a custom detector

The detector may be written in Python, C#, C++, Node.js, or any TCP-capable IPC/PLC environment. It must:

1. Connect to the address and port displayed by Delta X.
2. Read the greeting `deltax\n`.
3. Send `ExternalVision DXV1\n`.
4. Read framed messages as `DXV1 <JSON byte count>\n<UTF-8 JSON>`.
5. For each `type=image` message, run inference and return exactly one `type=objects` message.
6. Echo `frameId`, `requestId`, and `trackingId` without modification.

Only one detector may register at a time. A second client is rejected so two results cannot compete for one frame.

### 4.1 Image message from Delta X

```json
{
  "type": "image",
  "protocol": "DXV1",
  "schemaVersion": 1,
  "frameId": "41",
  "requestId": "9001",
  "trackingId": 0,
  "capturedAtMonotonicNs": "1287345000",
  "source": "Webcam",
  "encoding": "jpg",
  "width": 1280,
  "height": 720,
  "channels": 3,
  "payload": "...Base64..."
}
```

64-bit IDs are strings to preserve precision in JavaScript.

### 4.2 Detection result returned to Delta X

```json
{
  "type": "objects",
  "protocol": "DXV1",
  "schemaVersion": 1,
  "frameId": "41",
  "requestId": "9001",
  "trackingId": 0,
  "coordinateSpace": "image",
  "listName": "#Objects",
  "list": [
    {
      "type": 2,
      "label": "product-A",
      "confidence": 0.94,
      "externalId": "41:0",
      "x": 412.5,
      "y": 238.0,
      "z": 0.0,
      "w": 35.0,
      "h": 62.0,
      "angle": 17.0,
      "isPicked": false
    }
  ]
}
```

Required object fields are `type`, `x`, `y`, `w`, `h`, and `angle`. Optional fields are `z`, `isPicked`, `confidence`, `label`, and `externalId`. Confidence must be within `[0,1]`, and type must be a stable integer defined by the model. Label is for display and diagnostics; G-Script should filter on type. Tracking assigns the official UID and never uses `externalId` as ownership.

An empty list is a valid result and must be returned when no object is present:

```json
{"type":"objects","protocol":"DXV1","frameId":"41","requestId":"9001","trackingId":0,"coordinateSpace":"image","list":[]}
```

## 5. Coordinate spaces and calibration

- `coordinateSpace: "image"`: `x,y,w,h` are pixels in the exact DXV1 image. Delta X applies the camera mapping to conveyor coordinates. This is recommended.
- `coordinateSpace: "conveyor"`: the detector has already calibrated the result into conveyor millimetres. Delta X does not map it again.
- `coordinateSpace: "world"`: treated as calibrated real-world data.

Do not change resolution, resize, warp, crop, or distortion correction after camera mapping. A change invalidates the calibration and requires recalibration.

Verify the angle convention with parts at 0, 45, and 90 degrees. Bounding boxes commonly have 180-degree periodicity. If the camera mapping mirrors the image, verify angle sign before enabling robot motion.

## 6. G-Script and tracking

Use the frame-correlated blocking primitive:

```gcode
M98 PcaptureAndDetect(0, 3000)
```

Never use a fixed delay to guess that inference has completed. `PcaptureAndDetect` resumes only after tracking emits `FrameReady`. A disconnected detector, timeout, or mismatched metadata returns `VisionError`.

After commit, each object exposes:

- `.Type`, `.X`, `.Y`, `.Z`, `.W`, `.L`, `.A`, `.UID`
- `.Confidence`, `.Label`, `.ExternalId`
- `.Confirmed`, `.HitCount`, `.MissedFrames`, `.State`

The robot must claim an object through the tracking primitive before picking it. Never use `externalId` as an ownership key.

## 7. Status and troubleshooting

| State | Meaning and action |
|---|---|
| `NOT CONNECTED` | No detector is registered. Check host, port, firewall, and script. |
| `SCRIPT RUNNING` | Python is running but may not have registered its socket. Inspect stderr. |
| `CONNECTED` | A DXV1 detector is registered. Inspect Activity during capture. |
| `PROTOCOL ERROR` | JSON, framing, data types, or correlation metadata are invalid. |
| `STALE RESULT IGNORED` | A late or mismatched result was excluded from tracking. |
| `SCRIPT ERROR/STOPPED` | Python, a dependency, the model, or the detector process failed. |

Quick checks:

- `Frames sent` increases but `Results` does not: inference is stalled/slow or the detector is not returning empty lists.
- Latency grows continuously: reduce image size/ROI, use acceleration, or reduce capture frequency.
- `Camera mapping has not been calibrated`: calibrate image-to-conveyor mapping or return genuinely calibrated `coordinateSpace: conveyor` data.
- `Another External Vision detector is already active`: stop the previous client.
- The script works in a terminal but Play fails: select the correct Python executable or add it to `PATH`.

## 8. Operational safety

1. Begin with empty results and disarmed robots.
2. Test synthetic or sample parts at low conveyor speed with a restricted claim zone.
3. Permit only `Confirmed=true` objects above the process confidence threshold.
4. Stop assigning work when the camera, encoder, mapping, or detector is unavailable. Never reuse an old frame result.
5. The server binds `127.0.0.1` by default. For a detector on another computer, enable `Network/AllowLanControl` only on a trusted, firewalled machine network.
6. DXV1 is plain TCP without TLS or token authentication. Do not expose it directly to the Internet. Legacy remote G-Script, event, and variable-write operations remain disabled independently of the DXV1 detection path.
