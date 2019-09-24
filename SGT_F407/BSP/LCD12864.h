#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f4xx.h"

/*
 * LCD16824 ��ʾ��
 * ��������ʾ�㹻������֣������ϱ���Ҫ��
 * ʹ��SPI����
 * SPI2 
 * NSS   PB12 RS
 * SCK   PB13 E
 * MISO  PB14
 * MOSI  PB15 RW
 */

//����LCD12864 ��SPI2��
void LCD12864Config(void);

void LCDWrite(unsigned char mode,unsigned char data);

#endif
