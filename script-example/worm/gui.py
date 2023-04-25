import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox
from PyQt5.uic import loadUi
from PyQt5.QtCore import Qt, pyqtSignal, QObject, QThread
import socket


class Worker(QObject):
    update_lcd_signal = pyqtSignal(str)

    def __init__(self, host, port, parent=None):
        super(Worker, self).__init__(parent)
        self.host = host
        self.port = port
        self.socket = None

    def run(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host, self.port))
            print('Đã kết nối tới server')
        except:
            QMessageBox.warning(self, 'Lỗi', 'Không thể kết nối tới server')
            sys.exit()

        while True:
            # Nhận thông điệp từ server
            data = self.socket.recv(1024).decode()
            self.update_lcd_signal.emit(data)

    def send_message(self, message:str):
        # Gửi thông điệp đến server
        if not message.endswith('\n'):
            message += '\n'
        self.socket.sendall(message.encode())


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        loadUi('worm.ui', self)

        self.host = '127.0.0.1'
        self.port = 8844

        self.worker = Worker(self.host, self.port)

        # Connect signal
        self.worker.update_lcd_signal.connect(self.update_lcd)

        # Connect buttons
        self.pbStartCount.clicked.connect(lambda: self.worker.send_message('#StartCount'))
        self.pbStop.clicked.connect(lambda: self.worker.send_message('#Stop'))
        self.pbReset.clicked.connect(lambda: self.worker.send_message('#Reset'))
        self.pbHeadWash.clicked.connect(lambda: self.worker.send_message('#HeadWash'))
        self.pbSort.clicked.connect(lambda: self.worker.send_message('#Sort'))
        self.pb12S.clicked.connect(lambda: self.worker.send_message('#12S'))
        self.pb12B.clicked.connect(lambda: self.worker.send_message('#12B'))
        self.pb18S.clicked.connect(lambda: self.worker.send_message('#18S'))
        self.pb18B.clicked.connect(lambda: self.worker.send_message('#18B'))
        self.pb30S.clicked.connect(lambda: self.worker.send_message('#30S'))
        self.pb30B.clicked.connect(lambda: self.worker.send_message('#30B'))
        self.pb50B.clicked.connect(lambda: self.worker.send_message('#50B'))

        # Start thread
        self.thread = QThread()
        self.worker.moveToThread(self.thread)
        self.thread.started.connect(self.worker.run)
        self.thread.start()

    def update_lcd(self, data):
        # Cập nhật dữ liệu lên widget LCD
        self.lcdCounter.display(data)

    def closeEvent(self, event):
        # Kết thúc thread trước khi đóng chương trình
        self.thread.quit()
        self.thread.wait()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())
