# Phone Camera

Use a phone as an image source inside Delta X Software. No phone app or cloud
relay is needed. This does not install a system-wide virtual webcam.

## First-time HTTPS setup

Phone browsers require a trusted HTTPS origin to grant camera access. An HTTP
address on the computer's LAN IP is not sufficient. Certificate trust is a
one-time setup per phone, not something a QR code can grant automatically.

1. Connect the phone and computer to the same private Wi-Fi/LAN. Guest Wi-Fi
   isolation may prevent them from communicating.
2. In Image Provider select **Phone Camera**, then **Load Camera**.
3. Select the network interface that the phone can reach. Expand **HTTPS Setup**.
4. If your organization already provides trusted certificates, select the PEM
   server certificate/chain and matching unencrypted RSA or EC private key. The
   certificate SAN must include the chosen IP address.
5. Otherwise install OpenSSL 1.1.1+ on the computer and use **Create local
   certificates**. The resulting folder opens. Only transfer `phone-root.crt`
   to the phone by a method you trust. Never share either `.key` file.
6. Android: install this certificate as a CA certificate through the system's
   security/credential settings. Names vary by manufacturer. iOS: install the
   certificate profile, then enable full trust in Settings > General > About >
   Certificate Trust Settings. Managed phones may require administrator help.
7. Tap **Start pairing**. Scan the QR with the phone's normal camera app. Open
   the page in Safari/Chrome, tap **Start camera**, and allow camera access.

If certificate validation fails, correct certificate trust/IP/expiry before
continuing. Delta X does not disable browser security or change trust stores.
The generated server certificate lasts 90 days and the local CA 365 days.
Regenerate certificates if the computer's LAN address changes. Removing the
local CA from the phone's trust store revokes trust for this local setup.

## Daily use

Select Phone Camera → Load Camera → Start pairing → scan QR → Start camera.
The pairing window closes when the phone has granted camera access and paired.
The normal Capture / Acquisition controls and capture requests from G-Script
then use the phone. Choose rear/front camera and resolution on the phone before
starting. Stop sharing and pair again to change these controls. Keep the page in the foreground;
hiding it releases the camera. Stop Camera in Delta X closes the local server.

Each session has a new secret QR link and accepts one phone. A second phone is
rejected while the first is paired. Copy link is available if QR scanning is
inconvenient. Do not share the pairing URL. QR rendering needs OpenCV 4.5+;
older supported builds provide the same pairing URL for manual opening.

No images are stored by this feature. Frames are sent over HTTPS directly to
the selected LAN interface. The computer firewall must permit incoming traffic
to Delta X on the private network; the feature never opens firewall rules.
The listening port is assigned for each session and displayed in the QR link.

## Capture behavior and limits

Delta X requests one fresh JPEG at a time. The browser captures after receiving
that request; it does not push an unbounded frame queue. Requests and replies
carry a sequence number, with a 3.5-second capture timeout and 6-second phone
heartbeat timeout. Stale, duplicate, unauthorized and oversized frames are
rejected. Frame dimensions are capped at 1920 pixels per side / 2.07 megapixels.
The browser polls for capture requests approximately every 80 ms.

Capture timestamps and conveyor encoder snapshots are taken on receipt by the
computer, not at the phone sensor's exposure time. Wi-Fi/encoding latency is
variable. Phone Camera is suitable for setup, inspection and demonstrations;
do not assume accurate fast conveyor tracking or hardware synchronization.
Recalibrate image mapping after changing phone position, camera or resolution.

## Troubleshooting

- Page cannot open: check the chosen IP, same LAN, guest isolation and firewall.
- Camera permission unavailable: verify HTTPS trust; reopen in the full browser,
  not an embedded QR-reader browser. The permission must be granted on the phone.
- Pairing expired: reopen Load Camera and scan the current QR. Reloading the
  page intentionally drops the secret from its address; scan again.
- Phone disconnected: keep its screen awake and the browser visible; pair again.
- TLS unavailable: install/deploy a Qt TLS backend. Other camera sources remain usable.
- OpenSSL unavailable: import existing certificates or install OpenSSL for local
  certificate generation. OpenSSL is not needed to use existing certificates.

Reference: [Browser camera secure-context requirements](https://developer.mozilla.org/en-US/docs/Web/API/MediaDevices/getUserMedia).
