#ifndef _BSP_H
#define _BSP_H

#include <stdbool.h>
#include "LED.h"
#include "Delay.h"
#include "Serial.h"
#include "KeyBoard.h"
#include "Encoder_TIM.h"
#include "MontorDriver_3Pin.h"
#include "MPU9250.h"

//������������
void BSP_Modles_Config(void);
//�����Χģ������
bool BSP_Modles_Test(void);

#endif
