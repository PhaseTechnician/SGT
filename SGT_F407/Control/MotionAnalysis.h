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

//轮操作掩码 高四位正向使能 低四位反向使能
#define WHEEL_MASK_CLOCK          0b10100101
#define WHEEL_MASK_ANTICLOCK      0b01011010
#define WHEEL_MASK_FORWARD        0b11110000
#define WHEEL_MASK_BACKWARD       0b00001111
#define WHEEL_MASK_LEFT           0b01101001
#define WHEEL_MASK_RIGHT          0b10010110
#define WHEEL_MASK_LEFT_FORWARD   0b01100000
#define WHEEL_MASK_RIGHT_FORWARD  0b10010000
#define WHEEL_MASK_LEFT_BACKWARD  0b00001001
#define WHEEL_MASK_RIGHT_BACKWARD 0b00000110
#define WHEEL_MASK_EMPTY          0b00000000

//注意无论如何，三项之和不得超过最大电机速度
//同时，需要留出一定的范围为PID控制提供操作余量

extern int MoveSpeedFactor;
extern int RotateSpeedFactor;
extern int TranslateSpeedFactor;
extern unsigned char MoveMask;
extern unsigned char TranslateMask;
extern unsigned char RotateMask;

//初始化设置
void MontionAnalysisConfig(void);
//设置底盘的速度和方向,不经自动维护直接赋值
void MotionAnalysisDirectSet(int speed,unsigned char WHEEL_MASK);
//逻辑内核函数[不完善]【考虑以100ms间隔调用】【太小的间隔导致编码器不能积累足够多的数值进行平均，太长的间隔影响逻辑的运行】
void MotionAnalysisOnStep(void);

#endif
