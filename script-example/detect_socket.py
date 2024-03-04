import socket
import numpy as np
import time
import cv2

HOST = '127.0.0.1'
PORT = 8844

Software_Socket = None

def ConnectToSoftware(host, port):
    global Software_Socket

    HOST = host
    PORT = port
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
    Software_Socket.sendall(b'ClientName=ImageClient\n')

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

        print("w: {0} h: {1} c: {2}", wid, hig, channels)

        stringData = Recv_All(Software_Socket, int(totalNum))

        data = np.frombuffer(stringData, dtype='uint8')

        mat = data.reshape(hig, wid, channels)

        return mat
    except:
        pass

def Get_Image2():
    data = b''
    while True:
        # print('reading data')
        packet = Software_Socket.recv(4096)
        if not packet: break
        data += packet
        if len(packet) < 4096: break

    if data:
        print('Received data')
        
        if data.startswith(b'Image\n'):
            try:
                print('Received image')
                image_data = data[6:]
                nparr = np.frombuffer(image_data, np.uint8)
                img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                return img
            except Exception as e:
                print('Error receiving image:', e)
        else:
            print(data)

def find_circles(img):
    img_copy = np.copy(img)
    gray = cv2.cvtColor(img_copy, cv2.COLOR_BGR2GRAY)
    # edges = cv2.Canny(gray, 207, 255)
    # Giảm nhiễu
    edges = cv2.blur(gray, (3, 3))

    circles = cv2.HoughCircles(edges, cv2.HOUGH_GRADIENT, dp=1, minDist=30, param1=100, param2=17, minRadius=9, maxRadius=13)

    if circles is not None:
        circles = np.round(circles[0, :]).astype("int")
        return circles[:, :2]
    else:
        _circles = []
        return _circles

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
            ConnectToSoftware("192.168.1.8", 8844)
            while True:
                try:
                    image = Get_Image()
                    # get_objects(image)
                    cv2.imshow("Image", image)
                    cv2.waitKey(1)
                except:
                    break
        except socket.timeout:
            print("time out")
            time.sleep(2)

def main():
    Loop_Event()

if __name__ == "__main__":
    main()
