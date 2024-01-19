# import socket
# import pickle
# from PyQt5.QtGui import QImage
# import numpy as np
# import sys
# import time
# import socket
# import pickle
# from PyQt5.QtGui import QImage
# import numpy as np
# import cv2
# import threading
# import threading
# import time
# import numpy as np
# import cv2

# img = None
# lock = threading.Lock()

# # Thay đổi các giá trị này cho phù hợp với server của bạn
# HOST = '192.168.1.8'
# PORT = 8844

# points = []

# # Lấy giá trị HOST và PORT từ file config.txt, nếu config.txt không tồn tại thì tạo mới
# try:
#     with open('config.txt', 'r') as f:
#         HOST = f.readline().strip()
#         PORT = int(f.readline().strip())
# except:
#     pass

# # Lấy giá trị HOST và PORT được truyền vào từ Argument
# if len(sys.argv) > 1:
#     HOST = sys.argv[1]
# if len(sys.argv) > 2:
#     PORT = int(sys.argv[2])

# with open('config.txt', 'w') as f:
#     f.write(HOST + '\n')
#     f.write(str(PORT) + '\n')

# def Send_Init_Message():
#     Software_Socket.sendall(b'ClientName=ImageClient\n')

# def ConnectToSoftware(host, port):
#     global Software_Socket

#     # if Software_Socket == None or Software_Socket.fileno() < 0:
#     try:
#         Software_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#         Software_Socket.connect((HOST, PORT))

#         print("Connected " + HOST)
#         # Lưu HOST và PORT vào file để lần sau không cần nhập lại
#         with open('config.txt', 'w') as f:
#             f.write(HOST + '\n')
#             f.write(str(PORT) + '\n')

#         Send_Init_Message()
#         # pass b'deltax'
#         hello = str(Software_Socket.recv(4096))

#         print(hello)

#         return True
#     except socket.timeout:
#         print("Fail connection")
#         return False
    
#     return True

# # Hàm biến ảnh sang các đường nét
# def Canny(img):
#     img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#     img = cv2.Canny(img, 100, 200)
#     return img

# # Gửi thông tin đối tượng nhận diện đến server với format: "#Objects=x1,y1,z1,w1,l1,a1;x2,y2,z2,w2,l2,a2;...;xn,yn,zn,wn,ln,an"
# def Send_Object_Info(objects):
#     if len(objects) == 0:
#         return
#     # #Object=x1,y1,z1,w1,l1,a1;x2,y2,z2,w2,l2,a2;...;xn,yn,zn,wn,ln,an
#     message = "#Blobs="
#     for object in objects:
#         message += str(object[0]) + ',' + str(object[1]) + ',' + str(object[2]) + ',' + str(object[3]) + ',' + str(object[4]) + ',' + str(object[5]) + ';'
#     message = message[:-1]
#     message += '\n'
#     Software_Socket.sendall(message.encode())

# # Gửi ví dụ objects đến server
# def Send_Example_Objects():
#     objects = [[0 ,200, 250, 40, 20, 50]]
#     Send_Object_Info(objects)

# # Tạo ra cửa sổ hiển thị ảnh mà khi click vào một điểm trên ảnh thì sẽ lấy tọa độ của điểm đó và vẽ một chấm màu đỏ
# def mouse_click(event, x, y, flags, param):
#     global points
#     if event == cv2.EVENT_LBUTTONDOWN:
#         print(x, y)
#         cv2.circle(img, (x, y), 2, (0, 0, 255), -1)
#         # Lưu thông tin điểm vào list
#         # Tạo ra giá trị góc ngẫu nhiên từ -90 đến 90
#         angle = np.random.randint(-90, 90)                            
#         points.append([0, x, y, 20, 40, angle])
#     if event == cv2.EVENT_RBUTTONDOWN:
#         Send_Object_Info(points)
#         points.clear()

# cv2.namedWindow('Received Image')
# cv2.setMouseCallback('Received Image', mouse_click)

# # Add missing import statements
# # Define a lock for thread synchronization
# lock = threading.Lock()

# def receive_image_from_server():
#     global img
#     while True:
#         data = b''
#         while True:
#             packet = Software_Socket.recv(4096)
#             if not packet: break
#             data += packet
#             if len(packet) < 4096: break

