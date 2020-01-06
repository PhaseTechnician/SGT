#ifndef _MPU_H
#define _MPU_H

#include "stm32f10x.h"
#include <stdbool.h>
#include "BSP.h"

#define MPU9250_SPI

#ifdef MPU9250_SPI
/*
 * 姿态传感器MPU
 * SPI1
 *  PA5 SCLK
 *  PA6 MISO 
 *  PA7 MOSI 
 *  PA4 NSS
 *  FSYNC GND
 */
#endif
#ifdef MPU9250_IIC
/*
	* IIC2 PB10 SCL    PB11 SDA
	*/
#endif	

//MPU相关资源初始化
void BSP_MPU_Config(void);
//MPU寄存器设置
void BSP_MPU_RegesterConfig(void);
//MPU9250唤醒设置
void BSP_MPU_WakeUp(void);
//MPU检测是否离线
bool BSP_MPU_CheckOnLine(void);
//MPU校准
void BSP_MPU_Calibrate(int times);

int16_t BSP_MPU_ReadACCX(void);
int16_t BSP_MPU_ReadACCY(void);
int16_t BSP_MPU_ReadACCZ(void);
int16_t BSP_MPU_ReadOMGX(void);
int16_t BSP_MPU_ReadOMGY(void);
int16_t BSP_MPU_ReadOMGZ(void);
int16_t BSP_MPU_ReadTEMP(void);
int16_t BSP_MPU_ReadMAGX(void);
int16_t BSP_MPU_ReadMAGY(void);
int16_t BSP_MPU_ReadMAGZ(void);
void BSP_MPU_ReadMAG(int16_t* mag);


void MPUWrite(unsigned char addr,unsigned char value);
unsigned char MPURead(unsigned char addr);
unsigned char MPUReadSendByte(unsigned char byte);
void MPUWriteByIIC(unsigned char reg, unsigned char value);
unsigned char MPUReadByIIC(unsigned char reg);

#endif
