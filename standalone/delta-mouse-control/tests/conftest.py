import pytest

from delta_mouse import RobotSession, SimulatedTransport


class Clock:
    def __init__(self):
        self.now = 0.0

    def __call__(self):
        return self.now

    def advance(self, amount=0.008):
        self.now += amount


def advance_until(session, clock, condition, seconds=10):
    deadline = clock() + seconds
    while not condition():
        assert session.state != "fault", session.message
        assert clock() < deadline, session.snapshot()
        clock.advance()
        session.tick()


@pytest.fixture
def robot():
    clock = Clock()
    transport = SimulatedTransport(clock=clock)
    session = RobotSession(transport, clock=clock)
    session.start()
    advance_until(session, clock, lambda: session.state == "ready")
    return session, transport, clock
