#ifndef _MPU_H
#define _MPU_H

#include "BSP.h"
#include "stm32f10x.h"
#include <stdbool.h>

//本MPU9250的驱动极大的参考与GITHUB上SMARTIMU项目

#define MPU9250_SPI
typedef enum MPUReadValueAddressEnum
{
	ACCX = 0x3B,
	ACCY = 0x3D,
	ACCZ = 0x3F,
	GRYX = 0x43,
	GRYY = 0x45,
	GRYZ = 0x47,
	MAGX = 0X4A,
	MAGY = 0X4C,
	MAGZ = 0X4E,
	TEMP = 0X41
}MPUReadValueAddress;

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
#error "DON NOT FINISHED,ONLY SPI SUPPORTED"
#endif

//MPU相关资源初始化
void BSP_MPU_Config(void);
//MPU寄存器设置
void BSP_MPU_RegesterConfig(void);
void BSP_AK8963_RegisterConfig(void);
//MPU检测是否离线
bool BSP_MPU_CheckOnLine(void);
bool BSP_AK8963_CheckOnLine(void);
//MPU校准
void BSP_MPU_Calibrate(int times);

int16_t BSP_MPU_ReadValue(MPUReadValueAddress value);

void MPUWrite(unsigned char addr, unsigned char value);
unsigned char MPURead(unsigned char addr);
unsigned char MPUReadSendByte(unsigned char byte);
void MPUWriteByIIC(unsigned char reg, unsigned char value);
unsigned char MPUReadByIIC(unsigned char reg);

#endif
