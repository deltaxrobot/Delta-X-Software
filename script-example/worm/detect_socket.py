import socket
import numpy as np
import time
import cv2

HOST = '127.0.0.1'
PORT = 8844

Software_Socket = None

def ConnectToSoftware(host, port):
    global Software_Socket

    if Software_Socket == None or Software_Socket.fileno() < 0:
        try:
            Software_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            Software_Socket.connect((HOST, PORT))

            print("Connected " + HOST)
            Send_Init_Message()

            return True
        except socket.timeout:
            print("Fail connection")
            return False
    
    return True

def Recv_All(sock, count):
    buf = b''
    while count:
        newbuf = sock.recv(count)
        if not newbuf: return None
        buf += newbuf
        count -= len(newbuf)
    return buf

def Send_Init_Message():
    Software_Socket.sendall(b'ExternalScript\n')

    # pass b'deltax'
    deltax_mess = str(Software_Socket.recv(4096))

def Get_Data_Size():
    wid = Software_Socket.recv(4)[::-1]
    hig = Software_Socket.recv(4)[::-1]
    channels = Software_Socket.recv(4)[::-1]
    wid = int.from_bytes(wid, "big")
    hig = int.from_bytes(hig, "big")
    channels = int.from_bytes(channels, "big")

    totalNum = wid * hig * channels

    return wid, hig, channels, totalNum

def Get_Image():
    wid, hig, channels, totalNum = Get_Data_Size()

    stringData = Recv_All(Software_Socket, int(totalNum))

    data = np.frombuffer(stringData, dtype='uint8')

    mat = data.reshape(hig, wid, channels)

    return mat

def Loop_Event():
    while True:
        try:
            image = Get_Image()
            cv2.imshow("Image", image)
            cv2.waitKey(1)
            
        except socket.timeout:
            print("time out")
            ConnectToSoftware(HOST, PORT)
            time.sleep(2)

def main():
    ConnectToSoftware("192.168.101.135", 8844)
    Loop_Event()

if __name__ == "__main__":
    main()
