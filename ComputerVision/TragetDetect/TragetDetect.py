import cv2
import numpy

cap = cv2.VideoCapture(0)
lowerGreen = numpy.array([35,50,100])
highGreen = numpy.array([77,255,255])
kernl = numpy.ones((5,5),numpy.uint8)

if cap.isOpened() is True:
    while True:
        ret,frame = cap.read();
        #gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
        hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv,lowerGreen,highGreen)
        openmask = cv2.morphologyEx(mask,cv2.MORPH_OPEN,kernl)
        #closemask = cv2.morphologyEx(openmask,cv2.MORPH_CLOSE,kernl)
        bila = cv2.bilateralFilter(mask,10,200,200)
        edges = cv2.Canny(openmask,50,100)
        circles = cv2.HoughCircles(edges,cv2.HOUGH_GRADIENT,1,1)
        if circles is not None:
            for circle in circles[0]:
                cv2.circle(frame,(circle[0],circle[1]),circle[2],(255,255,255),3);
                cv2.circle(frame,(circle[0],circle[1]),5,(0,0,0),-1);
        cv2.imshow("mask",mask)
        cv2.imshow("res",frame)
        cv2.waitKey(30);
        