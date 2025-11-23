#!/usr/bin/env python3
import argparse
import base64
import json
import socket
from pathlib import Path

import cv2
import numpy as np


def recv_one_message(sock):
    """Receive a single message framed as: <prefix>\\n<json>."""
    # Read prefix line
    prefix = b""
    while b"\n" not in prefix:
        chunk = sock.recv(1)
        if not chunk:
            return None, None
        prefix += chunk
    prefix = prefix.strip()

    # Read JSON payload; assume it fits in reasonable size, keep reading until valid JSON
    payload = b""
    while True:
        chunk = sock.recv(4096)
        if not chunk:
            break
        payload += chunk
        try:
            obj = json.loads(payload.decode("utf-8"))
            return prefix, obj
        except json.JSONDecodeError:
            continue
    return prefix, None


def save_image_from_obj(obj, out_path=None):
    b64 = obj["payload"]
    channels = obj.get("channels", 3)
    binary = base64.b64decode(b64)
    nparr = np.frombuffer(binary, np.uint8)
    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR if channels == 3 else cv2.IMREAD_UNCHANGED)
    if img is None:
        return None
    if out_path:
        cv2.imwrite(str(out_path), img)
    return img


def simple_detect_bboxes(img):
    """Demo detections: always return 2 rotated rectangles based on image size."""
    if img is None:
        return []
    h, w = img.shape[:2]
    # First rectangle near center
    det1 = (0, int(w * 0.4), int(h * 0.5), int(w * 0.2), int(h * 0.1), 15)
    # Second rectangle near bottom-right
    det2 = (1, int(w * 0.7), int(h * 0.7), int(w * 0.15), int(h * 0.2), -25)
    return [det1, det2]


def send_detections(sock, detections, list_name="#Objects"):
    if not detections:
        return
    # Gửi JSON object để Delta X parse: {type:"objects", list:[...]}
    obj_list = []
    for det in detections:
        det_id, x, y, w, h, angle = det
        obj_list.append({
            "type": det_id,
            "x": float(x),
            "y": float(y),
            "w": float(w),
            "h": float(h),
            "angle": float(angle),
        })
    payload = {
        "type": "objects",
        "list": obj_list
    }
    print(f"Sending detections: {payload}")
    try:
        sock.sendall(json.dumps(payload).encode("utf-8"))
    except OSError as e:
        print(f"Failed to send detections: {e}")


def main():
    parser = argparse.ArgumentParser(description="Receive JSON/base64 images continuously from Delta X Software")
    parser.add_argument("--host", default="192.168.1.59", help="Server host")
    parser.add_argument("--port", type=int, default=8844, help="Server port")
    parser.add_argument("--out-dir", default=None, help="Directory to save decoded images (optional)")
    parser.add_argument("--send-detections", action="store_true", default=True, help="Send simple contour detections back to Delta X")
    parser.add_argument("--list-name", default="#Objects", help="Variable name to send detections (e.g., #Objects)")
    args = parser.parse_args()

    out_dir = Path(args.out_dir) if args.out_dir else None
    if out_dir:
        out_dir.mkdir(parents=True, exist_ok=True)

    with socket.create_connection((args.host, args.port)) as sock:
        print(f"Connected to {args.host}:{args.port}")
        # Đăng ký tên client để DeltaX gửi ảnh
        sock.sendall(b"ClientName=ImageClient\n")
        # Đọc thông điệp khởi tạo từ server (ví dụ "deltax\n")
        hello = sock.recv(4096)
        print(f"Server hello: {hello!r}")
        frame_id = 0
        while True:
            prefix, obj = recv_one_message(sock)
            if not prefix:
                print("Connection closed")
                break
            if prefix != b"ImageJson":
                print(f"Skipping unexpected prefix: {prefix}")
                continue
            if obj is None:
                print("Failed to parse JSON payload")
                continue

            out_path = None
            if out_dir:
                out_path = out_dir / f"frame_{frame_id:05d}.jpg"
            img = save_image_from_obj(obj, out_path)
            if img is not None:
                if out_path:
                    print(f"[{frame_id}] saved {img.shape[1]}x{img.shape[0]} to {out_path}")
                # Hiển thị ảnh lên giao diện
                cv2.imshow("ImageJson Stream", img)
                if cv2.waitKey(1) & 0xFF == ord("q"):
                    print("Quit requested by user")
                    break
                # Gửi kết quả detect đơn giản về Delta X nếu cần
                if args.send_detections:
                    dets = simple_detect_bboxes(img)
                    send_detections(sock, dets, args.list_name)
            frame_id += 1


if __name__ == "__main__":
    main()
