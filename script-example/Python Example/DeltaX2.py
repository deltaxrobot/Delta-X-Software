# Connect to COM7

import serial
import time

ser = serial.Serial('COM7', 115200, timeout=1)

# Wait for the serial port to open
time.sleep(2)

# Read the serial port

# while True:
#     try:
#         line = ser.readline().decode('utf-8')
#         print(line)
#     except serial.SerialException:
#         print("Serial port error")
#         break
#     except UnicodeDecodeError:
#         print("Unicode decode error")
#         break

# Send Gcode to the serial port

ser.write(b"G28\n")

# Function to send Gcode to the serial port and wait response

def send_gcode(gcode):
    ser.write(gcode.encode())
    while True:
        try:
            line = ser.readline().decode('utf-8')
            print(line)
            if "Ok" in line:
                break
        except serial.SerialException:
            print("Serial port error")
            break
        except UnicodeDecodeError:
            print("Unicode decode error")
            break

# send_gcode("G28\n")
send_gcode("G01 Z-350\n")
send_gcode("G01 X100 Y100\n")
send_gcode("M03\n")
time.sleep(1)
# send_gcode("M05\n")

