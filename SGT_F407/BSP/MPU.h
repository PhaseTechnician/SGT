#ifndef _MPU_H
#define _MPU_H

#include "stm32f4xx.h"
#include <stdbool.h>

/*
 * 姿态传感器MPU
 * 
 */

extern float AccX,AccY,AccZ;
extern float OmgX,OmgY,OmgZ;
//extern float MagX,MagY,MagZ;
extern float temp;

//MPU相关资源初始化
void MpuConfig(void);
//MPU检测是否离线
bool CheckMpuOnLine(void);

#endif
