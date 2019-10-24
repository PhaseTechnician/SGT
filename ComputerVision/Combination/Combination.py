import cv2
import serial
import numpy

#常量定义区域
RedLow = numpy.array({0,0,0},numpy.uint8)
RedHigh = numpy.array({0,0,0},numpy.uint8)
GreenLow = numpy.array({0,0,0},numpy.uint8)
GreenHigh = numpy.array({0,0,0},numpy.uint8)
BlueLow = numpy.array({0,0,0},numpy.uint8)
BlueHigh = numpy.array({0,0,0},numpy.uint8)


def dealOrder(char1,char2):
    if order[0] == 'S':
        COM.write("123321")
    elif order[0] == 'T':
        COM.write("OK")
    #elif order[0] == 'P':

    #elif order[0] == 'A':

    #elif order[0] == 'C':


#函数运行区域
#COM = serial.Serial('COM',9600)
COM = serial.Serial('/dev/ttyUSB0',9600)
COM.open()
if COM.isOpen():
    while True:
        if COM.isWaiting()>4:
            if COM.read(1) is '<':
                order=COM.read(2)
else:
    print("ERROR OPEN COM FAILED\R\N");

#order两个字节【地址】【数据】 
# SCANQR 'S' empty
# PEEK   'P' empty
# ADJUST 'A' 'R/G/B'
# CATCH  'C' 'R/G/B' 
#回传数据格式相对定制化
# SCANQR [8][8][8][8][8][8] 123321       二维码信息
# PEEK   [8][8][8]          RGB          色块的顺序【以字符发送】
# ADJUST [8][8][8]          [123][23][0] 圆中心偏移坐标【连续刷新】
# CATCH  [8]                [1]/[0]      是否捕捉到对应颜色