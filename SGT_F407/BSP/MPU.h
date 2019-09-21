#ifndef _MPU_H
#define _MPU_H

#include "stm32f4xx.h"
#include <stdbool.h>

/*
 * ��̬������MPU
 * 
 */

extern float AccX,AccY,AccZ;
extern float OmgX,OmgY,OmgZ;
//extern float MagX,MagY,MagZ;
extern float temp;

//MPU�����Դ��ʼ��
void MpuConfig(void);
//MPU����Ƿ�����
bool CheckMpuOnLine(void);

#endif
