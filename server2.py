import socket;  
import threading;
import struct;
import cv2
import time
import os
import numpy as np
from PIL import Image

wid = 640
hig = 480
channels = 3

def recvall(sock, count):
        buf = b''
        while count:
            newbuf = sock.recv(count)
            if not newbuf: return None
            buf += newbuf
            count -= len(newbuf)
        return buf

if __name__ == '__main__':
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind(("localhost", 7999))
        server.listen(0)
        totleNum = wid * hig * channels;
        connection, address = server.accept()
        print(connection, address)
        while True:
            
            
            stringData = recvall(connection, int(totleNum))
 
            data = np.fromstring(stringData, dtype='uint8')
            print(len(data))
 
            Array = data.reshape(hig, wid, channels)
            im = Image.fromarray(Array)
            im.show("test")
            
            connection.send(bytes("clientRecv: ok", encoding="ascii"))
            time.sleep(1)
        connection.close()
            
        
