import cv2
import numpy as np

def display(im, bbox):
    n = len(bbox)
    for j in range(n):
        cv2.line(im, tuple(bbox[j][0]), tuple(bbox[(j + 1) % n][0]), (255, 0, 0), 3)
    cv2.imshow("Results", im)

capture=cv2.VideoCapture(0) 
while(True):
    ref,frame=capture.read()
#inputImage = cv2.imread("F:\\SGT\\ComputerVision\\image\\123+321.png")
    decoder = cv2.QRCodeDetector()
    data, bbox, rectifiedImage = decoder.detectAndDecode(frame)
    if len(data) > 0:
        print("Decoded Data : {}".format(data))
        display(frame, bbox)
    else:
        print("QR Code not detected")
        cv2.imshow("Results", frame)
    cv2.waitKey(30);

cv2.waitKey(0)
cv2.destroyAllWindows()