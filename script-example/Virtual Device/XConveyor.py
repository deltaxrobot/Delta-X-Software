import sys
from PyQt5.QtCore import QTimer, QThread, pyqtSignal, QObject
from PyQt5.QtWidgets import QApplication
import serial
from serial.tools import list_ports


class EncoderSimulator(QObject):
    encoder_position = 0
    velocity = 0

    def __init__(self):
        super().__init__()
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_encoder_position)
        self.timer.start(100)  # Update every 100 ms

    def update_encoder_position(self):
        self.encoder_position += self.velocity * 0.1
        # print(f"Encoder position: {self.encoder_position}")


class SerialPortListener(QThread):
    received_command = pyqtSignal(str)

    def __init__(self, port):
        super().__init__()
        self.port = port
        self.ser = serial.Serial(self.port, 9600, timeout=1)
        self.encoder_simulator = EncoderSimulator()

    def run(self):
        while True:
            if self.ser.in_waiting > 0:
                command = self.ser.readline().decode().strip()
                response = self.handle_gcode(command)
                self.ser.write((response + "\n").encode())
                print(f"Received: {command}, Responded: {response}")

    def handle_gcode(self, command):
        if command.startswith("M311"):
            self.encoder_simulator.velocity = int(command.split(" ")[1])
            return "Ok"
        elif command.startswith("M312"):
            self.encoder_simulator.encoder_position = int(command.split(" ")[1])
            self.encoder_simulator.velocity = 0
            return "Ok"
        elif command == "IsXConveyor":
            return "YesXConveyor"
        elif command.startswith("M317"):
            return f"P0:{self.encoder_simulator.encoder_position}"
        # Add more Gcode handlers here
        return "Ok"


def find_conveyor_port():
    ports = list_ports.comports()
    for port in ports:
        if "COM1" in port.device:  # Assuming COM1 is used for the example
            return port.device
    return None


def main():
    app = QApplication(sys.argv)
    conveyor_port = find_conveyor_port()
    if conveyor_port:
        serial_port_listener = SerialPortListener(conveyor_port)
        serial_port_listener.start()
    else:
        print("Conveyor port not found.")
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
