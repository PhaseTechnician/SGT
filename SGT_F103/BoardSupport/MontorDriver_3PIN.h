#ifndef _MONTORDRIVER_3PIN_H
#define _MONTORDRIVER_3PIN_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * 利用定时器的PWM功能进行电机驱动输出
 * PC6-9
 */

//设置驱动IO和定时器
void BSP_MontorDriver_3Pin_Config(void);
//设置转速
void BSP_MontorDriver_3Pin_SetABSSpeed(unsigned int ABSspeed);
//设置转向
void BSP_MontorDriver_3Pin_SetRotation(bool isForward);
//设定输出值
void BSP_MontorDriver_3Pin_SetOutPut(int output);
//电机刹车模式
void BSP_MontorDriver_3Pin_Brake(void);

#endif
