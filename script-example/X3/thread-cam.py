import sys
import cv2
import cv2.aruco as aruco
import serial
import time
import threading
import numpy as np
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

class RobotThread(QThread):
    status_signal = pyqtSignal(str)
    
    def __init__(self, home_z=-291.28):
        super().__init__()
        self.conn = None
        self.home_z = home_z
        self.running = False
        self.paused = False
        self.aruco_mode = False
        self.aruco_target = None
        self.pick_height = -50  # Height above object for picking
        self.place_position = (200, 0)  # Place position (X, Y)
        
    def connect_robot(self, port=None):
        if not port:
            import serial.tools.list_ports
            for p in serial.tools.list_ports.comports():
                try:
                    conn = serial.Serial(p.device, 115200, timeout=2)
                    time.sleep(1)
                    conn.write(b"IsDelta\n")
                    if conn.readline().decode().strip() == "YesDelta":
                        self.conn = conn
                        self.status_signal.emit(f"Robot connected to {p.device}")
                        return True
                    conn.close()
                except:
                    continue
            self.status_signal.emit("Delta robot not found!")
            return False
        else:
            try:
                self.conn = serial.Serial(port, 115200, timeout=2)
                time.sleep(1)
                self.conn.write(b"IsDelta\n")
                if self.conn.readline().decode().strip() == "YesDelta":
                    self.status_signal.emit(f"Robot connected to {port}")
                    return True
                self.status_signal.emit("Not a delta robot!")
                return False
            except Exception as e:
                self.status_signal.emit(f"Connection error: {e}")
                return False
    
    def send_gcode(self, cmd):
        if not self.conn:
            return False
        try:
            self.status_signal.emit(f"Send: {cmd}")
            self.conn.write(f"{cmd}\n".encode())
            response = self.conn.readline().decode().strip()
            self.status_signal.emit(f"Reply: {response}")
            return True
        except:
            return False
    
    def start_program(self):
        self.running = True
        self.start()
    
    def pause_program(self):
        self.paused = not self.paused
        
    def stop_program(self):
        self.running = False
        
    def set_aruco_mode(self, enabled):
        self.aruco_mode = enabled
        
    def set_aruco_target(self, x, y):
        """Set ArUco target position from camera"""
        self.aruco_target = (x, y)
        self.status_signal.emit(f"ArUco target set: X={x:.1f}, Y={y:.1f}")
        
    def pick_and_place_sequence(self, target_x, target_y):
        """Execute pick and place sequence at target position"""
        self.status_signal.emit(f"Starting pick & place at ({target_x:.1f}, {target_y:.1f})")
        
        # Move to position above target
        self.send_gcode(f"G01 Z{self.home_z + self.pick_height}")
        self.send_gcode(f"G01 X{target_x} Y{target_y}")
        
        # Lower to pick
        self.send_gcode(f"G01 Z{self.home_z - 20}")
        
        # Simulate gripper close (you can add actual gripper control here)
        self.status_signal.emit("Gripper: CLOSE")
        time.sleep(0.5)
        
        # Lift object
        self.send_gcode(f"G01 Z{self.home_z + self.pick_height}")
        
        # Move to place position
        place_x, place_y = self.place_position
        self.send_gcode(f"G01 X{place_x} Y{place_y}")
        
        # Lower to place
        self.send_gcode(f"G01 Z{self.home_z - 20}")
        
        # Simulate gripper open
        self.status_signal.emit("Gripper: OPEN")
        time.sleep(0.5)
        
        # Return to safe height
        self.send_gcode(f"G01 Z{self.home_z + self.pick_height}")
        
        self.status_signal.emit("Pick & place completed!")
        
    def run(self):
        if not self.conn:
            self.status_signal.emit("Robot not connected!")
            return
        
        self.send_gcode("G28")  # Home
        
        if self.aruco_mode:
            # ArUco detection mode - wait for targets
            self.status_signal.emit("ArUco mode: Waiting for targets...")
            while self.running:
                if self.aruco_target and not self.paused:
                    target_x, target_y = self.aruco_target
                    self.pick_and_place_sequence(target_x, target_y)
                    self.aruco_target = None  # Reset after processing
                
                while self.paused and self.running:
                    time.sleep(0.1)
                    
                time.sleep(0.1)  # Check for new targets
        else:
            # Original demo sequence
            for i in range(5):
                if not self.running:
                    break
                    
                while self.paused and self.running:
                    time.sleep(0.1)
                    
                if not self.running:
                    break
                    
                self.status_signal.emit(f"Loop {i+1}/5")
                self.send_gcode(f"G01 Z{self.home_z - 80}")
                self.send_gcode("G01 X-100")
                self.send_gcode(f"G01 Z{self.home_z - 100}")
                self.send_gcode(f"G01 Z{self.home_z - 80}")
                self.send_gcode("G01 X100")
                self.send_gcode(f"G01 Z{self.home_z - 100}")
        
        self.send_gcode("G28")  # Home
        self.status_signal.emit("Program completed!")
        self.running = False
    
    def disconnect(self):
        self.running = False
        if self.conn:
            self.conn.close()
            self.status_signal.emit("Robot disconnected")

