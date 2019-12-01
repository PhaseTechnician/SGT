#ifndef _DELAY_H
#define _DELAY_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * 使用普通定时器来实现更高分辨率的堵塞延时
 */ 

void BSP_Delay_Config(void);

void BSP_Delay_DelayMs(unsigned int ms);

void BSP_Delay_DelayUs(unsigned int us);

#endif
