import serial
import time

import math

def calculate_move_time(initial_velocity, max_velocity, final_velocity, acceleration, distance):
    # Thời gian tăng tốc
    t_acc = (max_velocity - initial_velocity) / acceleration
    
    # Thời gian giảm tốc
    t_dec = (max_velocity - final_velocity) / acceleration
    
    # Khoảng cách tăng tốc và giảm tốc
    d_acc = (max_velocity**2 - initial_velocity**2) / (2 * acceleration)
    d_dec = (max_velocity**2 - final_velocity**2) / (2 * acceleration)
    
    # Khoảng cách di chuyển đều
    d_constant = distance - d_acc - d_dec
    
    # Kiểm tra nếu khoảng cách di chuyển đều là âm, tức là max_velocity không đạt được
    if d_constant < 0:
        # Tính lại max_velocity để phù hợp với khoảng cách
        max_velocity = ((2 * acceleration * distance + initial_velocity**2 + final_velocity**2) / 2)**0.5
        t_acc = (max_velocity - initial_velocity) / acceleration
        t_dec = (max_velocity - final_velocity) / acceleration
        t_constant = 0
    else:
        # Thời gian di chuyển đều
        t_constant = d_constant / max_velocity
    
    # Tổng thời gian di chuyển
    t_total = t_acc + t_constant + t_dec
    
    return t_total

def calculate_movement_time(v_start, v_max, a_max, v_end, distance):
    # Tính thời gian tăng tốc
    t_acc = (v_max - v_start) / a_max

    # Tính quãng đường tăng tốc
    d_acc = v_start * t_acc + 0.5 * a_max * t_acc**2

    # Tính thời gian giảm tốc
    t_dec = (v_max - v_end) / a_max

    # Tính quãng đường giảm tốc
    d_dec = v_max * t_dec - 0.5 * a_max * t_dec**2
    print("d_dec: ", d_dec)

    # Tính quãng đường di chuyển với vận tốc lớn nhất
    d_max = distance - d_acc - d_dec

    print("d_max: ", d_max)

    if d_max <= 0:
        # Không đạt vận tốc lớn nhất
        t_max = 0
        v_max = math.sqrt(v_start**2 + a_max * distance)
        t_acc = (v_max * 1.5 - v_start * 1.5) / (a_max * 1.5)
        t_dec = t_acc

        print("t_acc: ", t_acc)
    else:
        # Tính thời gian di chuyển với vận tốc lớn nhất
        t_max = d_max / v_max
        print("t_max: ", t_max)

    # Tính tổng thời gian di chuyển
    total_time = t_acc + t_max + t_dec

    return total_time

def compute_move_time(v0, v_end, vmax, a, s):
    """
    Tính thời gian di chuyển của robot dựa trên quỹ đạo vận tốc dạng bậc thang (trapezoidal).
    - v0: vận tốc ban đầu (m/s)
    - v_end: vận tốc cuối (m/s)
    - vmax: vận tốc tối đa (m/s)
    - a: gia tốc (m/s^2)
    - s: quãng đường cần di chuyển (m)
    
    Trả về: tổng thời gian di chuyển (s)
    """
    
    # Tính quãng đường cần để tăng tốc từ v0 lên vmax
    # s1 = (vmax^2 - v0^2) / (2a)
    s1 = (vmax**2 - v0**2) / (2 * a)
    
    # Tính quãng đường cần để giảm tốc từ vmax xuống v_end
    # s3 = (vmax^2 - v_end^2) / (2a)
    s3 = (vmax**2 - v_end**2) / (2 * a)
    
    # Nếu tổng quãng đường s lớn hơn s1 + s3, robot sẽ có giai đoạn chạy đều ở vmax
    if s > s1 + s3:
        # Giai đoạn trapezoidal
        # Thời gian tăng tốc:
        # t1 = (vmax - v0) / a
        t1 = (vmax - v0) / a
        
        # Thời gian giảm tốc:
        # t3 = (vmax - v_end) / a
        t3 = (vmax - v_end) / a
        
        # Quãng đường chạy đều:
        s2 = s - (s1 + s3)
        
        # Thời gian chạy đều:
        # t2 = s2 / vmax
        t2 = s2 / vmax
        
        # Tổng thời gian:
        T = t1 + t2 + t3
        # in thời gian tăng tốc, giảm tốc, chạy đều
        print("t1: ", t1)
        print("t2: ", t2)
        print("t3: ", t3)
        return T
    
    else:
        # Quãng đường không đủ để đạt vmax, quỹ đạo dạng tam giác
        # Ta cần tìm vpeak (vận tốc đỉnh) từ công thức:
        # s = (vpeak^2 - v0^2)/(2a) + (vpeak^2 - v_end^2)/(2a)
        # => 2a s = 2vpeak^2 - (v0^2 + v_end^2)
        # => vpeak^2 = a s + (v0^2 + v_end^2)/2
        # Lấy căn bậc 2:
        
        vpeak_squared = a*s + (v0**2 + v_end**2)/2
        if vpeak_squared < 0:
            # Trường hợp này không thực tế, vì a, s, v0, v_end ≥ 0
            # nhưng ta cứ kiểm tra để tránh lỗi toán học.
            raise ValueError("Dữ liệu đầu vào không hợp lệ.")
        
        vpeak = math.sqrt(vpeak_squared)
        
        # Thời gian tăng tốc đến vpeak
        t1 = (vpeak - v0) / a
        
        # Thời gian giảm tốc từ vpeak xuống v_end
        t3 = (vpeak - v_end) / a
        
        # Tổng thời gian trong trường hợp tam giác
        T = t1 + t3
        # in thời gian tăng tốc, giảm tốc
        print("t1: ", t1)
        print("t3: ", t3)
        return T



