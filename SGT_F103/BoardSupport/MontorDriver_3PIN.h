#ifndef _MONTORDRIVER_3PIN_H
#define _MONTORDRIVER_3PIN_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * 利用定时器的PWM功能进行电机驱动输出
 * PC6-9 TIM CH1-4
 * PC0-5 PP PB0 PB1 PP
 */

typedef enum MontorInstance
{
	MontorFL,
	MontorFR,
	MontorBL,
	MontorBR
}Montor;

//设置驱动IO和定时器
void BSP_MontorDriver_3Pin_Config(void);
//设置转速
void BSP_MontorDriver_3Pin_SetABSSpeed(unsigned int ABSspeed,Montor montor);
//设置转向
void BSP_MontorDriver_3Pin_SetRotation(bool isForward,Montor montor);
//设定输出值
void BSP_MontorDriver_3Pin_SetOutPut(int output,Montor montor);
//电机刹车模式
void BSP_MontorDriver_3Pin_Brake(Montor montor);

#endif