#         if data:
#             try:
#                 if data.startswith(b'Image\n'):
#                     print("Received image")
#                     image_data = data[6:]
#                     # Convert data to image
#                     nparr = np.frombuffer(image_data, np.uint8)
#                     with lock:
#                         img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)    
#                         print("Decode image")      
#                         cv2.imshow('Received Image', img)       
#                         cv2.waitKey(0)   

#                 else:
#                     print("Image not found")
#                     pass
#             except Exception as e:
#                 print("Error receiving image:", e)
#         else:
#             break

# def display_image():
#     global img
#     while True:
#         time.sleep(1)
#         print("Loop display image")
#         with lock:
#             if img is not None:
#                 cv2.imshow('Received Image', img)
#                 cv2.waitKey(0)
#                 print("Display image")

# try:
#     while True:
#         if ConnectToSoftware(HOST, PORT):
#             break
#         else:
#             time.sleep(1)

#     receive_thread = threading.Thread(target=receive_image_from_server)
#     # display_thread = threading.Thread(target=display_image)

#     receive_thread.start()
#     # display_thread.start()

#     # Wait for both threads to finish
#     receive_thread.join()
#     # display_thread.join()

# except KeyboardInterrupt:
#     # Handle KeyboardInterrupt exception
#     cv2.destroyAllWindows()
#     print("KeyboardInterrupt")


import sys
import socket
import numpy as np
import cv2
import threading
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtCore import pyqtSignal, pyqtSlot, Qt, QThread

class ImageReceiver(QThread):
    image_received = pyqtSignal(np.ndarray)

    def __init__(self, host, port):
        super().__init__()
        self.host = host
        self.port = port
        self.running = True

    def run(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as self.sock:
            self.sock.connect((self.host, self.port))
            print('Connected to %s:%s' % (self.host, self.port))
            self.sock.sendall(b'ClientName=ImageClient\n')
            while self.running:
                data = b''
                while True:
                    # print('reading data')
                    packet = self.sock.recv(4096)
                    if not packet: break
                    data += packet
                    if len(packet) < 4096: break

                if data:
                    print('Received data')
                    
                    if data.startswith(b'Image\n'):
                        try:
                            print('Received image')
                            image_data = data[6:]
                            nparr = np.frombuffer(image_data, np.uint8)
                            img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                            self.image_received.emit(img)
                        except Exception as e:
                            print('Error receiving image:', e)
                    else:
                        print(data)

    def stop(self):
        self.running = False

class MainWindow(QMainWindow):
    def __init__(self, host, port):
        super().__init__()
        self.initUI()
        self.receiver = ImageReceiver(host, port)
        self.receiver.image_received.connect(self.updateImage)
        self.receiver.start()

    def initUI(self):
        self.label = QLabel(self)
        self.points = []

    @pyqtSlot(np.ndarray)
    def updateImage(self, img):
        self.current_image = img
        height, width, channel = img.shape
        bytesPerLine = 3 * width
        qImg = QImage(img.data, width, height, bytesPerLine, QImage.Format_RGB888).rgbSwapped()
        self.label.setPixmap(QPixmap.fromImage(qImg))
        # Label size will be adjusted to image size
        self.label.adjustSize()
        # Window size will be adjusted to image size
        self.resize(width, height)


    def mousePressEvent(self, event):
        x = event.x()
        y = event.y()
        if event.button() == Qt.LeftButton:
            print(x, y)
            angle = np.random.randint(-90, 90)
            self.points.append([0, x, y, 2, 2, angle])
            cv2.circle(self.current_image, (x, y), 2, (0, 0, 255), -1)
            self.updateImage(self.current_image)

        elif event.button() == Qt.RightButton:
            self.sendObjectInfo(self.points)
            self.points.clear()

    def sendObjectInfo(self, points):
        if len(points) == 0:
            return
        message = "#Blobs="
        for object in points:
            message += str(object[0]) + ',' + str(object[1]) + ',' + str(object[2]) + ',' + str(object[3]) + ',' + str(object[4]) + ',' + str(object[5]) + ';'
        message = message[:-1]
        message += '\n'
        self.receiver.sock.sendall(message.encode())

def main():
    host = '192.168.1.8'  # Replace with your host
    port = 8844           # Replace with your port

    app = QApplication(sys.argv)
    mainWindow = MainWindow(host, port)
    mainWindow.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
