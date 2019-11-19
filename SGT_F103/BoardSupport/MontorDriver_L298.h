#ifndef _MONTORDRIVER_L298N_H
#define _MONTORDRIVER_L298N_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * 利用定时器的PWM功能进行电机驱动输出
 */

//设置驱动IO和定时器
void BSP_MontorDriver_L298_Config();
//设置转速
void BSP_MontorDriver_L298_SetABSSpeed(unsigned int ABSspeed);
//设置转向
void BSP_MontorDriver_L298_SetRotation(bool isForward);
//设定输出值
void BSP_MontorDriver_L298_SetOutPut(int output);
//电机刹车模式
void BSP_MontorDriver_L298_Brake();

#endif
