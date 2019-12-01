#ifndef _BSP_H
#define _BSP_H

#include <stdbool.h>
#include "LED.h"
#include "Serial.h"
#include "MPU9250.h"
#include "Delay.h"

//配置所有外设
void BSP_Modles_Config(void);
//检测外围模块连接
bool BSP_Modles_Test(void);

#endif
