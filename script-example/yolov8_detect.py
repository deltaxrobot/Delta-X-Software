import cv2
import sys
import detect_socket
import time
import argparse
from ultralytics import YOLO

def check_opencv_gui_support():
    """Check if OpenCV has GUI support"""
    try:
        # Try to create a dummy window
        cv2.namedWindow("test", cv2.WINDOW_NORMAL)
        cv2.destroyWindow("test")
        return True
    except cv2.error:
        return False

def get_objects(image, headless=False):
    # Run YOLOv8 inference on the frame
    results = model(image)

    resultString = "#Blobs = "

    img_height, img_width, _ = image.shape

    # View results
    for r in results:
        for box in r.boxes.xywhn:
            id = int(r.boxes.cls[0])
            x = int(box[0] * img_width)
            y = int(box[1] * img_height)
            w = int(box[2] * img_width)
            h = int(box[3] * img_height)
            angle = 0

            resultString += str(id) + ',' + str(x) + ',' + str(y)  + ',' + str(w) + ',' + str(h) + ',' + str(angle)  + ";"
       
    # Visualize the results on the frame
    annotated_frame = results[0].plot()

    # Display the annotated frame (only if GUI is available and not headless)
    if not headless:
        try:
            cv2.imshow("YOLOv8 Inference", annotated_frame)
        except cv2.error as e:
            print(f"GUI not available: {e}")
            pass

    return resultString


    # Load the YOLOv8 model
model = None

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="YOLOv8 Inference Script")
    parser.add_argument("--host", type=str, default="192.168.56.1", help="IP address of the server")
    parser.add_argument("--port", type=int, default=8844, help="Port number of the server")
    parser.add_argument("--model-path", type=str, default='yolov8n.pt', help="Path to the YOLOv8 model file")
    parser.add_argument("--headless", action="store_true", help="Run without GUI display")

    args = parser.parse_args()

    HOST = args.host
    PORT = args.port
    MODEL_PATH = args.model_path
    HEADLESS = args.headless

    global model

    model = YOLO(MODEL_PATH)
    
    # Check OpenCV GUI support
    gui_available = check_opencv_gui_support()
    if not gui_available and not HEADLESS:
        print("Warning: OpenCV GUI not available. Running in headless mode.")
        HEADLESS = True
    elif gui_available and not HEADLESS:
        print("OpenCV GUI support detected. Display windows will be shown.")
    else:
        print("Running in headless mode (no display windows).")

    while True:
        try:
            detect_socket.ConnectToSoftware(HOST, PORT)
            while True:
                try:
                    image = detect_socket.Get_Image2()
                    result = get_objects(image, HEADLESS)
                    print(result)

                    detect_socket.Software_Socket.sendall(result.encode())

                    # Display original image (only if GUI is available and not headless)
                    if not HEADLESS:
                        try:
                            # cv2.imshow("Image", image)
                            cv2.waitKey(1)
                        except cv2.error as e:
                            print(f"GUI not available for original image: {e}")
                            pass
                except Exception as e:
                    print('Error receiving image:', e)
                    break
                
        except ConnectionRefusedError:
            # Không kết nối được đến server, đợi 5 giây và thử kết nối lại
            print(f"Connection refused. Retrying in 5 seconds...")
            time.sleep(5)

if __name__ == "__main__":
    main()