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
