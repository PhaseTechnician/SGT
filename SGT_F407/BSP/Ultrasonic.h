#ifndef _ULTRASONIC_H  
#define _ULTRASONIC_H

#include "stm32f4xx.h"
#include "Others.h"
#include <stdbool.h>
/*
 * 超声波测距模块
 * 触发IO 
 * PE3 PE4 PE5 PE6
 * 回馈IC
 * TIM12CH1 TIM12CH2 TIM13CH1 TIM14CH1【】
 * PB14     PB15     PA6      PA7【】
 * 基于单一定时器的捕获进行测量，多个传感器循环测量，限制测量频率
 */

typedef struct UltrasonicInstanceStructure
{
	GPIO_TypeDef* TIM;
	uint16_t pin;
	uint16_t echoLength;
}UltrasoniceInstance;

//启动自动测距模式
//#define AutoGetDistance【DISABLE】【INBUILD】

extern UltrasoniceInstance ULT1,ULT2,ULT3,ULT4;

//超声波测距相关资源初始化
void UltrasonicConfig(void);
//启动一次测距,返回为负数则意味着太远或太近，然而一般不会太近
int GetDistance(UltrasoniceInstance* instance);//[目前是堵塞的]
//判断是否持有新的数据【DISABLE】
bool IsUltrasonicFinish(UltrasoniceInstance* instance);
//启动一次测距
void StartOnceDetecte(UltrasoniceInstance* instance);
//从计数值转换到厘米单位
int GetCM(int count);
//常规主逻辑循环【DISABLE】
void UltrasonicOnStep(void);

#endif
