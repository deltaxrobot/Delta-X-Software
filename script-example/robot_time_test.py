import serial
import time

import math

def calculate_move_time(initial_velocity, max_velocity, final_velocity, acceleration, distance):
    # Acceleration time.
    t_acc = (max_velocity - initial_velocity) / acceleration
    
    # Deceleration time.
    t_dec = (max_velocity - final_velocity) / acceleration
    
    # Acceleration and deceleration distances.
    d_acc = (max_velocity**2 - initial_velocity**2) / (2 * acceleration)
    d_dec = (max_velocity**2 - final_velocity**2) / (2 * acceleration)
    
    # Constant-speed distance.
    d_constant = distance - d_acc - d_dec
    
    # A negative cruise distance means max_velocity cannot be reached.
    if d_constant < 0:
        # Recalculate peak velocity for the available distance.
        max_velocity = ((2 * acceleration * distance + initial_velocity**2 + final_velocity**2) / 2)**0.5
        t_acc = (max_velocity - initial_velocity) / acceleration
        t_dec = (max_velocity - final_velocity) / acceleration
        t_constant = 0
    else:
        # Constant-speed travel time.
        t_constant = d_constant / max_velocity
    
    # Total travel time.
    t_total = t_acc + t_constant + t_dec
    
    return t_total

def calculate_movement_time(v_start, v_max, a_max, v_end, distance):
    # Calculate acceleration time.
    t_acc = (v_max - v_start) / a_max

    # Calculate acceleration distance.
    d_acc = v_start * t_acc + 0.5 * a_max * t_acc**2

    # Calculate deceleration time.
    t_dec = (v_max - v_end) / a_max

    # Calculate deceleration distance.
    d_dec = v_max * t_dec - 0.5 * a_max * t_dec**2
    print("d_dec: ", d_dec)

    # Calculate distance travelled at maximum velocity.
    d_max = distance - d_acc - d_dec

    print("d_max: ", d_max)

    if d_max <= 0:
        # Maximum velocity is not reached.
        t_max = 0
        v_max = math.sqrt(v_start**2 + a_max * distance)
        t_acc = (v_max * 1.5 - v_start * 1.5) / (a_max * 1.5)
        t_dec = t_acc

        print("t_acc: ", t_acc)
    else:
        # Calculate travel time at maximum velocity.
        t_max = d_max / v_max
        print("t_max: ", t_max)

    # Calculate total travel time.
    total_time = t_acc + t_max + t_dec

    return total_time

def compute_move_time(v0, v_end, vmax, a, s):
    """
    Calculate robot travel time for a trapezoidal velocity profile.
    - v0: initial velocity (m/s)
    - v_end: final velocity (m/s)
    - vmax: maximum velocity (m/s)
    - a: acceleration (m/s^2)
    - s: travel distance (m)

    Returns the total travel time in seconds.
    """
    
    # Distance required to accelerate from v0 to vmax.
    # s1 = (vmax^2 - v0^2) / (2a)
    s1 = (vmax**2 - v0**2) / (2 * a)
    
    # Distance required to decelerate from vmax to v_end.
    # s3 = (vmax^2 - v_end^2) / (2a)
    s3 = (vmax**2 - v_end**2) / (2 * a)
    
    # Use a cruise segment when the total distance exceeds s1 + s3.
    if s > s1 + s3:
        # Trapezoidal profile.
        # Acceleration time:
        # t1 = (vmax - v0) / a
        t1 = (vmax - v0) / a
        
        # Deceleration time:
        # t3 = (vmax - v_end) / a
        t3 = (vmax - v_end) / a
        
        # Cruise distance:
        s2 = s - (s1 + s3)
        
        # Cruise time:
        # t2 = s2 / vmax
        t2 = s2 / vmax
        
        # Total time:
        T = t1 + t2 + t3
        # Report acceleration, deceleration, and cruise times.
        print("t1: ", t1)
        print("t2: ", t2)
        print("t3: ", t3)
        return T
    
    else:
        # The distance is too short to reach vmax, so use a triangular profile.
        # Calculate peak velocity from:
        # s = (vpeak^2 - v0^2)/(2a) + (vpeak^2 - v_end^2)/(2a)
        # => 2a s = 2vpeak^2 - (v0^2 + v_end^2)
        # => vpeak^2 = a s + (v0^2 + v_end^2)/2
        # Take the square root:
        
        vpeak_squared = a*s + (v0**2 + v_end**2)/2
        if vpeak_squared < 0:
            # This is not physically meaningful for non-negative inputs, but
            # keep the guard to prevent an invalid square root.
            raise ValueError("Invalid motion-profile input")
        
        vpeak = math.sqrt(vpeak_squared)
        
        # Time to accelerate to vpeak.
        t1 = (vpeak - v0) / a
        
        # Time to decelerate from vpeak to v_end.
        t3 = (vpeak - v_end) / a
        
        # Total time for the triangular profile.
        T = t1 + t3
        # Report acceleration and deceleration times.
        print("t1: ", t1)
        print("t3: ", t3)
        return T



