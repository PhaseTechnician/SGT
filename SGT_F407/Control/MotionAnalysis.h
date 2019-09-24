#ifndef _MOTIONANALYSIS_H
#define _MOTIONANALYSIS_H

#include "MontorDriver.h"
/*
 * 运动解算和分析 【当前未完成PID整合】
 * 对四个轮子的速度进行分析和控制
 * 局部坐标系：
 *    +x    
 *   +yoy-
 *    -x   
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

//设置运行方向 
void SetOrientation(unsigned char LocalOrientation);
//设置运行速度
void SetSpeed(unsigned int LineSpeed);
//逻辑内核函数[不完善]
void MotionAnalysisOnStep(void);
//获取当前的世界坐标方向
//get()

#endif
