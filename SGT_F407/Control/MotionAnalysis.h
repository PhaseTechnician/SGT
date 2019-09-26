#ifndef _MOTIONANALYSIS_H
#define _MOTIONANALYSIS_H

#include "MontorDriver.h"
#include "PIDController.h"

/*
 * 运动解算和分析 【当前未完成PID整合】
 * 对四个轮子的速度进行分析和控制
 * 局部坐标系：
 *   1+x 2   
 *   +yoy-
 *   3-x 4  
 * 四轮的输出应该是以下三项的线性叠加
 *   陀螺仪--》角度偏差--》旋转分量
 * 寻线模块--》位置偏差--》平移分量
 * 任务指令--》前进方向--》移动分量
 */

//低四位代表车轮转向【不完善】
#define LocalOrientation_X_Positive 5;
#define LocalOrientation_X_Negitive 6;
#define LocalOrientation_Y_Positive 7;
#define LocalOrientation_Y_Negitive 8;
#define LocalOrientation_XY_1 1;
#define LocalOrientation_XY_2 2;  
#define LocalOrientation_XY_3 3;
#define LocalOrientation_XY_4 4;

//轮操作掩码 高四位正向使能 第四位反向使能
#define WHEEL_MASK_Clock          0b10100101
#define WHEEL_MASK_ANTICLOCK      0b01011010
#define WHEEL_MASK_FORWARD        0b11110000
#define WHEEL_MASK_BACKWARD       0b00001111
#define WHEEL_MASK_LEFT           0b01101001
#define WHEEL_MASK_Right          0b10010110
#define WHEEL_MASK_LEFT_FORWARD   0b01100000
#define WHEEL_MASK_RIGHT_FORWARD  0b10010000
#define WHEEL_MASK_LEFT_BACKWARD  0b00001001
#define WHEEL_MASK_RIGHT_BACKWARD 0b00000110
//初始化设置
void MontionAnalysisConfig(void);
//设置运行方向 
void SetOrientation(unsigned char LocalOrientation);
//设置运行速度
void SetSpeed(unsigned int LineSpeed);
//逻辑内核函数[不完善]
void MotionAnalysisOnStep(void);
//获取当前的世界坐标方向
//get()

#endif
