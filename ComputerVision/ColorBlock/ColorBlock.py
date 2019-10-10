import cv2
import numpy

lowerRed = numpy.array([35,50,100])
highRed = numpy.array([77,255,255])

lowerGreen = numpy.array([35,50,100])
highGreen = numpy.array([77,255,255])

lowerBlue = numpy.array([35,50,100])
highBlue = numpy.array([77,255,255])

kernl = numpy.ones((5,5),numpy.uint8)
minArea = 120

IndexCount=0
redIndex=-1
greenIndex=-1
blueIndex=-1

def whetherHaveColorBlock(frame,lowRage,highRage):
    maskR = cv2.inRange(hsv,lowerRed,highRed)
    maskR = cv2.morphologyEx(maskR,cv2.MORPH_OPEN,kernl)
    maskR,contours, hierarchy = cv2.findContours(maskR,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)#cv.RETR_TREE，cv.CHAIN_APPROX_SIMPLE
    index=0
    for countour in contours:
        if cv2.contourArea(countour) > minArea:
            return True
            #cv2.drawContours(frame, contours, index, (255,255,255), 3)
        index=index+1

def PeekGoods():
    cap = cv2.VideoCapture(0)
    if cap.isOpened() is True:
        while True:
            ret,frame = cap.read();
            hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
            if redIndex is -1 and whetherHaveColorBlock(frame,lowerRed,highRed) is True:
                redIndex=IndexCount
                IndexCount=IndexCount+1
            if  greenIndex is -1 and whetherHaveColorBlock(frame,lowerGreen,highGreen) == True:
                greenIndex=IndexCount
                IndexCount=IndexCount+1
            if  blueIndex is -1 and whetherHaveColorBlock(frame,lowerBlue,highBlue) == True:
                blueIndex=IndexCount
                IndexCount=IndexCount+1
            if IndexCount is 3:
                resultList[redIndex] = 'R'
                resultList[greenIndex] = 'G'
                resultList[blueIndex] = 'B'
                break
            cv2.waitKey(30);
        cap.close()
        return resultList
    else
        print("NO CAP OPEN")
        return "000"

PeekGoods()