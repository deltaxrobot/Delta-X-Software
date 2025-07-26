import cv2
import cv2.aruco as aruco
import numpy as np

def test_aruco_api():
    """Test ArUco API compatibility"""
    print("Testing ArUco API compatibility...")
    
    # Test dictionary creation
    try:
        # OpenCV 4.7+
        aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
        aruco_params = aruco.DetectorParameters()
        print("✓ OpenCV 4.7+ ArUco API - OK")
        api_version = "4.7+"
    except AttributeError:
        try:
            # OpenCV 4.0-4.6
            aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
            aruco_params = aruco.DetectorParameters_create()
            print("✓ OpenCV 4.0-4.6 ArUco API - OK")
            api_version = "4.0-4.6"
        except AttributeError:
            try:
                # Fallback
                aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_4X4_50)
                aruco_params = cv2.aruco.DetectorParameters_create()
                print("✓ Fallback ArUco API - OK")
                api_version = "fallback"
            except Exception as e:
                print(f"✗ ArUco API test failed: {e}")
                return False
    
    # Test marker generation
    try:
        # Try different marker generation methods
        try:
            marker_img = aruco.generateImageMarker(aruco_dict, 0, 200)
        except AttributeError:
            try:
                marker_img = cv2.aruco.generateImageMarker(aruco_dict, 0, 200)
            except AttributeError:
                marker_img = aruco.drawMarker(aruco_dict, 0, 200)
        print("✓ Marker generation - OK")
    except Exception as e:
        print(f"✗ Marker generation failed: {e}")
        return False
    
    # Test marker detection on generated image
    try:
        if api_version == "4.7+":
            detector = aruco.ArucoDetector(aruco_dict, aruco_params)
            corners, ids, rejected = detector.detectMarkers(marker_img)
        else:
            corners, ids, rejected = aruco.detectMarkers(marker_img, aruco_dict, parameters=aruco_params)
        
        if ids is not None and len(ids) > 0:
            print("✓ Marker detection - OK")
        else:
            print("✗ Marker detection - No markers detected")
            return False
    except Exception as e:
        print(f"✗ Marker detection failed: {e}")
        return False
    
    print("\n✓ All ArUco tests passed! The main program should work correctly.")
    return True

def test_camera():
    """Test camera access"""
    print("\nTesting camera access...")
    
    try:
        cap = cv2.VideoCapture(0)
        if cap.isOpened():
            ret, frame = cap.read()
            if ret:
                print("✓ Camera access - OK")
                print(f"  Frame size: {frame.shape}")
                cap.release()
                return True
            else:
                print("✗ Camera access - Can't read frame")
                cap.release()
                return False
        else:
            print("✗ Camera access - Can't open camera")
            return False
    except Exception as e:
        print(f"✗ Camera access failed: {e}")
        return False

if __name__ == "__main__":
    print("ArUco System Test")
    print("=" * 30)
    
    # Test OpenCV version
    print(f"OpenCV version: {cv2.__version__}")
    
    # Test ArUco API
    aruco_ok = test_aruco_api()
    
    # Test camera
    camera_ok = test_camera()
    
    print("\n" + "=" * 30)
    if aruco_ok and camera_ok:
        print("✓ All tests passed! Ready to run the main program.")
        print("\nNext steps:")
        print("1. Run: python generate_aruco.py")
        print("2. Print the generated ArUco markers")
        print("3. Run: python thread-cam.py")
    else:
        print("✗ Some tests failed. Please check your OpenCV installation.")
        if not aruco_ok:
            print("  - Try: pip install opencv-contrib-python")
        if not camera_ok:
            print("  - Check camera connection and permissions") 