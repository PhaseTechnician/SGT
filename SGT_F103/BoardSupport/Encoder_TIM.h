#ifndef _ENCODER_TIM_H
#define _ENCODER_TIM_H

#include "stm32f10x.h"

/*
 * 利用TIM的CH1,CH2实现正交编码器的使用
 */

//设置编码器
void BSP_Encoder_Config();
//获取编码值
int BSP_Encoder_GetCode();
//重置编码器
void BSP_Encoder_Reset();

#endif