class CameraThread(QThread):
    frame_signal = pyqtSignal(object)
    status_signal = pyqtSignal(str)
    aruco_detected = pyqtSignal(float, float)  # x, y coordinates
    
    def __init__(self):
        super().__init__()
        self.cap = None
        self.running = False
        self.camera_id = 0
        self.aruco_detection = False
        
        # ArUco setup (compatible with OpenCV 4.x)
        self.aruco_dict = None
        self.aruco_params = None
        self.aruco_api_type = None
        
        # Try different API versions
        if self._init_aruco_v4_7():
            self.aruco_api_type = "4.7+"
            print("ArUco initialized (OpenCV 4.7+)")
        elif self._init_aruco_v4_0():
            self.aruco_api_type = "4.0-4.6"
            print("ArUco initialized (OpenCV 4.0-4.6)")
        elif self._init_aruco_fallback():
            self.aruco_api_type = "fallback"
            print("ArUco initialized (fallback)")
        else:
            print("Failed to initialize ArUco - all API attempts failed")
    
    def _init_aruco_v4_7(self):
        """Try OpenCV 4.7+ API"""
        try:
            self.aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
            self.aruco_params = aruco.DetectorParameters()
            return True
        except:
            return False
    
    def _init_aruco_v4_0(self):
        """Try OpenCV 4.0-4.6 API"""
        try:
            self.aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
            self.aruco_params = aruco.DetectorParameters_create()
            return True
        except:
            return False
    
    def _init_aruco_fallback(self):
        """Try fallback API"""
        try:
            self.aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_4X4_50)
            self.aruco_params = cv2.aruco.DetectorParameters_create()
            return True
        except:
            return False
    
    def _detect_aruco_markers(self, gray_image):
        """Detect ArUco markers with API compatibility"""
        try:
            if self.aruco_api_type == "4.7+":
                # OpenCV 4.7+
                detector = aruco.ArucoDetector(self.aruco_dict, self.aruco_params)
                corners, ids, rejected = detector.detectMarkers(gray_image)
            else:
                # OpenCV 4.0-4.6 and fallback
                corners, ids, rejected = aruco.detectMarkers(gray_image, self.aruco_dict, parameters=self.aruco_params)
            return corners, ids, rejected
        except Exception as e:
            print(f"ArUco detection error: {e}")
            return None, None, None
    
    def _draw_detected_markers(self, image, corners, ids):
        """Draw detected markers with API compatibility"""
        try:
            if self.aruco_api_type == "4.7+":
                return aruco.drawDetectedMarkers(image, corners, ids)
            else:
                return aruco.drawDetectedMarkers(image, corners, ids)
        except:
            return image
        
        # Camera calibration (you should calibrate your camera)
        self.camera_matrix = np.array([[800, 0, 320],
                                      [0, 800, 240],
                                      [0, 0, 1]], dtype=np.float32)
        self.dist_coeffs = np.zeros((4, 1))
        
    def connect_camera(self, camera_id=0):
        self.camera_id = camera_id
        self.cap = cv2.VideoCapture(camera_id)
        if self.cap.isOpened():
            self.status_signal.emit(f"Camera {camera_id} connected")
            return True
        else:
            self.status_signal.emit(f"Failed to connect camera {camera_id}")
            return False
    
    def start_capture(self):
        self.running = True
        self.start()
    
    def stop_capture(self):
        self.running = False
        
    def set_aruco_detection(self, enabled):
        if enabled and self.aruco_dict is None:
            self.status_signal.emit("ArUco not initialized - cannot enable detection")
            return False
        self.aruco_detection = enabled
        status = "enabled" if enabled else "disabled"
        self.status_signal.emit(f"ArUco detection {status}")
        return True
        
    def run(self):
        while self.running and self.cap and self.cap.isOpened():
            ret, frame = self.cap.read()
            if ret:
                # Basic image processing
                processed_frame = self.process_frame(frame)
                self.frame_signal.emit(processed_frame)
            time.sleep(0.03)  # ~30 FPS
    
    def process_frame(self, frame):
        processed_frame = frame.copy()
        
        if self.aruco_detection and self.aruco_dict is not None:
            # ArUco detection
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            corners, ids, rejected = self._detect_aruco_markers(gray)
            
            if ids is not None:
                # Draw detected markers
                processed_frame = self._draw_detected_markers(processed_frame, corners, ids)
                
                # Calculate marker positions
                for i, marker_id in enumerate(ids):
                    # Get marker center
                    center = corners[i][0].mean(axis=0)
                    marker_x, marker_y = center
                    
                    # Convert pixel coordinates to robot coordinates
                    # This is a simple mapping - you should calibrate for your setup
                    robot_x = (marker_x - 320) * 0.5  # Scale and offset
                    robot_y = (240 - marker_y) * 0.5  # Invert Y and scale
                    
                    # Draw center point
                    cv2.circle(processed_frame, (int(marker_x), int(marker_y)), 5, (0, 255, 0), -1)
                    
                    # Draw coordinates
                    text = f"ID:{marker_id[0]} ({robot_x:.1f},{robot_y:.1f})"
                    cv2.putText(processed_frame, text, (int(marker_x-50), int(marker_y-20)), 
                               cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
                    
                    # Emit coordinates for robot
                    self.aruco_detected.emit(robot_x, robot_y)
                    self.status_signal.emit(f"ArUco {marker_id[0]} detected at ({robot_x:.1f}, {robot_y:.1f})")
        
        else:
            # Basic edge detection when not in ArUco mode
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            edges = cv2.Canny(gray, 50, 150)
            edges_bgr = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)
            processed_frame = cv2.hconcat([frame, edges_bgr])
        
        return processed_frame
    
    def disconnect(self):
        self.running = False
        if self.cap:
            self.cap.release()
            self.status_signal.emit("Camera disconnected")

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.robot_thread = RobotThread()
        self.camera_thread = CameraThread()
        self.init_ui()
        self.connect_signals()
        
    def init_ui(self):
        self.setWindowTitle("Delta Robot & Camera Controller")
        self.setGeometry(100, 100, 1200, 800)
        
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Main layout
        main_layout = QHBoxLayout(central_widget)
        
        # Left panel - Camera
        camera_group = QGroupBox("Camera")
        camera_layout = QVBoxLayout(camera_group)
        
        self.camera_label = QLabel("No camera feed")
        self.camera_label.setMinimumSize(640, 480)
        self.camera_label.setStyleSheet("border: 1px solid gray")
        self.camera_label.setAlignment(Qt.AlignCenter)
        camera_layout.addWidget(self.camera_label)
        
        camera_controls = QHBoxLayout()
        self.connect_camera_btn = QPushButton("Connect Camera")
        self.start_camera_btn = QPushButton("Start")
        self.stop_camera_btn = QPushButton("Stop")
        
        camera_controls.addWidget(self.connect_camera_btn)
        camera_controls.addWidget(self.start_camera_btn)
        camera_controls.addWidget(self.stop_camera_btn)
        camera_layout.addLayout(camera_controls)
        
        # ArUco controls
        aruco_controls = QHBoxLayout()
        self.aruco_checkbox = QCheckBox("ArUco Detection")
        self.aruco_mode_checkbox = QCheckBox("Robot ArUco Mode")
        
        aruco_controls.addWidget(self.aruco_checkbox)
        aruco_controls.addWidget(self.aruco_mode_checkbox)
        camera_layout.addLayout(aruco_controls)
        
        # Right panel - Robot
        robot_group = QGroupBox("Robot Control")
        robot_layout = QVBoxLayout(robot_group)
        
        robot_controls = QHBoxLayout()
        self.connect_robot_btn = QPushButton("Connect Robot")
        self.start_robot_btn = QPushButton("Start Program")
        self.pause_robot_btn = QPushButton("Pause")
        self.stop_robot_btn = QPushButton("Stop")
        
        robot_controls.addWidget(self.connect_robot_btn)
        robot_controls.addWidget(self.start_robot_btn)
        robot_controls.addWidget(self.pause_robot_btn)
        robot_controls.addWidget(self.stop_robot_btn)
        robot_layout.addLayout(robot_controls)
        
        # Status displays
        self.robot_status = QTextEdit()
        self.robot_status.setMaximumHeight(200)
        self.robot_status.setReadOnly(True)
        robot_layout.addWidget(QLabel("Robot Status:"))
        robot_layout.addWidget(self.robot_status)
        
        self.camera_status = QTextEdit()
        self.camera_status.setMaximumHeight(100)
        self.camera_status.setReadOnly(True)
        camera_layout.addWidget(QLabel("Camera Status:"))
        camera_layout.addWidget(self.camera_status)
        
        # Add to main layout
        main_layout.addWidget(camera_group, 2)
        main_layout.addWidget(robot_group, 1)
        
        # Initial button states
        self.start_camera_btn.setEnabled(False)
        self.stop_camera_btn.setEnabled(False)
        self.start_robot_btn.setEnabled(False)
        self.pause_robot_btn.setEnabled(False)
        self.stop_robot_btn.setEnabled(False)
        
        # Initial status messages
        self.camera_status.append("Ready to connect camera")
        self.robot_status.append("Ready to connect robot")
        self.robot_status.append("Instructions:")
        self.robot_status.append("1. Connect camera and robot")
        self.robot_status.append("2. Enable 'ArUco Detection' to see markers")
        self.robot_status.append("3. Enable 'Robot ArUco Mode' for pick & place")
        self.robot_status.append("4. Start robot program - it will wait for ArUco targets")
        self.robot_status.append("")
        self.robot_status.append("Note: If ArUco fails, run test_aruco.py first")
        
    def connect_signals(self):
        # Camera signals
        self.connect_camera_btn.clicked.connect(self.connect_camera)
        self.start_camera_btn.clicked.connect(self.start_camera)
        self.stop_camera_btn.clicked.connect(self.stop_camera)
        self.camera_thread.frame_signal.connect(self.update_camera_frame)
        self.camera_thread.status_signal.connect(self.update_camera_status)
        
        # ArUco signals
        self.aruco_checkbox.toggled.connect(self.toggle_aruco_detection)
        self.aruco_mode_checkbox.toggled.connect(self.toggle_aruco_mode)
        self.camera_thread.aruco_detected.connect(self.robot_thread.set_aruco_target)
        
        # Robot signals
        self.connect_robot_btn.clicked.connect(self.connect_robot)
        self.start_robot_btn.clicked.connect(self.start_robot)
        self.pause_robot_btn.clicked.connect(self.pause_robot)
        self.stop_robot_btn.clicked.connect(self.stop_robot)
        self.robot_thread.status_signal.connect(self.update_robot_status)
    
    def connect_camera(self):
        if self.camera_thread.connect_camera():
            self.connect_camera_btn.setEnabled(False)
            self.start_camera_btn.setEnabled(True)
    
    def start_camera(self):
        self.camera_thread.start_capture()
        self.start_camera_btn.setEnabled(False)
        self.stop_camera_btn.setEnabled(True)
    
    def stop_camera(self):
        self.camera_thread.stop_capture()
        self.start_camera_btn.setEnabled(True)
        self.stop_camera_btn.setEnabled(False)
        
    def toggle_aruco_detection(self, checked):
        if not self.camera_thread.set_aruco_detection(checked):
            # If failed to enable, uncheck the checkbox
            self.aruco_checkbox.setChecked(False)
        
    def toggle_aruco_mode(self, checked):
        self.robot_thread.set_aruco_mode(checked)
    
    def connect_robot(self):
        if self.robot_thread.connect_robot():
            self.connect_robot_btn.setEnabled(False)
            self.start_robot_btn.setEnabled(True)
    
    def start_robot(self):
        self.robot_thread.start_program()
        self.start_robot_btn.setEnabled(False)
        self.pause_robot_btn.setEnabled(True)
        self.stop_robot_btn.setEnabled(True)
    
    def pause_robot(self):
        self.robot_thread.pause_program()
    
    def stop_robot(self):
        self.robot_thread.stop_program()
        self.start_robot_btn.setEnabled(True)
        self.pause_robot_btn.setEnabled(False)
        self.stop_robot_btn.setEnabled(False)
    
    def update_camera_frame(self, frame):
        height, width, channel = frame.shape
        bytes_per_line = 3 * width
        q_image = QImage(frame.data, width, height, bytes_per_line, QImage.Format_RGB888).rgbSwapped()
        pixmap = QPixmap.fromImage(q_image)
        scaled_pixmap = pixmap.scaled(self.camera_label.size(), Qt.KeepAspectRatio, Qt.SmoothTransformation)
        self.camera_label.setPixmap(scaled_pixmap)
    
    def update_camera_status(self, message):
        self.camera_status.append(f"{time.strftime('%H:%M:%S')} - {message}")
        self.camera_status.verticalScrollBar().setValue(self.camera_status.verticalScrollBar().maximum())
    
    def update_robot_status(self, message):
        self.robot_status.append(f"{time.strftime('%H:%M:%S')} - {message}")
        self.robot_status.verticalScrollBar().setValue(self.robot_status.verticalScrollBar().maximum())
    
    def closeEvent(self, event):
        self.camera_thread.disconnect()
        self.robot_thread.disconnect()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
