#ifndef _BEEP_H
#define _BEEP_H

#include <stdbool.h>
#include "stm32f10x.h"
//配置蜂鸣器
void BSP_Beep_Config(void);
//使能蜂鸣器
void BSP_Beep_Enable(bool enable);

#endif
