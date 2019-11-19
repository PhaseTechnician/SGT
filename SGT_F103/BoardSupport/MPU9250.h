#ifndef _MPU_H
#define _MPU_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * ��̬������MPU
 * SPI3
 *  PA5 SCLK
 *  PA6 MISO
 *  PA7 MOSI
 *  PA4 NSS
 */

extern float AccX,AccY,AccZ;
extern float OmgX,OmgY,OmgZ;
//extern float MagX,MagY,MagZ;
extern float temp;

//MPU�����Դ��ʼ��
void MpuConfig(void);
//MPU����Ƿ�����
bool CheckMPUOnLine(void);


void MPUWrite(unsigned char addr,unsigned char value);
unsigned char MPURead(unsigned char addr);
unsigned char MPUReadSendByte(unsigned char byte);
#endif
