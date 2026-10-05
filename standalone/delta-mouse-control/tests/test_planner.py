from dataclasses import replace
import math

import pytest

from delta_mouse import Limits, MotionError, State, Vec3, brake, follow, plan
from delta_mouse.planner import duration, transition_distance
from delta_mouse.tracker import TargetTracker


def test_straight_path_keeps_velocity_and_finishes_at_rest():
    limits = Limits()
    moves = plan(State(Vec3(0, 0, -300)), [Vec3(20, 0, -300), Vec3(60, 0, -300)])
    assert moves[0].entry == moves[-1].exit == 0
    assert moves[-1].end == Vec3(60, 0, -300)
    for previous, current in zip(moves, moves[1:]):
        assert current.entry == previous.exit > 0
    for move in moves:
        assert max(move.entry, move.exit) <= move.feed - 2
        assert transition_distance(move.entry, move.exit, limits) <= (move.end - move.start).length() + 0.001
        assert math.isfinite(move.seconds)
        assert len(move.gcode()) <= 79
    assert sum(m.seconds for m in moves) < 0.6 * sum(duration((m.end - m.start).length(), 0, 0, limits) for m in moves)


def test_corners_preserved_and_no_silent_removal_of_small_detail():
    vertices = [Vec3(10, 0), Vec3(10, 10), Vec3(10, 0)]
    moves = plan(State(Vec3()), vertices)
    for vertex in vertices:
        assert any(m.end == vertex and m.exit == 0 for m in moves)
    with pytest.raises(MotionError, match="minimum"):
        plan(State(Vec3()), [Vec3(0.1, 0), Vec3(0.1, 1)])


@pytest.mark.parametrize("limits", [Limits(jerk=0), Limits(speed=0), Limits(acceleration=-1),
                                   Limits(speed=10.5), Limits(segment_length=0.2),
                                   Limits(minimum_length=float("nan")), Limits(queued_seconds=0)])
def test_invalid_profile_rejected(limits):
    with pytest.raises(MotionError):
        plan(State(Vec3()), [Vec3(10, 0)], limits)


@pytest.mark.parametrize("point", [Vec3(float("inf")), Vec3(float("nan")), Vec3(100001)])
def test_invalid_coordinates_rejected(point):
    with pytest.raises(MotionError):
        plan(State(Vec3()), [point])


def test_prediction_bounded_and_exact_target_restored():
    limits = replace(Limits(), segment_length=8)
    moves = follow(State(Vec3()), Vec3(10), Vec3(100), 0.1, limits)
    assert moves[-1].end == Vec3(13)
    assert moves[0].end.x > 2
    assert all(m.feed <= 100 for m in moves)
    settled = follow(State(Vec3()), Vec3(10), Vec3(), 0.1, limits)
    assert settled[-1].end == Vec3(10)
    assert settled[-1].exit == 0


def test_reversal_brakes_in_old_direction_and_feed_reduction_is_feasible():
    start = State(Vec3(), Vec3(1), 60)
    moves = follow(start, Vec3(-10), Vec3(-100), 0, Limits(segment_length=8))
    assert len(moves) == 1 and moves[0].end.x > 0 and moves[0].exit == 0
    assert moves[0].end.x >= transition_distance(60, 0, Limits())
    lower = follow(start, Vec3(30), Vec3(), 0, Limits(speed=10, segment_length=8))
    assert lower[0].exit == 0
    assert math.isfinite(lower[0].seconds)


def test_final_deceleration_kept_whole():
    moves = follow(State(Vec3(124.285), Vec3(1), 78), Vec3(130), Vec3(), 0, Limits(segment_length=8))
    assert len(moves) == 1
    assert moves[0].end == Vec3(130)
    assert moves[0].exit == 0


def test_tracker_batches_expiry_and_reversal():
    tracker = TargetTracker(Vec3(), 0)
    for i in range(1, 11):
        tracker.observe(Vec3(i), i * 0.01)
    assert tracker.velocity(0.1, 150).x == pytest.approx(100)
    assert tracker.velocity(0.16, 150).x == pytest.approx(50)
    assert tracker.velocity(0.181, 150) == Vec3()
    tracker.observe(Vec3(9), 0.11)
    assert tracker.velocity(0.11, 150) == Vec3()
    tracker.observe(Vec3(8), 0.12)
    assert tracker.velocity(0.12, 150).x == pytest.approx(-100)
    tracker.reset(Vec3(), 1)
    for i in range(100):
        tracker.observe(Vec3(i), 1)
    assert tracker.velocity(1, 150) == Vec3()


def test_path_size_limit_and_rounding():
    assert Vec3(-1.2345, 1.2345).rounded() == Vec3(-1.235, 1.235)
    with pytest.raises(MotionError, match="4096"):
        plan(State(Vec3()), [Vec3(10000)])
    with pytest.raises(MotionError):
        brake(State(Vec3()))
