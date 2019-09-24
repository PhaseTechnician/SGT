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
//系统时间间隔
#define sysInterval 10
//系统时间计数相关初始化
void SystickConfig(void);
//更新系统时间步
void OnStepSystick(void);

/*
 * ERROR 
 */
//错误信息的处理
void ErrorMessage(char *message);

#endif