def send_gcode_command(ser, command):
    ser.write(command.encode())
    print(f"Command sent: {command}")

    response = ""
    while "Ok" not in response:
        response = ser.readline().decode()

    print(f"Response received: {response}")

def test1(ser):
    # Example values.
    v_start = 200  # Initial velocity (m/s).
    v_max = 700    # Maximum velocity (m/s).
    a_max = 1200    # Maximum acceleration (m/s^2).
    v_end = v_start   # Final velocity (m/s).
    distance = 125 # Travel distance (mm).

    # Function usage example:
    initial_velocity = v_start
    max_velocity = v_max
    final_velocity = v_start
    acceleration = a_max

    # result = calculate_move_time(initial_velocity, max_velocity, final_velocity, acceleration, distance)
    # print(f"Predicted travel time: {result} seconds")

    

    # send_gcode_command(ser, "G28\n")

    # Send G-code that sets acceleration from a_max.
    send_gcode_command(ser, "M204 A{a_max}\n".format(a_max=a_max))

    send_gcode_command(ser, "M205 S{v_start}\n".format(v_start=v_start))

    send_gcode_command(ser, "G01 X{distance} Y0 Z-350 F{v_max}\n".format(distance=distance, v_max=v_max))

    start_time = time.time()

    send_gcode_command(ser, "G01 X0 Y0 Z-350\n")

    end_time = time.time()

    execution_time = end_time - start_time

    # movement_time = calculate_movement_time(v_start, v_max, a_max, v_end, distance)
    movement_time = compute_move_time(v_start, v_end, v_max, a_max, distance)
    print(f"Calculated motion time: {movement_time:.4f} seconds")
    print(f"Robot response time: {execution_time:.4f} seconds")

    ser.close()

import serial.tools.list_ports

def find_and_connect_robot(baudrate=115200, timeout=1):
    # Enumerate available COM ports.
    ports = serial.tools.list_ports.comports()
    
    for port_info in ports:
        port_name = port_info.device
        try:
            print(f"Trying port {port_name}...")
            # Open the port and send a probe command.
            ser = serial.Serial(port=port_name, baudrate=baudrate, timeout=timeout)
            response = ser.readline().decode('utf-8', errors='replace').strip()
            print(f"Response: {response}")
            # Send "IsDelta\n" to probe for a robot.
            ser.write(b"IsDelta\n")
            
            # Read the response.
            response = ser.readline().decode('utf-8', errors='replace').strip()
            print(f"Response: {response}")
            
            # Confirm that the response contains "YesDelta".
            if "YesDelta" in response:
                print(f"Robot found on port {port_name}")
                return ser  # Return the connected serial object.
            else:
                ser.close()
        except (serial.SerialException, OSError):
            # Ignore port/communication errors and try the next port.
            pass

    
    # No port identified a Delta robot.
    print("No robot was found on any COM port")
    return None

robot_com = find_and_connect_robot()
test1(robot_com)
