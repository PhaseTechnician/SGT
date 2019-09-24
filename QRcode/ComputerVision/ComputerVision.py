import cv2 
import numpy as np

def nothing1(x):
    min[2]=x;


def nothing2(x):
    mingray=x;


def mouseCallBack(event,x,y,flags,param):
    if event==cv2.EVENT_FLAG_LBUTTON:
         print(hsv[y,x])
    return

min=[0,0,0]
max=[180,180,255]
mingray=0

video = cv2.VideoCapture(0)
video.set(cv2.CAP_PROP_EXPOSURE, -20)
cv2.namedWindow("light")
cv2.namedWindow("gray")
cv2.createTrackbar("Vmin","light",0,255,nothing1)
cv2.createTrackbar("Gmin","gray",0,255,nothing2)
cv2.setMouseCallback("light",mouseCallBack)

while(True):
    ret,frame = video.read()
    if ret==True:
        #色彩空间转换
        hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
        gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        #通过灰度图划分图像
        maskgray=cv2.inRange(gray,min[2],255)
        gray = cv2.bitwise_and(frame,frame,mask = maskgray)
        cv2.imshow("gray",gray)
        #通过亮度划分图像
        masks = cv2.inRange(hsv,np.array(min,np.uint8),np.array(max,np.uint8))
        img = cv2.bitwise_and(frame,frame,mask = masks)
        cv2.imshow("light",img)
    cv2.waitKey(1)
cv2.destroyAllWindows()
