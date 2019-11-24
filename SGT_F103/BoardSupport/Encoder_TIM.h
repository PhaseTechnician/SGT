#ifndef _ENCODER_TIM_H
#define _ENCODER_TIM_H

#include "stm32f10x.h"

/*
 * 利用TIM的CH1,CH2实现正交编码器的使用
 */

//设置编码器
void BSP_Encoder_Config(void);
//获取编码值
int BSP_Encoder_GetCode(void);
//重置编码器
void BSP_Encoder_Reset(void);

#endif
