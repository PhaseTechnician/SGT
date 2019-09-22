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

//������������
void BSPConfig(void);
//�����Χģ������
bool BSPTest(void);

#endif
