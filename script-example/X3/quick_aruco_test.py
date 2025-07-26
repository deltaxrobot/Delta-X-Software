import cv2
import cv2.aruco as aruco

def quick_aruco_test():
    """Quick ArUco compatibility test"""
    print("Quick ArUco Test...")
    print(f"OpenCV version: {cv2.__version__}")
    
    # Test different APIs
    success = False
    
    # Try OpenCV 4.7+
    try:
        aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
        aruco_params = aruco.DetectorParameters()
        detector = aruco.ArucoDetector(aruco_dict, aruco_params)
        print("✓ OpenCV 4.7+ API works")
        success = True
    except:
        print("✗ OpenCV 4.7+ API failed")
    
    # Try OpenCV 4.0-4.6
    if not success:
        try:
            aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
            aruco_params = aruco.DetectorParameters_create()
            print("✓ OpenCV 4.0-4.6 API works")
            success = True
        except:
            print("✗ OpenCV 4.0-4.6 API failed")
    
    # Try fallback
    if not success:
        try:
            aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_4X4_50)
            aruco_params = cv2.aruco.DetectorParameters_create()
            print("✓ Fallback API works")
            success = True
        except:
            print("✗ Fallback API failed")
    
    if success:
        print("\n✓ ArUco should work in main program")
    else:
        print("\n✗ ArUco will NOT work - check OpenCV installation")
        print("Try: pip install opencv-contrib-python")
    
    return success

if __name__ == "__main__":
    quick_aruco_test() 