#!/usr/bin/env python3
"""YOLOv8 detector adapter for the correlated Delta X DXV1 protocol."""

from __future__ import annotations

import argparse
import os
import sys
import time
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from dxv1_client import DeltaXVisionClient, Dxv1ProtocolError, decode_image  # noqa: E402


def default_model_path() -> str:
    configured = os.environ.get("DELTAX_MODEL_PATH", "").strip()
    if configured:
        return configured
    return str(SCRIPT_DIR.parent / "models" / "yolov8n.pt")


def parse_args():
    parser = argparse.ArgumentParser(description="YOLOv8 External Vision adapter for Delta X")
    parser.add_argument("--host", "-ip", default="127.0.0.1")
    parser.add_argument("--port", "-port", type=int, default=8844)
    parser.add_argument("--model-path", "-model", default=default_model_path())
    parser.add_argument("--confidence", type=float, default=0.25)
    parser.add_argument("--device", default=None, help="Ultralytics device, e.g. cpu, 0, 0,1")
    parser.add_argument("--show-preview", action="store_true")
    parser.add_argument("--retry-seconds", type=float, default=2.0)
    return parser.parse_args()


def result_to_detections(results, frame):
    detections = []
    detection_index = 0
    for result in results:
        boxes = result.boxes
        if boxes is None:
            continue
        xywh_values = boxes.xywh.cpu().tolist()
        class_values = boxes.cls.cpu().tolist()
        confidence_values = boxes.conf.cpu().tolist()
        names = result.names
        for xywh, class_value, confidence in zip(
            xywh_values, class_values, confidence_values
        ):
            class_id = int(class_value)
            label = names.get(class_id, str(class_id)) if isinstance(names, dict) else str(class_id)
            x, y, width, height = (float(value) for value in xywh)
            detections.append(
                {
                    "type": class_id,
                    "label": str(label),
                    "confidence": float(confidence),
                    "externalId": f"{frame['frameId']}:{detection_index}",
                    "x": x,
                    "y": y,
                    "z": 0.0,
                    "w": width,
                    "h": height,
                    "angle": 0.0,
                }
            )
            detection_index += 1
    return detections


def run_connected(client, model, args):
    import cv2

    while True:
        frame = client.receive_image()
        image = decode_image(frame)
        predict_args = {"conf": args.confidence, "verbose": False}
        if args.device:
            predict_args["device"] = args.device
        results = model.predict(image, **predict_args)
        detections = result_to_detections(results, frame)
        client.send_detections(frame, detections, coordinate_space="image")
        print(
            f"frame={frame['frameId']} request={frame['requestId']} "
            f"tracking={frame['trackingId']} objects={len(detections)}",
            flush=True,
        )

        if args.show_preview and results:
            cv2.imshow("Delta X YOLOv8", results[0].plot())
            if cv2.waitKey(1) & 0xFF == ord("q"):
                return


def main():
    args = parse_args()
    if not 0.0 <= args.confidence <= 1.0:
        raise ValueError("--confidence must be between 0 and 1")
    try:
        from ultralytics import YOLO
    except ImportError as exc:
        raise RuntimeError(
            "YOLO adapter dependencies are missing. Install with: "
            "python -m pip install ultralytics opencv-python numpy"
        ) from exc

    model_path = Path(args.model_path).expanduser().resolve()
    if not model_path.is_file():
        raise FileNotFoundError(f"YOLO model not found: {model_path}")
    model = YOLO(str(model_path))

    while True:
        client = DeltaXVisionClient(args.host, args.port)
        try:
            client.connect()
            print(f"DXV1 connected to {args.host}:{args.port}", flush=True)
            run_connected(client, model, args)
            return
        except KeyboardInterrupt:
            return
        except (ConnectionError, OSError, Dxv1ProtocolError) as exc:
            print(f"DXV1 connection lost: {exc}; retrying...", file=sys.stderr, flush=True)
            time.sleep(max(0.2, args.retry_seconds))
        finally:
            client.close()


if __name__ == "__main__":
    try:
        main()
    except (RuntimeError, ValueError, FileNotFoundError) as exc:
        print(f"External Vision stopped: {exc}", file=sys.stderr, flush=True)
        raise SystemExit(2)
