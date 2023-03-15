# import AIX

# mat = cv2.imread('img.jpg')
# objs = AIX.detect(mat)

# for obj in obj:
#     print("label:{0} x:{1} y:{2} w:{3} h:{4} angle:{5}".format(obj[0], obj[1], obj[2], ojb[3], ojb[4], ojb[5]))

'''
    >> label:0 x:100 Y:250 w:50 h:30 angle:135
'''


import cv2
from yoro import api
import sys
import yoro
import detect_socket
import time

class Detect():
    def __init__(self,modelPath):
        #load model
        devType = api.DeviceType.CUDA
        self.detector = api.YORODetector(modelPath, devType)
        
        self.output = []
        self.img = None
    def run(self,image: cv2.Mat):

        def getDegreeDetectron2Type(degree):
            if (degree >=-180 and degree <= 90):
                degree = 90 + degree
                return degree
            else:
                degree = -(270 - degree)
                return degree       

        outString = "#Object = "

        # Run detector
        pred = self.detector.detect(image, 0.95, 0.9)

        # convert output to list
        self.output = []
        out = None

        for inst in pred:

            # degree = getDegreeDetectron2Type(inst.degree)
            degree = inst.degree            

            outString  += str(inst.label)
            outString  += ", " + str(int(inst.x))
            outString  += ", " + str(int(inst.y))
            outString  += ", " + str(int(inst.w))
            outString  += ", " + str(int(inst.h))
            outString  += ", " + str(int(degree)) +";"
        
        outString += "\n"

        return outString


def main():
    HOST = "192.168.101.135"
    PORT = 8844

    modelPath  =  r"/mnt/d/Tanworking/newBugAIX - Dataset in Lab/FakeMushroom-output/FakeMushroom-Resize_iter_3100_best.zip"
    # modelPath  =  r"/mnt/d/Tanworking/newBugAIX - Dataset in Lab/wood output/wood 1_iter_3000.zip"
    
    detect = Detect(modelPath)

    while True:
        try:
            detect_socket.ConnectToSoftware(HOST, PORT)
            while True:
                try:
                    image = detect_socket.Get_Image()
                    mess = detect.run(image)
                    # print(mess)

                    detect_socket.Software_Socket.sendall(mess.encode())
                except:
                    break
                # cv2.imshow("Image", image)
                # cv2.waitKey(1)
        except ConnectionRefusedError:
            # Không kết nối được đến server, đợi 5 giây và thử kết nối lại
            print(f"Connection refused. Retrying in 5 seconds...")
            time.sleep(5)

if __name__ == "__main__":
    main()