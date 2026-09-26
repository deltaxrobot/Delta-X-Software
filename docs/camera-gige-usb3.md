# GigE and USB3 Cameras in Delta X Software

## Supported backends

| Camera type | Software source | External runtime |
|---|---|---|
| UVC USB/USB3 webcam | `Webcam` | None |
| Phone browser over Wi-Fi | `Phone Camera` | Trusted HTTPS; [setup guide](phone-camera.md) |
| Hikrobot GigE Vision | `Industrial Camera` | Hikrobot MVS |
| Hikrobot USB3 Vision | `Industrial Camera` | Hikrobot MVS |
| Basler GigE Vision | `Industrial Camera` | Basler pylon |
| Basler USB3 Vision | `Industrial Camera` | Basler pylon |

MVS and pylon are optional. Delta X Software checks each runtime independently at startup. A missing pylon runtime does not disable Hikrobot support, and a missing MVS runtime does not disable Basler support. If neither runtime is installed, the application remains usable and automatically falls back from a saved industrial-camera source to `Webcam`.

## Using a UVC USB/USB3 camera

1. Select `Webcam` in Image Provider.
2. Click `Load Camera`.
3. Select a verified device by its full camera name. Each row also shows the
   transport, OpenCV camera ID, best reported mode, capture backend, default
   device marker and a stable VID:PID or shortened device identity when the
   operating system exposes one. Hover a row for the complete device ID.
4. Set the resolution and start acquisition.

Use `Refresh` after connecting or disconnecting a camera while the selection
dialog is open. Camera indices are verified with OpenCV before they are shown,
so choosing an entry does not rely only on the operating system's device list.
On Windows, names and device paths come from the native DirectShow enumeration,
which also makes OBS and other virtual cameras distinguishable from physical
USB cameras. Devices detected by Windows but unavailable to OpenCV remain
visible as disabled `Unavailable` rows for diagnostics.

On Windows, the application prefers Media Foundation, falls back to DirectShow when necessary, and attempts MJPEG for high-resolution USB3 modes.

## Using a GigE/USB3 Vision camera

1. Install the official runtime: MVS for Hikrobot or pylon for Basler.
2. Restart Delta X Software.
3. Open the `IndustrialCamera` module and review each backend status.
4. Click Refresh. Entries identify the vendor, model, transport and serial
   number. GigE entries also show their current IP address.
5. Connect and test Single Shot before enabling Continuous Shot.

## Hardware setup

- GigE: place the NIC and camera on the same subnet, prefer a dedicated NIC, disable NIC power saving, and allow MVS or pylon through the firewall. The Hikrobot backend applies the recommended packet size when the driver supports it.
- USB3: use a direct USB3 port, a compliant cable, and avoid hubs shared with other high-bandwidth devices.
- Only one application may hold a camera in exclusive mode at a time.

## Diagnostics

The following project-scoped variables report availability:

- `Camera.Backends.UvcUsb.Available`
- `Camera.Backends.Industrial.Available`
- `Camera.Backends.Industrial.Status`

When an industrial runtime is unavailable, the `Industrial Camera` option is disabled with an explanatory tooltip. Capture fails immediately instead of waiting for a timeout or terminating the application.
