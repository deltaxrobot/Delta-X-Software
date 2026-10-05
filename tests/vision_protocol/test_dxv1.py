import importlib.util
import json
import socket
import threading
import unittest
from pathlib import Path
import sys


SCRIPT = Path(__file__).parents[2] / "script-example" / "receive_image_json.py"
sys.path.insert(0, str(SCRIPT.parent))
SPEC = importlib.util.spec_from_file_location("receive_image_json", SCRIPT)
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)


class Dxv1ProtocolTest(unittest.TestCase):
    def test_split_payload_is_read_exactly(self):
        sender, receiver = socket.socketpair()
        payload = json.dumps({"type": "image", "frameId": "12"}).encode()
        wire = f"DXV1 {len(payload)}\n".encode() + payload

        def write_chunks():
            for chunk in (wire[:3], wire[3:11], wire[11:17], wire[17:]):
                sender.sendall(chunk)
            sender.close()

        thread = threading.Thread(target=write_chunks)
        thread.start()
        prefix, message = MODULE.recv_one_message(receiver)
        thread.join()
        receiver.close()
        self.assertEqual(prefix, b"DXV1")
        self.assertEqual(message["frameId"], "12")

    def test_coalesced_messages_remain_separate(self):
        sender, receiver = socket.socketpair()
        messages = [{"frameId": "1"}, {"frameId": "2"}]
        wire = b"".join(
            f"DXV1 {len(data)}\n".encode() + data
            for data in (json.dumps(item).encode() for item in messages)
        )
        sender.sendall(wire)
        first = MODULE.recv_one_message(receiver)[1]
        second = MODULE.recv_one_message(receiver)[1]
        sender.close()
        receiver.close()
        self.assertEqual(first["frameId"], "1")
        self.assertEqual(second["frameId"], "2")

    def test_detection_message_preserves_correlation_and_empty_list(self):
        from dxv1_client import build_detections_message

        frame = {"frameId": "41", "requestId": "9001", "trackingId": 2}
        result = build_detections_message(frame, [], "image")
        self.assertEqual(result["protocol"], "DXV1")
        self.assertEqual(result["frameId"], "41")
        self.assertEqual(result["requestId"], "9001")
        self.assertEqual(result["trackingId"], 2)
        self.assertEqual(result["list"], [])


if __name__ == "__main__":
    unittest.main()
