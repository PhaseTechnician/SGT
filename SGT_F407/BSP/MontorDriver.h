#ifndef _MONTORDRIVER_H
#define _MONTORDRIVER_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * Montor 电机控制器[不配备PID控制器]
 * PWM驱动调速 TIM1 
 *   CH1  CH2  CH3  CH4
 *   PE9  PE11 PE13 PE14
 * IO方向控制 
 *   M1A M1B M2A M2B M3A M3B M4A M4B
 *   PD0 PD1 PD2 PD3 PD4 PD5 PD6 PD7
 * 输入捕获测量编码器 
 *  ■■■ TIM2 TIM3 TIM4 TIM5 
 *  CH1 PA5  PA6  PD12 PA0
 *  CH2 PB3  PA7  PD13 PA1
 */

#define MONTOR_FRONT_LEFT    0b00
#define MONTOR_FRONT_RIGHT   0b01
#define MONTOR_BACK_LEFT     0b10
#define MONTOR_BACK_RIGHT    0b11

//初始化电机驱动的相关资源
void MontorDriverConfig(void);
//设置一个电机的速度，将直接反映到PWM占空比之上
void SetMontorSpeed(int speed,int montor);
//设置电机转向
void SetMontorRotation(bool positive,int montor);
//获取一个电机编码器获得的计数值，对应的时间变化量参考Others.h
int GetEncoderNum(int montor);
//获取一个电机的物理线速度，需要物理参数支持【DISABLE】
int GetMontorSpeed(int montor);

#endif
