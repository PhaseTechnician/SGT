# SGT
## sketch
  In current logistics and factory production, AGV, as an efficient substitute for manual handling, plays a crucial role with lower cost and higher performance.It must be said objectively that the current various agvs have been able to have a good performance and efficient performance.However, AGV based on electromagnetic patrol and visual patrol is usually difficult to debug and maintain.However, the price of the current AGV car and its supporting system is still not affordable by ordinary factories.As the relevant control theory has been perfected and the price of hardware and software platforms has been decreasing year by year, it has become our goal to realize the common functions of AGV with relatively simple devices.
## principle
  MCU reads IMU to obtain inertial navigation data, and after correction and calculation, it is reflected into the wheel drive system to realize unreferenced inertial navigation and obtain better motion accuracy.The line trace is identified and processed by the camera, which provides the main operation reference.Vehicle-mounted proximity sensor ensures safe driving.The top manipulator USES precompiled action groups and instant IK to solve capturing material.The vehicle vision platform provides QRcode, bar code, color and shape recognition in the patrol line identification and completes the sorting.Transmission of vehicle information to the monitoring panel via local area network.
## Traget
  Design and manufacture of a 32-bit microcontroller based on the design of four McNamb wheel omnidirectional chassis controller, board four H bridge motor drive, four orthogonal encoder interface and IMU interface, and provide SPI,CAN,USB_device, USART communication interface, to achieve common wheel motion system without loss of versatility control functions.
Design and manufacture of an AGV car, with material grab, visual navigation, material sorting functions, and through the carefully designed communication protocol and the console communication, the basic Internet of things function.
background
## mechanical
### image
  ![ModleDisplay](https://github.com/PhaseTechnician/SGT/blob/master/media/SGT_final_Eeve.jpg)
### video
  [旋转展示](https://github.com/PhaseTechnician/SGT/blob/master/media/%E6%97%8B%E8%BD%AC%E5%BE%AA%E7%8E%AF%E5%B1%95%E7%A4%BA.mp4)
  [方形扫略](https://github.com/PhaseTechnician/SGT/blob/master/media/%E7%8E%AF%E8%A7%86%E8%A7%86%E9%A2%91.mp4)
  [捕获模拟](https://github.com/PhaseTechnician/SGT/blob/master/media/%E8%BF%90%E5%8A%A8%E6%8D%95%E8%8E%B7%E6%BC%94%E7%A4%BA.mp4)
## code structure
  ![code](https://github.com/PhaseTechnician/SGT/blob/master/media/flow.png)

this porject is still in building...
