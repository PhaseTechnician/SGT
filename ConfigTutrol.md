# 车辆配置调试文档

## 单元测试
    嵌入式系统自带外部模块和控制功能的单元测试案例，请按照底层到上层的顺序，严格检查设备连接和工作状态。    
    具体内容请参见Test.h文件。   
## 模块
+ 巡线模块
    > 调节电位器使得对应LED在黑色区域熄灭，其他区域明亮，可以适当增加围挡提高稳定性。
+ 电机驱动
    > 首先链接电路驱动部分，将驱动器和电机驱动输入输出相连，启动对应的MontorDriveOutputTest(),检查车轮转动方向。  
    > 之后测试电机反馈部分，为单独的电机编码器上电，调用MontorDriverFeedBackTest(),检查串口输出转速值，确保正向转动获得正向的度数反馈。  
    > 调节PID参数，链接串口到调试上位机，观察输出波形。通过修改 KP,KI,KD三个参数，使得曲线获得好的响应。  
+ 舵机调试
    > 链接舵机VCC,GND到5V，调用测试函数，比对舵机位置和旋转情况。
+ 陀螺仪调试
    > 陀螺仪在系统初始化过程中需要一段时间的自校准，不要在显示初始化完成之前驱动或强制移动车辆。  
    > 完成之后，通过旋转车辆，调节比例参数，校准角度范围。  
+ 超声波距离传感器
    > 超声波传感器不需要过分校准距离精度。  
    > 超声波传感器需要同时校准静态距离和动态距离。 
+ raspberry端口
    > 调用串口测试函数，在pi端使用VNC查看链接状态。   
    > 测试网络环境。    
    > 单独测试图形识别，启用对应识别模块，检查USB摄像头连接。   
## 控制 
+ 巡线与锚定器
    > 利用巡线模块实现，测试XY方向的巡线稳定程度，调节运动控制器中对应因子。  
    > 调整掩码设置，保证稳定性。   
+ 姿态控制
    > 调节MontionController对应参数，测试响应和稳定性。  