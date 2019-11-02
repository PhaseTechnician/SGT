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
 *  ■■■ TIM9 TIM3 TIM4 TIM5 
 *  CH1 PA2  PA6  PD12 PA0
 *  CH2 PA3  PB5  PD13 PA1
 */


//特别注意编码计数器的误判在较长的时间之后

typedef struct MontorInstanceStructure
{
	TIM_TypeDef* TIM;
	uint16_t PINA;
	uint16_t PINB;
	int EncoderFactor;
	void (*setFunction)(TIM_TypeDef* TIM,uint32_t value);
}MontorInstance;

extern const MontorInstance MONTOR_FRONT_LEFT;
extern const MontorInstance MONTOR_FRONT_RIGHT;
extern const MontorInstance MONTOR_BACK_LEFT;
extern const MontorInstance MONTOR_BACK_RIGHT;

//初始化电机驱动的相关资源
void MontorDriverConfig(void);
//设置一个电机绝对速度，将直接反映到PWM占空比之上
void SetMontorAbsSpeed(unsigned int speed,const MontorInstance* montor);
//设置电机转向
void SetMontorRotation(bool positive,const MontorInstance* montor);
//设置电机速度
void SetMontorSpeed(int speed,const MontorInstance* montor);
//获取一个电机编码器获得的计数值，对应的时间变化量参考Others.h
int GetEncoderNum(const MontorInstance* montor);
//重置全部的电机编码器计数值
void ResetEncoderNum(void);
//获取一个电机的物理线速度，需要物理参数支持【DISABLE】
int GetMontorSpeed(const MontorInstance* montor);

#endif