def send_gcode_command(ser, command):
    ser.write(command.encode())
    print(f"Đã gửi lệnh: {command}")

    response = ""
    while "Ok" not in response:
        response = ser.readline().decode()

    print(f"Đã nhận phản hồi: {response}")

def test1(ser):
    # Ví dụ sử dụng
    v_start = 200  # Vận tốc bắt đầu (m/s)
    v_max = 700    # Vận tốc lớn nhất (m/s)
    a_max = 1200    # Gia tốc lớn nhất (m/s^2)
    v_end = v_start   # Vận tốc kết thúc (m/s)
    distance = 125 # Quãng đường di chuyển (mm)

    # Ví dụ sử dụng hàm:
    initial_velocity = v_start
    max_velocity = v_max
    final_velocity = v_start
    acceleration = a_max

    # result = calculate_move_time(initial_velocity, max_velocity, final_velocity, acceleration, distance)
    # print(f"Thời gian di chuyển dự đoán: {result} giây")

    

    # send_gcode_command(ser, "G28\n")

    #Gửi gcode thay đổi gia tốc dựa vào biến a_max
    send_gcode_command(ser, "M204 A{a_max}\n".format(a_max=a_max))

    send_gcode_command(ser, "M205 S{v_start}\n".format(v_start=v_start))

    send_gcode_command(ser, "G01 X{distance} Y0 Z-350 F{v_max}\n".format(distance=distance, v_max=v_max))

    start_time = time.time()

    send_gcode_command(ser, "G01 X0 Y0 Z-350\n")

    end_time = time.time()

    execution_time = end_time - start_time

    # movement_time = calculate_movement_time(v_start, v_max, a_max, v_end, distance)
    movement_time = compute_move_time(v_start, v_end, v_max, a_max, distance)
    print(f"Thời gian tính toán: {movement_time:.4f} giây")
    print(f"Thời gian robot phản hồi: {execution_time:.4f} giây")

    ser.close()

import serial.tools.list_ports

def find_and_connect_robot(baudrate=115200, timeout=1):
    # Liệt kê tất cả các cổng COM đang có
    ports = serial.tools.list_ports.comports()
    
    for port_info in ports:
        port_name = port_info.device
        try:
            print(f"Đang thử mở cổng {port_name}...")
            # Thử mở cổng và gửi lệnh kiểm tra
            ser = serial.Serial(port=port_name, baudrate=baudrate, timeout=timeout)
            response = ser.readline().decode('utf-8', errors='replace').strip()
            print(f"Phản hồi: {response}")
            # Gửi lệnh "IsDelta\n" đến robot
            ser.write(b"IsDelta\n")
            
            # Đọc phản hồi
            response = ser.readline().decode('utf-8', errors='replace').strip()
            print(f"Phản hồi: {response}")
            
            # Kiểm tra phản hồi có chứa "YesDelta" hay không
            if "YesDelta" in response:
                print(f"Đã tìm thấy robot ở cổng {port_name}")
                return ser  # Trả về đối tượng Serial đã kết nối với robot
            else:
                ser.close()
        except (serial.SerialException, OSError):
            # Nếu có lỗi khi mở cổng hoặc giao tiếp, ta bỏ qua và thử cổng khác
            pass

    
    # Nếu không tìm thấy robot ở bất kỳ cổng nào
    print("Không tìm thấy robot trên bất cứ cổng COM nào.")
    return None

robot_com = find_and_connect_robot()
test1(robot_com)
