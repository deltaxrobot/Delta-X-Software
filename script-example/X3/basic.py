import serial
import time

class DeltaRobot:
    def __init__(self, home_z=-291.28):
        self.conn = None
        self.home_z = home_z
        
    def connect(self, port=None):
        if not port:
            import serial.tools.list_ports
            for p in serial.tools.list_ports.comports():
                try:
                    conn = serial.Serial(p.device, 115200, timeout=2)
                    time.sleep(1)
                    conn.write(b"IsDelta\n")
                    if conn.readline().decode().strip() == "YesDelta":
                        self.conn = conn
                        print(f"Connected to {p.device}")
                        return True
                    conn.close()
                except:
                    continue
            print("Delta robot not found!")
            return False
        else:
            try:
                self.conn = serial.Serial(port, 115200, timeout=2)
                time.sleep(1)
                self.conn.write(b"IsDelta\n")
                if self.conn.readline().decode().strip() == "YesDelta":
                    print(f"Connected to {port}")
                    return True
                print("Not a delta robot!")
                return False
            except Exception as e:
                print(f"Connection error: {e}")
                return False
    
    def gcode(self, cmd):
        if not self.conn:
            return False
        try:
            print(f"Send: {cmd}")
            self.conn.write(f"{cmd}\n".encode())
            response = self.conn.readline().decode().strip()
            print(f"Reply: {response}")
            return True
        except:
            return False
    
    def run(self):
        if not self.conn:
            return
        
        self.gcode("G28")  # Home
        
        for i in range(5):
            print(f"Loop {i+1}/5")
            self.gcode(f"G01 Z{self.home_z - 80}")  # Up
            self.gcode("G01 X-100")                 # Left
            self.gcode(f"G01 Z{self.home_z - 100}") # Down
            self.gcode(f"G01 Z{self.home_z - 80}")  # Up
            self.gcode("G01 X100")                  # Right
            self.gcode(f"G01 Z{self.home_z - 100}") # Down
        
        self.gcode("G28")  # Home
        print("Done!")
    
    def close(self):
        if self.conn:
            self.conn.close()

if __name__ == "__main__":
    robot = DeltaRobot()
    try:
        if robot.connect():
            robot.run()
    except KeyboardInterrupt:
        print("Stopped")
    finally:
        robot.close()
