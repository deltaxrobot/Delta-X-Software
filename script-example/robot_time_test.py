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



def send_gcode_command(ser, command):
    ser.write(command.encode())
    print(f"Đã gửi lệnh: {command}")

    response = ""
    while "Ok" not in response:
        response = ser.readline().decode()

    print(f"Đã nhận phản hồi: {response}")

def test1():
    # Ví dụ sử dụng
    v_start = 100  # Vận tốc bắt đầu (m/s)
    v_max = 300    # Vận tốc lớn nhất (m/s)
    a_max = 1000    # Gia tốc lớn nhất (m/s^2)
    v_end = v_start   # Vận tốc kết thúc (m/s)
    distance = 80 # Quãng đường di chuyển (m)

    # 0.4

    # Ví dụ sử dụng hàm:
    initial_velocity = v_start
    max_velocity = v_max
    final_velocity = v_start
    acceleration = a_max

    # result = calculate_move_time(initial_velocity, max_velocity, final_velocity, acceleration, distance)
    # print(f"Thời gian di chuyển dự đoán: {result} giây")

    movement_time = calculate_movement_time(v_start, v_max, a_max, v_end, distance)
    print(f"Thời gian di chuyển: {movement_time:.4f} giây")

    # Kết nối với cổng COM18
    ser = serial.Serial('COM5', 115200, timeout=1)

    # Đợi 2 giây để Arduino khởi động 
    time.sleep(2)

    send_gcode_command(ser, "G28\n")

    #Gửi gcode thay đổi gia tốc dựa vào biến a_max
    send_gcode_command(ser, "M204 A{a_max}\n".format(a_max=a_max))

    send_gcode_command(ser, "M205 S{v_start}\n".format(v_start=v_start))

    send_gcode_command(ser, "G01 X90 Z-325 F{v_max}\n".format(v_max=v_max))

    start_time = time.time()

    send_gcode_command(ser, "G01 X10 Z-325\n")

    end_time = time.time()

    execution_time = end_time - start_time

    print(f"Thời gian thực hiện lệnh: {execution_time:.4f} giây")

    ser.close()

import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Load dataset
file_path = r'script-example\datatable.csv'  # Thay đổi đường dẫn tới file dataset của bạn
dataset = pd.read_csv(file_path)

# Filter the rows where distance_to_move is 100
filtered_dataset = dataset[dataset['distance_to_move'] == 100]

# Adjust the unit of time to milliseconds
filtered_dataset['execute_time'] = filtered_dataset['execute_time']

# Split data into features and target
X_filtered = filtered_dataset[['begin_velocity', 'desired_velocity', 'acceleration']]
y_filtered = filtered_dataset['execute_time']

# Train linear regression model
model_filtered = LinearRegression()
model_filtered.fit(X_filtered, y_filtered)

# Predict on the filtered data
y_pred_filtered = model_filtered.predict(X_filtered)

# Evaluate model
mse_filtered = mean_squared_error(y_filtered, y_pred_filtered)
r2_filtered = r2_score(y_filtered, y_pred_filtered)

print("Mean Squared Error:", mse_filtered)
print("R-squared:", r2_filtered)

# Extract coefficients
coefficients = model_filtered.coef_
intercept = model_filtered.intercept_

print("Coefficients:", coefficients)
print("Intercept:", intercept)

# Function to predict execution time based on the fitted model
def predict_execution_time(begin_velocity, desired_velocity, acceleration):
    return coefficients[0] * begin_velocity + coefficients[1] * desired_velocity + coefficients[2] * acceleration + intercept

# Example usage
predicted_time = predict_execution_time(20, 200, 1000)
print("Predicted execution time:", predicted_time/1000)
