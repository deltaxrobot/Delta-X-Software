import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt5.QtGui import QPainter, QPen, QColor
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QGraphicsScene, QGraphicsView, QGraphicsRectItem, QGraphicsEllipseItem, QGraphicsLineItem

class DrawingWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.shapes = []

    def paintEvent(self, event):
        painter = QPainter(self)
        pen = QPen()
        pen.setWidth(2)
        painter.setPen(pen)

        for shape in self.shapes:
            if shape['type'] == 'rectangle':
                painter.drawRect(shape['x'], shape['y'], shape['width'], shape['height'])
            elif shape['type'] == 'point':
                painter.drawPoint(shape['x'], shape['y'])
            elif shape['type'] == 'circle':
                painter.drawEllipse(shape['x'], shape['y'], shape['radius'], shape['radius'])
            elif shape['type'] == 'line':
                painter.drawLine(shape['x1'], shape['y1'], shape['x2'], shape['y2'])
            elif shape['type'] == 'rotated_rectangle':
                painter.save()
                painter.translate(shape['x'], shape['y'])
                painter.rotate(shape['angle'])
                painter.drawRect(-shape['width']/2, -shape['height']/2, shape['width'], shape['height'])
                painter.restore()



    def add_rectangle(self, x, y, width, height):
        self.shapes.append({'type': 'rectangle', 'x': x, 'y': y, 'width': width, 'height': height})
        self.update()

    def add_rotated_rectangle(self, x, y, width, height, angle):
        self.shapes.append({'type': 'rotated_rectangle', 'x': x, 'y': y, 'width': width, 'height': height, 'angle': angle})
        self.update()

    def add_point(self, x, y):
        self.shapes.append({'type': 'point', 'x': x, 'y': y})
        self.update()

    def add_circle(self, x, y, radius):
        self.shapes.append({'type': 'circle', 'x': x, 'y': y, 'radius': radius})
        self.update()

    def add_line(self, x1, y1, x2, y2):
        self.shapes.append({'type': 'line', 'x1': x1, 'y1': y1, 'x2': x2, 'y2': y2})
        self.update()

    def clear(self):
        self.shapes = []
        self.update()

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Drawing Program')
        self.setGeometry(100, 100, 500, 500)

        self.drawing_widget = DrawingWidget(self)
        self.setCentralWidget(self.drawing_widget)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_R:
            self.drawing_widget.add_rectangle(100, 100, 200, 150)
        elif event.key() == Qt.Key_P:
            self.drawing_widget.add_point(250, 250)
        elif event.key() == Qt.Key_C:
            self.drawing_widget.add_circle(250, 250, 100)
        elif event.key() == Qt.Key_L:
            self.drawing_widget.add_line(100, 100, 400, 400)
        elif event.key() == Qt.Key_Delete:
            self.drawing_widget.clear()
        elif event.key() == Qt.Key_A:
            self.drawing_widget.add_rotated_rectangle(250, 250, 200, 150, 45)

    

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())