#Windows OS
#install: pip install pyserial

import serial
import time

ser = serial.Serial('COM5',115200, timeout = 1)  # open serial port
time.sleep(2)    
print(ser.readline())

gcodes = []
gcodes.append('G01 Z-620')
gcodes.append('G01 Z-600')

for i in range(1,1000):
    for gcode in gcodes:
        print(gcode)
        gcodeLine = gcode + '\n'
        ser.write(gcodeLine.encode())
        while 1:
            response = ser.readline()
            print(response)
            if (response.find('Ok'.encode()) > -1):
                break

ser.close()