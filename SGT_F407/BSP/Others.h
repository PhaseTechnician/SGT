#ifndef _OTHERS_H
#define _OTHERS_H

#include "stm32f4xx.h"
/*
 * NVIC
 */
//NVIC的初始化设置
void NVICConfig(void);

/*
 * SYSTICK
 */
//系统时间计数相关初始化
void SystickConfig(void);
//获取对应单位取整的时间
unsigned int GetPartTimeS(void);
unsigned int GetPartTimeMs(void);
unsigned int GetPartTimeUs(void);
//获取用对应单位表示的全部时间
unsigned int GetTotalTimeMs(void);
/*
 * 提供高精度的时序函数
 * TIM6
 * DelayUs();
 */
//初始化延时函数，配置对应计时器
void DelayFunctionConfig(void);
//程序阻塞一段时间 
void Delay(int16_t us);
//较长时间的阻塞
void DelayS(unsigned int s);
/*
 * ERROR 
 */
//错误信息的处理
void ErrorMessage(char *message);

#endif
