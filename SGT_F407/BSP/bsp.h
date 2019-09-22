#ifndef _BSP_H
#define _BSP_H

#include "USART.h"
#include "LineTrack.h"
#include "Others.h"
#include "MontorDriver.h"
#include "Server.h"
#include "LED.h"
#include "MPU.h"
#include "Ultrasonic.h"
#include <stdbool.h>

//配置所有外设
void BSPConfig(void);
//检测外围模块连接
bool BSPTest(void);

#endif
