import socket
from cv2 import threshold
import numpy as np
import time
from PIL import Image
import cv2 as cv
import cv2

import argparse
import imutils
import math
from collections import defaultdict
import argparse
from math import atan2, cos, sin, sqrt, pi
from sklearn.cluster import KMeans

from numpy import loadtxt
from numpy import savetxt

import matplotlib.pyplot as plt

import sys

import os

model0 = np.array([[  0,   0,   0,  12,  83, 141, 165, 170, 162, 143, 114,  60,   6,  0,   0,   0],
         [  0,   0,  76, 222, 254, 255, 255, 255, 255, 254, 249, 234, 169,  36,   0,   0],
         [  0,  77, 242, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 210,  37,   0],
         [ 18, 216, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 188,   5],
         [ 97, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 252,  69],
         [163, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 147],
         [189, 255, 255, 255, 254, 246, 254, 255, 255, 255, 245, 253, 255, 255, 255, 182],
         [177, 255, 255, 255, 252, 251, 255, 255, 255, 255, 229, 252, 255, 255, 255, 190],
         [112, 250, 255, 254, 255, 255, 255, 255, 255, 255, 230, 247, 255, 255, 255, 161],
         [ 47, 168, 214, 215, 240, 255, 255, 255, 255, 255, 236, 248, 254, 254, 227, 100],
         [ 11,  94, 121, 127, 190, 254, 255, 255, 255, 255, 230, 207, 190, 189, 149,  41],
         [  0,  28,  75,  74, 121, 239, 255, 255, 255, 253, 204, 116, 103, 105,  90,   8],
         [  0,   0,   1,   6,  73, 217, 255, 255, 255, 246, 181,  77,  81,  86,  37,   0],
         [  0,   1,   0,   0,  33, 173, 253, 255, 255, 238, 145,  41,  38,  29,   1,   0],
         [  0,   0,   0,   0,  17,  90, 192, 236, 254, 232, 124,   8,   0,   0,   0,   0],
         [  0,   4,   0,   0,   1,  27,  66,  70,  95, 109,  40,   0,   0,   0,   0,   0]])
model45 = np.array([[  0,   0,   8,  65, 144, 183, 179, 138,  78,  30,   2,   0,   0,   0,   0,   0],
         [  1,  37, 151, 243, 255, 255, 255, 254, 235, 170,  80,  15,   0,   0,   0,   0],
         [ 24, 147, 224, 255, 255, 255, 255, 255, 255, 252, 208, 104,  16,   0,   0,   0],
         [ 87, 167, 235, 255, 255, 255, 255, 255, 255, 255, 254, 226, 104,   5,   0,   0],
         [103, 163, 217, 250, 255, 255, 255, 255, 255, 255, 255, 255, 228,  75,   0,   0],
         [ 73, 136, 187, 226, 250, 253, 244, 255, 255, 255, 255, 255, 255, 214,  28,   0],
         [ 19,  86, 144, 237, 254, 245, 248, 253, 255, 255, 255, 255, 255, 255, 152,   1],
         [  9,  47, 172, 249, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 246,  40],
         [ 33,  86, 204, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 125],
         [ 48, 175, 237, 255, 255, 255, 255, 255, 255, 253, 254, 255, 255, 255, 255, 183],
         [ 36, 209, 246, 255, 255, 255, 255, 255, 244, 223, 240, 255, 255, 255, 255, 194],
         [ 20, 132, 225, 254, 255, 255, 255, 241, 218, 223, 248, 255, 255, 255, 255, 158],
         [  2,  92, 165, 225, 254, 241, 213, 214, 230, 241, 255, 255, 255, 255, 249,  74],
         [  4,  49,  97, 130, 143, 132,  90, 103, 201, 226, 253, 255, 255, 251, 169,   4],
         [  1,   4,  33,  46,  45,  31,   4,  44, 140, 205, 222, 237, 235, 162,  16,   0],
         [  0,   0,  11,   2,  16,   2,   0,   4,  43, 106, 140, 129,  62,   3,   0,   0]])

def generateModel(model0, model45):
    models = [model0, model45]
    models.append(np.rot90(model0, 3))
    models.append(np.rot90(model45, 3))
    models.append(np.rot90(model0, 2))
    models.append(np.rot90(model45, 2))
    models.append(np.rot90(model0))
    models.append(np.rot90(model45))

    return models

models = generateModel(model0, model45)

HOST = '192.168.101.135'  # The server's hostname or IP address
PORT = 8844        # The port used by the server

ImageSourceType = "FilterImage"

objectWidth = 50
objectHeight = 50
sizeError = 0.5

if (len(sys.argv) > 4):
    for i in range(1, len(sys.argv) - 1):
        if sys.argv[i] == '-ip':
            HOST = sys.argv[i + 1]
        if sys.argv[i] == '-port':
            PORT = int(sys.argv[i + 1])
        if sys.argv[i] == '-type':
            ImageSourceType = sys.argv[i + 1]
        if sys.argv[i] == '-ow':
            objectWidth = int(sys.argv[i + 1])
        if sys.argv[i] == '-oh':
            objectHeight = int(sys.argv[i + 1])
        if sys.argv[i] == '-err':
            sizeError = float(sys.argv[i + 1])

print(HOST)
print(PORT)

try:
    softwareSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    softwareSocket.connect((HOST, PORT))

    print("Connected " + HOST)
except socket.timeout:
    print("Fail connection")
    exit

print("wait data")

def saveArr(file, arr):
    savetxt(file, arr, delimiter = ",")

def loadArr(file):
    data = loadtxt(file, delimiter =",")
    return data

