import cv2
import sys
import detect_socket
import time
import argparse
from ultralytics import YOLO

def get_objects(image):
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

    # Display the annotated frame
    cv2.imshow("YOLOv8 Inference", annotated_frame)

    return resultString


    # Load the YOLOv8 model
model = None

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="YOLOv8 Inference Script")
    parser.add_argument("--host", type=str, default="172.16.0.2", help="IP address of the server")
    parser.add_argument("--port", type=int, default=8844, help="Port number of the server")
    parser.add_argument("--model-path", type=str, default='yolov8n.pt', help="Path to the YOLOv8 model file")

    args = parser.parse_args()

    HOST = args.host
    PORT = args.port
    MODEL_PATH = args.model_path

    global model

    model = YOLO(MODEL_PATH)

    while True:
        try:
            detect_socket.ConnectToSoftware(HOST, PORT)
            while True:
                try:
                    image = detect_socket.Get_Image2()
                    result = get_objects(image)
                    print(result)

                    detect_socket.Software_Socket.sendall(result.encode())

                    # cv2.imshow("Image", image)
                    cv2.waitKey(1)
                except Exception as e:
                    print('Error receiving image:', e)
                    break
                
        except ConnectionRefusedError:
            # Không kết nối được đến server, đợi 5 giây và thử kết nối lại
            print(f"Connection refused. Retrying in 5 seconds...")
            time.sleep(5)

if __name__ == "__main__":
    main()