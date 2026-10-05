from collections import deque
import math

import pytest

from delta_mouse import MotionError, MouseSettings, RobotSession, Vec3
from conftest import Clock, advance_until


def enable(session):
    session.arm(confirmed_homed=True)
    session.begin_hold()


def settle(session, clock):
    advance_until(session, clock, lambda: session.stream.idle)


def test_handshake_does_not_auto_enable_or_home(robot):
    session, transport, clock = robot
    assert list(transport.log) == ["IsDelta", "ROBOTMODEL", "G90", "M205 S0", "PositionOffset"]
    assert not session.armed
    assert session.snapshot().position == Vec3(0, 0, -300)
    with pytest.raises(MotionError):
        session.begin_hold()
    with pytest.raises(MotionError):
        session.arm()


def test_homing_waits_for_ok_then_reads_position(robot):
    session, transport, clock = robot
    session.home()
    assert not session.armed
    assert session.state == "homing"
    advance_until(session, clock, lambda: session.state == "ready")
    assert session.armed
    assert list(transport.log)[-2:] == ["G28", "PositionOffset"]


def test_large_mouse_displacement_reaches_target_while_still_held(robot):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(800, -200, 3)
    settle(session, clock)
    assert session.held
    assert (transport.position - Vec3(120, 30, -297)).length() < 0.201
    assert transport.max_depth <= 2
    moves = [line for line in transport.log if line.startswith("G01")]
    assert len(moves) > 3


def test_subminimum_input_accumulates_and_wheel_only_works(robot):
    session, transport, clock = robot
    enable(session)
    for _ in range(100):
        session.add_mouse_delta(0.1, 0)
        clock.advance()
        session.tick()
    settle(session, clock)
    assert transport.position.x == pytest.approx(1.5, abs=0.201)
    for _ in range(4):
        session.add_mouse_delta(wheel_notches=0.25)
    settle(session, clock)
    assert transport.position.z == pytest.approx(-299, abs=0.201)


def test_release_cancels_unsent_target_and_close_resets_edges(robot):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(1000)
    clock.advance()
    session.tick()
    assert session.stream.inflight
    session.close()
    advance_until(session, clock, lambda: session.state == "closed")
    assert transport.position.x < 30
    assert transport.closed
    assert list(transport.log)[-1] == "M205 S0"
    assert not session.armed and not session.held


def test_next_hold_rebases_after_braking(robot):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(800)
    clock.advance()
    session.tick()
    session.stop()
    settle(session, clock)
    stopped = transport.position
    session.begin_hold()
    session.add_mouse_delta(-20)
    settle(session, clock)
    assert (transport.position - (stopped + Vec3(-3))).length() < 0.201


@pytest.mark.parametrize("curved", [False, True])
def test_live_tracking_settles_and_maintains_bounded_pipeline(robot, curved):
    session, transport, clock = robot
    enable(session)
    previous = Vec3()
    lag = []
    for i in range(1, 151):
        t = i * 0.01
        target = Vec3((45 if curved else 80) * t, 6 * math.sin(4 * t) if curved else 0)
        delta = target - previous
        session.add_mouse_delta(delta.x / 0.15, -delta.y / 0.15)
        clock.advance(0.01)
        session.tick()
        if i > 30:
            lag.append((target + Vec3(0, 0, -300) - transport.position).length())
        previous = target
    settle(session, clock)
    assert (transport.position - previous - Vec3(0, 0, -300)).length() < 0.201
    assert sum(lag) / len(lag) < (13 if curved else 30)
    assert transport.max_depth <= 2


def test_telemetry_does_not_complete_motion(robot):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(200)
    session.tick()
    pending = len(session.stream.inflight)
    transport.events.appendleft((clock(), "I0 V1", None))
    session.tick()
    assert len(session.stream.inflight) == pending


@pytest.mark.parametrize("reply", ["Error: workspace", "Delta:EStop", "Delta:Pause", "Unknown:G01", "Init Success!"])
def test_fault_latches_and_never_sends_more_motion(robot, reply):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(200)
    session.tick()
    transport.events.appendleft((clock(), reply, None))
    sent = len(transport.log)
    session.tick()
    assert session.state == "fault"
    session.add_mouse_delta(100)
    session.tick()
    assert len(transport.log) == sent
    assert transport.closed
    with pytest.raises(MotionError):
        session.start()


def test_lost_ack_times_out_and_delayed_ok_cannot_revive_session(robot):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(300)
    session.tick()
    transport.events.clear()
    clock.advance(4)
    session.tick()
    assert session.state == "fault"
    sent = len(transport.log)
    transport.events.append((clock(), "Ok", None))
    session.tick()
    assert len(transport.log) == sent


def test_batched_delayed_completions_restart_from_rest(robot):
    session, transport, clock = robot
    enable(session)
    session.add_mouse_delta(800)
    advance_until(session, clock, lambda: len(session.stream.inflight) == 2)
    before = len(transport.log)
    clock.advance(0.6)
    session.tick()
    moves = [line for line in list(transport.log)[before:] if line.startswith("G01")]
    assert moves and " S0 " in moves[0]
    assert session.state == "ready"
    settle(session, clock)
    assert transport.position.x == pytest.approx(120, abs=0.201)


def test_write_failure_latches_session(robot):
    session, transport, clock = robot
    enable(session)

    def failing_send(command):
        raise OSError("Partial serial write")

    transport.send = failing_send
    session.add_mouse_delta(100)
    session.tick()
    assert session.state == "fault"
    assert "Partial serial write" in session.message


def test_unsolicited_ok_detects_other_writer(robot):
    session, transport, clock = robot
    transport.events.append((clock(), "Ok", None))
    session.tick()
    assert session.state == "fault"


def test_transport_disconnect_latches_fault(robot):
    session, transport, clock = robot
    enable(session)
    transport.closed = True
    session.tick()
    assert session.state == "fault"


def test_ordered_path_and_brake_on_stop(robot):
    session, transport, clock = robot
    session.arm(confirmed_homed=True)
    session.move_path([Vec3(10, 0, -300), Vec3(10, 10, -300), Vec3(0, 10, -300)])
    settle(session, clock)
    assert transport.position == Vec3(0, 10, -300)
    assert transport.max_depth <= 2


def test_invalid_mouse_and_settings(robot):
    session, transport, clock = robot
    with pytest.raises(ValueError):
        session.set_mouse_settings(MouseSettings(float("nan")))
    enable(session)
    session.add_mouse_delta(float("nan"))
    assert session.state == "fault"


class Replies:
    def __init__(self, batches):
        self.batches = deque(batches)
        self.commands = []

    def send(self, command):
        self.commands.append(command)

    def read_lines(self, now):
        return self.batches.popleft() if self.batches else []

    def close(self):
        pass


@pytest.mark.parametrize("position", ["nan,0,-300", "0,0", "0,cat,-300", "0,0,inf", "0,0,-300,nan"])
def test_malformed_start_position_fails(position):
    clock = Clock()
    transport = Replies([["YesDelta"], ["MODEL:DELTA_X_3"], ["Ok"], ["Ok"], [position]])
    session = RobotSession(transport, clock=clock)
    session.start()
    for _ in range(5):
        session.tick()
    assert session.state == "fault"


def test_two_reply_batch_cannot_ack_a_new_handshake_command():
    transport = Replies([["YesDelta", "Ok"]])
    session = RobotSession(transport, clock=Clock())
    session.start()
    session.tick()
    assert session.state == "fault"
    assert transport.commands == ["IsDelta"]
