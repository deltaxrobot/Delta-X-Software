import pygame
import time
import socket
import threading
import math

HOST = '192.168.1.8'
PORT = 8844

software_socket = None

angle = 0

x , y, z = 0, 0, -238

steps = [0.1, 0.5, 1, 5, 10]
step_id = 2
step = steps[step_id]

is_release = True
pressing_button = None

response = True

gripper = False

def calculate_sphere_coordinates(x, y, radius, sphere_center=(0, 0, 0)):
    # Clamp z to the sphere centre when the point is outside the sphere.
    if (x - sphere_center[0]) ** 2 + (y - sphere_center[1]) ** 2 > radius ** 2:
        return x, y, sphere_center[2]
    
    # Calculate z.
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
    # The function returns quickly, so consecutive calls are less than 0.1 s apart.
    global last_time
    if time.time() - last_time < 0.2:
        return
    global x,y
    try:
        message = f"Axis: {axis}, Value: {value}\n"
        # if abs(value) > 0.1:
        #     if axis == 0:
        #         x+=step * value * 0.1
        #     elif axis == 1:
        #         y+=step * value * 0.1
        #     gcode = f"GScript = G01 X{x} Y{y} F200\n"
        #     software_socket.sendall(gcode.encode())
        #     print(gcode)
    except Exception as e:
        print("Error sending joystick data:", e)

def process_joystick_button(button):
    global angle, step_id, step, x, y, z, gripper, response, last_time

    print("Button:", button)
    if button in [3, 0]:
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
    elif button in [11, 12, 13, 14]:
        if button == 11:
            y+=step
        elif button == 12:
            y-=step
        if button == 13:
            x-=step
        elif button == 14:
            x+=step

        software_socket.sendall(f"GScript = G01 X{x} Y{y}\n".encode())
        pass
    elif button in [9, 10]:           
        if button == 9:
            z+=step
        elif button == 10:
            z-=step

        software_socket.sendall(f"GScript = G01 Z{z}\n".encode())
        pass

    elif button == 2:
        software_socket.sendall(f"GScript = G28\n".encode())

    elif button == 6:
        gripper = not gripper
        if gripper:
            software_socket.sendall(f"GScript = M03 D4\n".encode())
        else:
            software_socket.sendall(f"GScript = M05 D4\n".encode())
    
    elif button == 7:
        # software_socket.sendall(f"GScript = G01 X{cam_pos[0]} Y{cam_pos[1]} Z{cam_pos[2]}\n".encode())
        pass
    elif button == 8:
        # software_socket.sendall(f"GScript = G01 X{x} Y{y} Z{z}\n".encode())
        pass

    # Store x, y, and z, creating the file when necessary.
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
                send_joystick_data(event.axis, event.value)
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
