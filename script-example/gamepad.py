import pygame
import time
import socket
import threading
import math

HOST = '192.168.1.8'
PORT = 8844

software_socket = None

angle = 0
# Lấy giá trị x, y, z từ file, nếu file không tồn tại thì để giá trị mặc định
try:
    with open('coordinates.txt', 'r') as f:
        x = float(f.readline().strip())
        y = float(f.readline().strip())
        z = float(f.readline().strip())
except:
    x , y, z = 79, 37, -645.503
steps = [0.1, 0.5, 1, 5, 10]
step_id = 2
step = steps[step_id]

is_release = True
pressing_button = None

response = True

gripper = False

min_z = -635

cam_pos = (-24, 61.5, -613)

def calculate_sphere_coordinates(x, y, radius, sphere_center=(0, 0, 0)):
    # Kiểm tra xem điểm có nằm ngoài hình cầu hay không. Nếu có thì gán z = sphere_center[2]
    if (x - sphere_center[0]) ** 2 + (y - sphere_center[1]) ** 2 > radius ** 2:
        return x, y, sphere_center[2]
    
    # Tính toán tọa độ z
    z = math.sqrt(radius ** 2 - (x - sphere_center[0]) ** 2 - (y - sphere_center[1]) ** 2) + sphere_center[2]
    return x, y, z

points = []
radius = 40

sphere_center = (81, 61.5, -699.5)

last_time = time.time()

def connect_to_software(host, port):
    global software_socket

    if software_socket is None or software_socket.fileno() < 0:
        try:
            software_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            software_socket.connect((host, port))
            print("Connected to " + host)
            send_init_message()
            return True
        except Exception as e:
            print("Connection failed:", e)
            return False
    return True

def send_init_message():
    try:
        software_socket.sendall(b'ExternalScript\n')
        deltax_mess = software_socket.recv(4096).decode()
        print(deltax_mess)
    except Exception as e:
        print("Error sending message:", e)

def send_joystick_data(axis, value):
    try:
        message = f"Axis: {axis}, Value: {value}\n"
        if abs(value) > 0.1:
            # software_socket.sendall(message.encode())
            print(message)
    except Exception as e:
        print("Error sending joystick data:", e)

def process_joystick_button(button):
    global angle, step_id, step, x, y, z, gripper, response, last_time

    # print("Button:", button)
    if button in [1, 2]:
        if button == 1:
            angle+=step
        elif button == 2:
            angle-=step

        software_socket.sendall(f"GScript = device0 M322 {angle}\n".encode())
    elif button in [3, 0]:
        if button == 3:
            step_id+= 1
            if step_id >= len(steps):
                step_id = len(steps) - 1             
            step = steps[step_id]
        elif button == 0:
            step_id-= 1
            if step_id < 0:
                step_id = 0
            step = steps[step_id]
    elif button in [13, 14]:
        # if button == 11:
        #     y+=step
        # elif button == 12:
        #     y-=step
        if button == 13:
            x-=step
        elif button == 14:
            x+=step

        software_socket.sendall(f"GScript = G01 X{x} Y{sphere_center[1]}\n".encode())
    elif button in [11, 12]:           
        if button == 11:
            z+=step
        elif button == 12:
            z-=step

        point = calculate_sphere_coordinates(x, y, radius, sphere_center)

        if z < point[2]:
            z = point[2]

        software_socket.sendall(f"GScript = G01 Z{z}\n".encode())

    elif button == 6:
        software_socket.sendall(f"GScript = device0 M320\n".encode())
    elif button == 4:
        software_socket.sendall(f"GScript = G28\n".encode())

    elif button == 10:
        point = calculate_sphere_coordinates(x, y, radius, sphere_center)
        print(point)
        z = point[2]

        software_socket.sendall(f"GScript = G01 Z{z}\nG01 Z{min_z}".encode())
        z = min_z
    elif button == 9:
        gripper = not gripper
        if gripper:
            software_socket.sendall(f"GScript = M03 D4\n".encode())
        else:
            software_socket.sendall(f"GScript = M05 D4\n".encode())
    
    elif button == 7:
        software_socket.sendall(f"GScript = G01 X{cam_pos[0]} Y{cam_pos[1]} Z{cam_pos[2]}\n".encode())
    elif button == 8:
        software_socket.sendall(f"GScript = G01 X{x} Y{y} Z{z}\n".encode())

    # Lưu x, y, z vào file, nếu file không tồn tại thì tạo mới
    with open('coordinates.txt', 'w') as f:
        f.write(str(x) + '\n')
        f.write(str(y) + '\n')
        f.write(str(z) + '\n')

    print("x:", x, "y:", y, "z:", z, "angle:", angle, "step:", step)

# Function to handle joystick events
def handle_joystick_events():
    global is_release
    pygame.joystick.init()
    joystick_count = pygame.joystick.get_count()
    if joystick_count == 0:
        print("No gamepad found.")
        return

    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.JOYAXISMOTION:
                # send_joystick_data(event.axis, event.value)
                pass
            elif event.type in [pygame.JOYBUTTONDOWN, pygame.JOYBUTTONUP]:
                if event.type == pygame.JOYBUTTONDOWN and is_release == False:
                    is_release = True
                    process_joystick_button(event.button)
                else:
                    is_release = False

    pygame.quit()

# Initialize Pygame
pygame.init()

# Connect to the software
if not connect_to_software(HOST, PORT):
    print("Failed to connect to the software.")
    pygame.quit()
    exit()

# Start joystick handling in a separate thread
joystick_thread = threading.Thread(target=handle_joystick_events)
joystick_thread.start()

# Wait for the joystick thread to finish
joystick_thread.join()
