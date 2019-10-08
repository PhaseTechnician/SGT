#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f4xx.h"
#include "Others.h"

/*
 * LED����� ��ʾ��
 * ʹ��SPI����
 * SPI2 
 * NSS   PB12 
 * SCK   PB13 
 * MISO  PB14 empty 
 * MOSI  PB15 
 */
 
//����LCD12864 ��SPI2��
void LEDMX7219Config(void);
//����Ҫ�������д�롾������Ƶ�����á�
void LEDWrite(int num1,int num2);

#endif