def resize(image):
    # read image to be resized by imread() function of openCV library
    img = cv2.imread(image)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    thresh = cv2.threshold(blurred, 75, 255, cv2.THRESH_BINARY)[1]

    # set the ratio of resized image
    width = 16
    height = 16

    # resize the image by resize() function of openCV library
    scaled = cv2.resize(thresh, (width, height), interpolation=cv2.INTER_AREA)

    #cv2.imshow("Output", scaled)
    #cv2.waitKey(500)
    #cv2.destroyAllWindows()
    #cv2.imwrite("sample/"+str(i)+"-r.jpeg", scaled)
    return scaled
    # show the resized image using imshow() function of openCV library



data = []
predicts = []

# def generateModel():
#     data = []
#     for j in range(8):
#         sample = resize("sample/"+str(j)+".jpeg")
#         saveArr("model/model-"+str(j)+".csv", sample)
# print("load model")

# def loadModel():
#     # try:
#     data = []
#     for j in range(8):

#         p = os.path.dirname(os.path.realpath(__file__)) +  "\model\model-"+str(j)+".csv"
#         # print(p)
#         data.append(loadArr(p))
#         # print("load model " + str(j))
#     return data
#     # except Exception as e:
#     #     print(e)

print("detect")

def detect(image, test = False):
    image_np = image.astype(np.int32)
    min = 1000000
    ori = 0
    for j in range(8):
        sam = models[j]

        dist = np.linalg.norm(sam - image_np)

        if dist < min:
            min = dist
            ori = j*1.5

        if (test):
            data.append(sam - image_np)
            predicts.append(dist)        

    #print(ori)
    return ori

def GetAngle(value):
    return value * 30
print("load model function")
# models = loadModel()
print("process")
def processSape(image):
    if (ImageSourceType == "OriginImage" or image.shape[2] == 3):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)       
        thresh = cv2.threshold(gray, 100, 255, cv2.THRESH_BINARY)[1]        
        thresh = cv2.GaussianBlur(thresh, (5, 5), 0) 
    else:
        thresh = image.copy()

    image = cv2.threshold(image, 255, 255, cv2.THRESH_BINARY)[1]     
    
    # find contours in the thresholded image
    cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    

    cnts = imutils.grab_contours(cnts)

    line = "#Object = "
    
    # loop over the contours
    for c in cnts:
         
        bounding_rect = cv2.minAreaRect(c)

        isCorrectBlob = False

        if objectWidth != 0 and objectHeight != 0:
            if (objectHeight * (1 + sizeError) - bounding_rect[1][1]) < objectHeight * sizeError * 2:
                if (objectWidth * (1 + sizeError) - bounding_rect[1][0]) < objectWidth * sizeError * 2:
                    isCorrectBlob = True
        else:
            isCorrectBlob = True

        if isCorrectBlob == False:
            continue


        x, y, w, h = cv2.boundingRect(c)

        roi = thresh[y:y+h, x:x+w]

        scaled = cv2.resize(roi, (16, 16), interpolation=cv2.INTER_AREA)
        predict = detect(scaled)
        angle = GetAngle(predict)

        # if angle > 180:
            # angle = angle - 360
        
        # cv2.imshow("fdf", roi)
        # cv2.waitKey(0)


        ow = 50
        oh = 100

        if objectWidth != 0 and objectHeight != 0:
            ow = objectWidth
            oh = objectHeight

        cX = x + w/2
        cY = y + h/2

        if y == 0 or y + h >= thresh.shape[0]:
            continue

        line += str('0,') + str(cX) + ',' + str(cY)  + ',' + str(ow) + ',' + str(oh) + ',' + str(angle)  + ";"
        # print(cX)
        image = cv2.putText(image, str(angle), (int(cX), int(cY)), cv2.FONT_HERSHEY_COMPLEX, 1.0, (255,0,0), 2, cv2.LINE_AA)
                
            
    line += "\n"
    

    try:
        softwareSocket.sendall(line.encode())
    except socket.timeout:
        return
        
    cv2.imshow("Image", image)
    cv2.waitKey(1)

    return image
    # show the image
    # rzimg = cv2.resize(image, (640, 480))



def recvall(sock, count):
    buf = b''
    while count:
        newbuf = sock.recv(count)
        if not newbuf: return None
        buf += newbuf
        count -= len(newbuf)
    return buf


softwareSocket.sendall(b'ExternalScript\n')

# pass b'deltax'
hello = str(softwareSocket.recv(4096))


imgOrder = 0

start = time.time()

print("before while")

while True:

    try:
        wid = softwareSocket.recv(4)[::-1]
        hig = softwareSocket.recv(4)[::-1]
        channels = softwareSocket.recv(4)[::-1]
        wid = int.from_bytes(wid, "big")
        hig = int.from_bytes(hig, "big")
        channels = int.from_bytes(channels, "big")

        totalNum = wid * hig * channels

        print("receive size")

        stringData = recvall(softwareSocket, int(totalNum))
        # with open("test.bin", "wb") as f:
        #     f.write(stringData)

        print("receive image data")

        data = np.frombuffer(stringData, dtype='uint8')
        #print(len(data))

        mat = data.reshape(hig, wid, channels)
        #im = Image.fromarray(Array)

        # imgOrder = imgOrder + 1
        # print(imgOrder)

        start = time.time()
        image = processSape(mat)
        print(time.time() - start)

        # rzimg = cv2.resize(image, (600, 400))
        cv2.imshow("Image", mat)
        cv2.waitKey(1)

        
    except socket.timeout:
        print("time out")
        exit