#!/usr/bin/env python3
"""Safe DXV1 example: receive frames and return an empty detection list by default."""

from __future__ import annotations

import argparse
import socket
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from dxv1_client import (  # noqa: E402
    DeltaXVisionClient,
    Dxv1ProtocolError,
    decode_image,
    receive_message,
)


def recv_one_message(sock):
    """Backward-compatible test helper returning ``(b'DXV1', message)``."""
    try:
        return b"DXV1", receive_message(sock)
    except ConnectionError:
        return None, None


def demo_detections(frame):
    """Two synthetic boxes for protocol testing; never enabled by default."""
    width = int(frame.get("width", 0))
    height = int(frame.get("height", 0))
    if width <= 0 or height <= 0:
        return []
    return [
        {
            "type": 0,
            "label": "demo-0",
            "confidence": 1.0,
            "externalId": f"{frame['frameId']}:0",
            "x": width * 0.4,
            "y": height * 0.5,
            "z": 0.0,
            "w": width * 0.2,
            "h": height * 0.1,
            "angle": 15.0,
        },
        {
            "type": 1,
            "label": "demo-1",
            "confidence": 1.0,
            "externalId": f"{frame['frameId']}:1",
            "x": width * 0.7,
            "y": height * 0.7,
            "z": 0.0,
            "w": width * 0.15,
            "h": height * 0.2,
            "angle": -25.0,
        },
    ]


def parse_args():
    parser = argparse.ArgumentParser(
        description="Delta X DXV1 receiver; safely returns zero objects unless --demo-boxes is used"
    )
    parser.add_argument("--host", "-ip", default="127.0.0.1", help="Delta X server host")
    parser.add_argument("--port", "-port", type=int, default=8844, help="Delta X server port")
    parser.add_argument("--out-dir", default=None, help="Optionally save received JPEG frames")
    parser.add_argument("--show-preview", action="store_true", help="Show frames using OpenCV")
    parser.add_argument(
        "--demo-boxes",
        action="store_true",
        help="Return two synthetic boxes for bench testing only; never use with an armed robot",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    output_dir = Path(args.out_dir).resolve() if args.out_dir else None
    if output_dir:
        output_dir.mkdir(parents=True, exist_ok=True)

    frame_count = 0
    with DeltaXVisionClient(args.host, args.port) as client:
        print(f"DXV1 connected to {args.host}:{args.port}", flush=True)
        while True:
            frame = client.receive_image()
            detections = demo_detections(frame) if args.demo_boxes else []

            if output_dir or args.show_preview:
                image = decode_image(frame)
                if output_dir:
                    try:
                        import cv2
                    except ImportError as exc:
                        raise RuntimeError("Saving frames requires: pip install opencv-python") from exc
                    cv2.imwrite(str(output_dir / f"frame_{frame_count:06d}.jpg"), image)
                if args.show_preview:
                    import cv2

                    cv2.imshow("Delta X External Vision", image)
                    if cv2.waitKey(1) & 0xFF == ord("q"):
                        break

            client.send_detections(frame, detections, coordinate_space="image")
            print(
                f"frame={frame['frameId']} request={frame['requestId']} "
                f"tracking={frame['trackingId']} objects={len(detections)}",
                flush=True,
            )
            frame_count += 1


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
    except (ConnectionError, OSError, Dxv1ProtocolError, RuntimeError) as exc:
        print(f"External Vision stopped: {exc}", file=sys.stderr, flush=True)
        raise SystemExit(2)
