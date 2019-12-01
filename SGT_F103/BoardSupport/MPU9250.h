#ifndef _MPU_H
#define _MPU_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * 姿态传感器MPU
 * SPI3
 *  PA5 SCLK
 *  PA6 MISO
 *  PA7 MOSI
 *  PA4 NSS
 */

//MPU相关资源初始化
void BSP_MPU_Config(void);
//MPU寄存器设置
void BSP_MPU_RegesterConfig(void);
//MPU9250唤醒设置
void BSP_MPU_WakeUp(void);
//MPU检测是否离线
bool BSP_MPU_CheckOnLine(void);

int16_t BSP_MPU_ReadACCX(void);
int16_t BSP_MPU_ReadACCY(void);
int16_t BSP_MPU_ReadACCZ(void);
int16_t BSP_MPU_ReadOMGX(void);
int16_t BSP_MPU_ReadOMGY(void);
int16_t BSP_MPU_ReadOMGZ(void);
int16_t BSP_MPU_ReadTEMP(void);


void MPUWrite(unsigned char addr,unsigned char value);
unsigned char MPURead(unsigned char addr);
unsigned char MPUReadSendByte(unsigned char byte);
#endif
