#ifndef _BSP_H
#define _BSP_H

#include <stdbool.h>
#include "LED.h"
#include "Serial.h"
#include "MPU9250.h"
#include "Delay.h"

//������������
void BSP_Modles_Config(void);
//�����Χģ������
bool BSP_Modles_Test(void);

#endif
