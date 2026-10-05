"""Adapter template for an application's existing exclusive robot connection.

The owner must detach all other producers/consumers from this connection for
the complete session, including final drain. Supply nonblocking receive_lines.
Do not instantiate SerialTransport as well as this adapter for the same robot.
"""

from collections.abc import Callable

from delta_mouse.protocol import command_bytes


class ExistingConnection:
    def __init__(self, send_line: Callable[[str], None], receive_lines: Callable[[], list[str]],
                 release_owner: Callable[[], None]):
        self.send_line = send_line
        self.receive_lines = receive_lines
        self.release_owner = release_owner

    def send(self, command: str) -> None:
        command_bytes(command)  # Validate even if the host owns newline framing.
        self.send_line(command)

    def read_lines(self, now: float) -> list[str]:
        return self.receive_lines()

    def close(self) -> None:
        self.release_owner()


# Example wiring in the integrating application's worker thread:
# transport = ExistingConnection(host.send_line, host.take_received_lines, host.release_lease)
# session = RobotSession(transport)
# session.start()
# owner_timer.every(0.008, session.tick)
# Start input only after session.state == 'ready' and the home is established.
# A fault must lock the host connection against new work until hardware recovery.
