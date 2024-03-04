'''
    >> label:0 x:100 Y:250 w:50 h:30 angle:135
'''


import cv2
import sys
import detect_socket
import time
from ultralytics import YOLO

def get_objects(image):
    # Run YOLOv8 inference on the frame
    results = model(image)

    resultString = "#Blobs = "

    img_height, img_width, _ = image.shape

    # View results
    for r in results:
        for box in r.boxes.xywhn:
            id = 0
            x = int(box[0] * img_width)
            y = int(box[1] * img_height)
            w = int(box[2] * img_width)
            h = int(box[3] * img_height)
            angle = 0

            resultString += str(int(id)) + ',' + str(x) + ',' + str(y)  + ',' + str(w) + ',' + str(h) + ',' + str(angle)  + ";"
       
    # Visualize the results on the frame
    annotated_frame = results[0].plot()

    # Display the annotated frame
    cv2.imshow("YOLOv8 Inference", annotated_frame)

    return resultString

# Load the YOLOv8 model
model = YOLO('yolov8n.pt')

def main():
    HOST = "192.168.1.8"
    PORT = 8844

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