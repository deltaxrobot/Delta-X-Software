"""Small dependency-free client SDK for Delta X External Vision (DXV1)."""

from __future__ import annotations

import base64
import json
import socket
from typing import Any, Iterable, Mapping, Optional


PROTOCOL = "DXV1"
MAX_MESSAGE_BYTES = 32 * 1024 * 1024
MAX_HEADER_BYTES = 128


class Dxv1ProtocolError(RuntimeError):
    """Raised when a peer sends an invalid or unsupported DXV1 message."""


def _recv_exact(sock: socket.socket, size: int) -> bytes:
    payload = bytearray()
    while len(payload) < size:
        chunk = sock.recv(min(65536, size - len(payload)))
        if not chunk:
            raise ConnectionError("Delta X closed the connection")
        payload.extend(chunk)
    return bytes(payload)


def _recv_line(sock: socket.socket, max_bytes: int = MAX_HEADER_BYTES) -> bytes:
    line = bytearray()
    while len(line) < max_bytes:
        chunk = sock.recv(1)
        if not chunk:
            raise ConnectionError("Delta X closed the connection")
        line.extend(chunk)
        if chunk == b"\n":
            return bytes(line)
    raise Dxv1ProtocolError("DXV1 header is too long")


def receive_message(sock: socket.socket) -> dict[str, Any]:
    """Read exactly one length-prefixed DXV1 JSON message."""
    header = _recv_line(sock).strip()
    parts = header.split(b" ", 1)
    if len(parts) != 2 or parts[0] != PROTOCOL.encode("ascii"):
        raise Dxv1ProtocolError(f"Unexpected protocol header: {header!r}")
    try:
        size = int(parts[1])
    except ValueError as exc:
        raise Dxv1ProtocolError("Invalid DXV1 payload length") from exc
    if size < 0 or size > MAX_MESSAGE_BYTES:
        raise Dxv1ProtocolError(f"DXV1 payload length out of range: {size}")
    try:
        message = json.loads(_recv_exact(sock, size).decode("utf-8"))
    except (UnicodeDecodeError, json.JSONDecodeError) as exc:
        raise Dxv1ProtocolError("DXV1 payload is not valid UTF-8 JSON") from exc
    if not isinstance(message, dict):
        raise Dxv1ProtocolError("DXV1 root value must be a JSON object")
    return message


def send_message(sock: socket.socket, message: Mapping[str, Any]) -> None:
    payload = json.dumps(message, separators=(",", ":"), ensure_ascii=False).encode("utf-8")
    if len(payload) > MAX_MESSAGE_BYTES:
        raise Dxv1ProtocolError("DXV1 payload exceeds the 32 MiB limit")
    sock.sendall(f"{PROTOCOL} {len(payload)}\n".encode("ascii") + payload)


def decode_jpeg_bytes(message: Mapping[str, Any]) -> bytes:
    if message.get("type") != "image" or message.get("encoding") != "jpg":
        raise Dxv1ProtocolError("Expected a DXV1 JPEG image message")
    try:
        return base64.b64decode(message["payload"], validate=True)
    except (KeyError, ValueError, TypeError) as exc:
        raise Dxv1ProtocolError("Image payload is not valid Base64") from exc


def decode_image(message: Mapping[str, Any]):
    """Decode a frame to an OpenCV image; imports OpenCV/Numpy only when used."""
    try:
        import cv2
        import numpy as np
    except ImportError as exc:
        raise RuntimeError("Image decoding requires: pip install opencv-python numpy") from exc
    encoded = decode_jpeg_bytes(message)
    image = cv2.imdecode(np.frombuffer(encoded, dtype=np.uint8), cv2.IMREAD_COLOR)
    if image is None:
        raise Dxv1ProtocolError("OpenCV could not decode the JPEG frame")
    return image


def build_detections_message(
    frame: Mapping[str, Any],
    detections: Iterable[Mapping[str, Any]],
    coordinate_space: str = "image",
    list_name: str = "#Objects",
) -> dict[str, Any]:
    if coordinate_space not in {"image", "conveyor", "world"}:
        raise ValueError("coordinate_space must be image, conveyor, or world")
    required_metadata = ("frameId", "requestId", "trackingId")
    missing = [name for name in required_metadata if name not in frame]
    if missing:
        raise Dxv1ProtocolError(f"Frame is missing correlation metadata: {', '.join(missing)}")
    return {
        "type": "objects",
        "protocol": PROTOCOL,
        "schemaVersion": 1,
        "frameId": frame["frameId"],
        "requestId": frame["requestId"],
        "trackingId": frame["trackingId"],
        "coordinateSpace": coordinate_space,
        "listName": list_name,
        "list": list(detections),
    }


class DeltaXVisionClient:
    """Connect, receive correlated frames, and return detector results."""

    def __init__(self, host: str = "127.0.0.1", port: int = 8844, timeout: float = 5.0):
        self.host = host
        self.port = port
        self.timeout = timeout
        self.socket: Optional[socket.socket] = None

    def connect(self) -> "DeltaXVisionClient":
        self.close()
        sock = socket.create_connection((self.host, self.port), timeout=self.timeout)
        hello = _recv_line(sock, 256).strip()
        if hello != b"deltax":
            sock.close()
            raise Dxv1ProtocolError(f"Unexpected Delta X greeting: {hello!r}")
        sock.sendall(b"ExternalVision DXV1\n")
        sock.settimeout(None)
        self.socket = sock
        return self

    def close(self) -> None:
        if self.socket is not None:
            try:
                self.socket.shutdown(socket.SHUT_RDWR)
            except OSError:
                pass
            self.socket.close()
            self.socket = None

    def receive_image(self) -> dict[str, Any]:
        if self.socket is None:
            raise ConnectionError("DXV1 client is not connected")
        while True:
            message = receive_message(self.socket)
            message_type = message.get("type")
            if message_type == "image":
                return message
            if message_type == "error":
                raise Dxv1ProtocolError(str(message.get("message", "Delta X protocol error")))

    def send_detections(
        self,
        frame: Mapping[str, Any],
        detections: Iterable[Mapping[str, Any]],
        coordinate_space: str = "image",
        list_name: str = "#Objects",
    ) -> None:
        if self.socket is None:
            raise ConnectionError("DXV1 client is not connected")
        send_message(
            self.socket,
            build_detections_message(frame, detections, coordinate_space, list_name),
        )

    def __enter__(self) -> "DeltaXVisionClient":
        return self.connect()

    def __exit__(self, _exc_type, _exc, _traceback) -> None:
        self.close()
