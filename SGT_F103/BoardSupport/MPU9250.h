#ifndef _MPU_H
#define _MPU_H

#include "stm32f10x.h"
#include <stdbool.h>

#define MPU9250_SPI

#ifdef MPU9250_SPI
/*
 * ��̬������MPU
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

//MPU�����Դ��ʼ��
void BSP_MPU_Config(void);
//MPU�Ĵ�������
void BSP_MPU_RegesterConfig(void);
//MPU9250��������
void BSP_MPU_WakeUp(void);
//MPU����Ƿ�����
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
