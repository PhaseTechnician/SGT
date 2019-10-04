import cv2
import numpy

cap = cv2.VideoCapture(0)

lowerRed = numpy.array([35,50,100])
highRed = numpy.array([77,255,255])

lowerGreen = numpy.array([35,50,100])
highGreen = numpy.array([77,255,255])

lowerBlue = numpy.array([35,50,100])
highBlue = numpy.array([77,255,255])

kernl = numpy.ones((5,5),numpy.uint8)

if cap.isOpened() is True:
    while True:
        ret,frame = cap.read();
        hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
        maskR = cv2.inRange(hsv,lowerRed,highRed)
        maskG = cv2.inRange(hsv,lowerGreen,highGreen)
        maskB = cv2.inRange(hsv,lowerBlue,highBlue)
        #openmask = cv2.morphologyEx(mask,cv2.MORPH_OPEN,kernl)
        #closemask = cv2.morphologyEx(openmask,cv2.MORPH_CLOSE,kernl)
        #bila = cv2.bilateralFilter(mask,10,200,200)
        #edges = cv2.Canny(openmask,50,100)
        cv2.imshow("R",maskR)
        cv2.imshow("G",maskG)
        cv2.imshow("B",maskB)
        cv2.waitKey(30);