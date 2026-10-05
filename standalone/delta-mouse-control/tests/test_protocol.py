import sys
from types import SimpleNamespace

import pytest

from delta_mouse import MotionError, SerialTransport, Vec3
from delta_mouse.protocol import LineBuffer, command_bytes, position_response


def test_partial_and_coalesced_serial_lines():
    buffer = LineBuffer()
    assert buffer.feed(b"O") == []
    assert buffer.feed(b"k\r\n0,0,-300\nI0 V1\n") == ["Ok", "0,0,-300", "I0 V1"]
    assert position_response(" 1.2, -3.4,-300,0,0,0 ") == Vec3(1.2, -3.4, -300)


@pytest.mark.parametrize("data", [b"a" * 513, b"a" * 513 + b"\n", b"\xff\n"])
def test_invalid_receive_framing(data):
    with pytest.raises(MotionError):
        LineBuffer().feed(data)


@pytest.mark.parametrize("line", ["G90\nG28", "G90\r", "x" * 80, "", "G01 X\x00"])
def test_invalid_command_framing(line):
    with pytest.raises(MotionError):
        command_bytes(line)


def test_selected_baudrate_is_passed_to_serial_and_partial_write_is_error(monkeypatch):
    captured = {}

    def create(**kwargs):
        captured.update(kwargs)
        return SimpleNamespace(write=lambda data: len(data) - 1, close=lambda: None)

    monkeypatch.setitem(sys.modules, "serial", SimpleNamespace(Serial=create))
    transport = SerialTransport("COM7", 230400)
    assert captured["baudrate"] == 230400
    assert captured["port"] == "COM7"
    assert captured["timeout"] == 0
    with pytest.raises(OSError, match="Partial"):
        transport.send("G90")
