"""No GUI, serial port or physical robot needed; deterministic simulated clock."""

from delta_mouse import RobotSession, SimulatedTransport, Vec3


def main():
    now = 0.0
    transport = SimulatedTransport(clock=lambda: now)
    session = RobotSession(transport, clock=lambda: now)
    session.start()

    def wait_until(condition, limit=10):
        nonlocal now
        deadline = now + limit
        while not condition():
            if session.state == "fault":
                raise RuntimeError(session.message)
            if now >= deadline:
                raise TimeoutError(session.snapshot())
            now += 0.008
            session.tick()

    wait_until(lambda: session.state == "ready")
    session.arm(confirmed_homed=True)  # Simulation only; real hardware needs an established home.
    session.begin_hold()
    session.add_mouse_delta(dx=800, dy=-200, wheel_notches=3)
    wait_until(lambda: session.snapshot().idle)
    snapshot = session.snapshot()
    print("Acknowledged position:", snapshot.position)
    print("Expected position:    ", Vec3(120, 30, -297))
    print("Remaining (mm):", snapshot.remaining_mm)
    print("Maximum queue depth:", transport.max_depth)
    session.close()
    wait_until(lambda: session.state == "closed")
    print("Clean close:", session.state)


if __name__ == "__main__":
    main()
