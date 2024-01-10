import socket
import pickle
from PyQt5.QtGui import QImage
import numpy as np
import sys
import time
import socket
import pickle
from PyQt5.QtGui import QImage
import numpy as np
import cv2

# Thay đổi các giá trị này cho phù hợp với server của bạn
HOST = '192.168.1.5'
PORT = 8844

# Lấy giá trị HOST và PORT từ file config.txt, nếu config.txt không tồn tại thì tạo mới
try:
    with open('config.txt', 'r') as f:
        HOST = f.readline().strip()
        PORT = int(f.readline().strip())
except:
    pass

# Lấy giá trị HOST và PORT được truyền vào từ Argument
if len(sys.argv) > 1:
    HOST = sys.argv[1]
if len(sys.argv) > 2:
    PORT = int(sys.argv[2])

with open('config.txt', 'w') as f:
    f.write(HOST + '\n')
    f.write(str(PORT) + '\n')

def Send_Init_Message():
    Software_Socket.sendall(b'ClientName=ImageClient\n')

def ConnectToSoftware(host, port):
    global Software_Socket

    # if Software_Socket == None or Software_Socket.fileno() < 0:
    try:
        Software_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        Software_Socket.connect((HOST, PORT))

        print("Connected " + HOST)
        # Lưu HOST và PORT vào file để lần sau không cần nhập lại
        with open('config.txt', 'w') as f:
            f.write(HOST + '\n')
            f.write(str(PORT) + '\n')

        Send_Init_Message()
        # pass b'deltax'
        hello = str(Software_Socket.recv(4096))

        print(hello)

        return True
    except socket.timeout:
        print("Fail connection")
        return False
    
    return True

# Hàm biến ảnh sang các đường nét
def Canny(img):
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img = cv2.Canny(img, 100, 200)
    return img

# Gửi thông tin đối tượng nhận diện đến server với format: "#Objects=x1,y1,z1,w1,l1,a1;x2,y2,z2,w2,l2,a2;...;xn,yn,zn,wn,ln,an"
def Send_Object_Info(objects):
    if len(objects) == 0:
        return
    message = "#Objects="
    for object in objects:
        message += str(object[0]) + ',' + str(object[1]) + ',' + str(object[2]) + ',' + str(object[3]) + ',' + str(object[4]) + ',' + str(object[5]) + ';'
    message = message[:-1]
    message += '\n'
    Software_Socket.sendall(message.encode())

# Gửi ví dụ objects đến server
def Send_Example_Objects():
    objects = [[1 ,1, 2, 3, 4, 5, 6]]
    Send_Object_Info(objects)

def receive_image_from_server():
    while True:
        data = b''
        while True:
            packet = Software_Socket.recv(4096)
            if not packet: break
            data += packet
            if len(packet) < 4096: break

        if data:
            try:
                if data.startswith(b'Image\n'):
                    print("Received image")
                    image_data = data[6:]
                    # Convert data to image
                    nparr = np.frombuffer(image_data, np.uint8)
                    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

                    img = Canny(img)

                    # Display image
                    cv2.imshow('Received Image', img)
                    cv2.waitKey(1)

                else:
                    # print(data)
                    pass
            except Exception as e:
                print("Error receiving image:", e)
        else:
            break

if __name__ == '__main__':
    # Kết nối đến server, nếu server bị đứt thì tìm cách kết nối lại
    while True:
        if ConnectToSoftware(HOST, PORT):
            break
        else:
            time.sleep(1)

    Send_Example_Objects()
    receive_image_from_server()
    

