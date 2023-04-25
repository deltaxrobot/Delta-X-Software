import socket
import numpy as np
import time
import cv2

HOST = '127.0.0.1'
PORT = 8844

Software_Socket = None

def ConnectToSoftware(host, port):
    global Software_Socket

    # if Software_Socket == None or Software_Socket.fileno() < 0:
    try:
        Software_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        Software_Socket.connect((HOST, PORT))

        print("Connected " + HOST)
        Send_Init_Message()
        # pass b'deltax'
        hello = str(Software_Socket.recv(4096))

        print(hello)

        return True
    except socket.timeout:
        print("Fail connection")
        return False
    
    return True

def Recv_All(sock, count):
    try:
        # print('count ' + str(count))
        buf = b''
        while count:
            newbuf = sock.recv(count)
            if not newbuf: return None
            buf += newbuf
            count -= len(newbuf)
        return buf
    except:
        pass

def Send_Init_Message():
    Software_Socket.sendall(b'ExternalScript\n')

    # pass b'deltax'
    # deltax_mess = str(Software_Socket.recv(4096))

def Get_Data_Size():
    try:
        wid = Software_Socket.recv(4)[::-1]
        hig = Software_Socket.recv(4)[::-1]
        channels = Software_Socket.recv(4)[::-1]
        wid = int.from_bytes(wid, "big")
        hig = int.from_bytes(hig, "big")
        channels = int.from_bytes(channels, "big")

        totalNum = wid * hig * channels

        # print("w: {0} h: {1} c: {2}", wid, hig, channels)

        return wid, hig, channels, totalNum
    except:
        pass

def Get_Image():
    try:
        wid, hig, channels, totalNum = Get_Data_Size()

        stringData = Recv_All(Software_Socket, int(totalNum))

        data = np.frombuffer(stringData, dtype='uint8')

        mat = data.reshape(hig, wid, channels)

        return mat
    except:
        pass

def find_circles(img):
    img_copy = np.copy(img)

    img_copy = cv2.medianBlur(img_copy, 17)
    _hsv = cv2.cvtColor(img_copy, cv2.COLOR_RGB2HSV)
    
    _lower_blue = np.array(15, 16, 0)
    _upper_blue = np.array(97, 255, 255)

    # preparing the mask to overlay
    mask = cv2.inRange(_hsv, _lower_blue, _upper_blue)

    # The black region in the mask has the value of 0,
    # so when multiplied with original image removes all non-blue regions
    _result = cv2.bitwise_and(img_copy, img_copy, mask = mask)

    retval2, threshold2 = cv2.threshold(cv2.cvtColor(_result, cv2.COLOR_RGB2GRAY), 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    # detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    contours, hierarchy = cv2.findContours(image=threshold2, mode=cv2.RETR_EXTERNAL, method=cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(image=img, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2, lineType=cv2.LINE_AA)

    centers = []

    for _contour in contours:
        rect = cv2.minAreaRect(_contour)
        box = cv2.boxPoints(rect)
        box = np.intp(box)
        cv2.drawContours(img,[box],0,(0,0,255),2)
        
        (_x, _y),(_w, _h),_r = rect

        center_x = (box[0][0] + box[2][0]) / 2
        center_y = (box[0][1] + box[2][1]) / 2

        if _w < 20 and _h < 20:
            continue
        elif _w > 260 or _h > 260:
            cv2.putText(img, 'tree', (center_x, center_y), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2, cv2.LINE_AA)
            cv2.circle(img,(int(center_x), int(center_y)),5,(255,0,0),5)
        else:
            cv2.putText(img, 'grass', (center_x, center_y), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2, cv2.LINE_AA)
            cv2.circle(img,(int(center_x), int(center_y)),5,(255,0,0),5)

            centers.append((int(center_x), int(center_y)))

    cv2.imshow('image', img)
    cv2.waitKey(1)
    return centers

def get_objects(image):

    circles = find_circles(image)

    line = "#Object = "
    
    # loop over the contours
    for (x, y) in circles:
        line += str('0,') + str(x) + ',' + str(y)  + ',' + str(10) + ',' + str(10) + ',' + str(0)  + ";"
        # print(cX)
        cv2.circle(image, (x, y), 5, (0, 255, 0), -1)
                
            
    line += "\n"
    

    try:
        Software_Socket.sendall(line.encode())
    except socket.timeout:
        return
        
    cv2.imshow("Image", image)
    cv2.waitKey(1)

    return image        

def Loop_Event():
    while True:  
        try:      
            ConnectToSoftware("127.0.0.1", 8844)
            while True:
                try:
                    image = Get_Image()
                    #get_objects(image)
                    cv2.imshow("Image", image)
                    cv2.waitKey(1)
                except:
                    break
        except Exception as e:
            # In ra lỗi
            print(e)
            traceback.print_exc()
            time.sleep(2)

def main():
    Loop_Event()

if __name__ == "__main__":
    main()
