#ifndef _ULTRASONIC_H  
#define _ULTRASONIC_H

#include "stm32f4xx.h"

/*
 * 超声波测距模块
 * 触发IO 
 * PE3 PE4 PE5 PE6
 * 回馈IC
 * TIM12CH1 TIM12CH2 TIM13CH1 TIM14CH1
 * PB14     PB15     PA6      PA7
 */


#define ULT_FRONT 0
#define ULT_LEFT 1
#define ULT_RIGHT 2
#define ULT_Back 3

//启动自动测距模式
//#define AutoGetDistance【DISABLE】【INBUILD】

//超声波测距相关资源初始化
void UltrasonicConfig(void);
//启动一次测距,返回为负数则意味着太远或太近，然而一般不会太近
int GetDistance(int ULT);

#endif
