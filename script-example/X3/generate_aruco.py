import cv2
import cv2.aruco as aruco
import numpy as np

# Create ArUco dictionary (compatible with OpenCV 4.x)
try:
    # OpenCV 4.7+
    aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
    print("Using OpenCV 4.7+ ArUco API")
except AttributeError:
    try:
        # OpenCV 4.0-4.6
        aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
        print("Using OpenCV 4.0-4.6 ArUco API")
    except AttributeError:
        # Fallback
        aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_4X4_50)
        print("Using fallback ArUco API")

# Generate markers
for marker_id in range(5):
    # Create marker image (200x200 pixels)
    try:
        # Try newest method first
        marker_img = aruco.generateImageMarker(aruco_dict, marker_id, 200)
    except AttributeError:
        try:
            # Try alternative method
            marker_img = cv2.aruco.generateImageMarker(aruco_dict, marker_id, 200)
        except AttributeError:
            # Fallback to older method
            marker_img = aruco.drawMarker(aruco_dict, marker_id, 200)
    
    # Save marker
    filename = f"aruco_marker_{marker_id}.png"
    cv2.imwrite(filename, marker_img)
    print(f"Generated: {filename}")

print("\nArUco markers generated!")
print("Print these images and place them in front of the camera")
print("The robot will automatically pick & place when detected") 