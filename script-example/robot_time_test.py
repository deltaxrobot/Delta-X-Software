import serial
import time

import math

def calculate_movement_time(v_start, v_max, a_max, v_end, distance):
    # Tính thời gian tăng tốc
    t_acc = (v_max - v_start) / a_max

    # Tính quãng đường tăng tốc
    d_acc = v_start * t_acc + 0.5 * a_max * t_acc**2

    # Tính thời gian giảm tốc
    t_dec = (v_max - v_end) / a_max

    # Tính quãng đường giảm tốc
    d_dec = v_max * t_dec - 0.5 * a_max * t_dec**2

    # Tính quãng đường di chuyển với vận tốc lớn nhất
    d_max = distance - d_acc - d_dec

    if d_max < 0:
        # Không đạt vận tốc lớn nhất
        t_max = 0
        v_max = math.sqrt(v_start**2 + a_max * distance)
        t_acc = (v_max - v_start) / a_max
        t_dec = (v_max - v_end) / a_max
    else:
        # Tính thời gian di chuyển với vận tốc lớn nhất
        t_max = d_max / v_max

    # Tính tổng thời gian di chuyển
    total_time = t_acc + t_max + t_dec

    return total_time

# Ví dụ sử dụng
v_start = 50  # Vận tốc bắt đầu (m/s)
v_max = 100    # Vận tốc lớn nhất (m/s)
a_max = 3000    # Gia tốc lớn nhất (m/s^2)
v_end = v_start   # Vận tốc kết thúc (m/s)
distance = 180 # Quãng đường di chuyển (m)

movement_time = calculate_movement_time(v_start, v_max, a_max, v_end, distance)
print(f"Thời gian di chuyển: {movement_time:.2f} giây")

# Kết nối với cổng COM18
ser = serial.Serial('COM18', 115200, timeout=1)

# Đợi 2 giây để Arduino khởi động 
time.sleep(2)

def send_gcode_command(ser, command):
    ser.write(command.encode())
    print(f"Đã gửi lệnh: {command}")

    response = ""
    while "Ok" not in response:
        response = ser.readline().decode()

    print(f"Đã nhận phản hồi: {response}")

send_gcode_command(ser, "G28\n")

#Gửi gcode thay đổi gia tốc dựa vào biến a_max
send_gcode_command(ser, "M204 A{a_max}\n".format(a_max=a_max))

send_gcode_command(ser, "M205 S{v_start}\n".format(v_start=v_start))

send_gcode_command(ser, "G01 X90 Y-100 Z-325 F{v_max}\n".format(v_max=v_max))

start_time = time.time()

send_gcode_command(ser, "G01 X-90 Y-100 Z-325\n")

end_time = time.time()

execution_time = end_time - start_time

print(f"Thời gian thực hiện lệnh: {execution_time:.2f} giây")

ser.close()