#ifndef _LED_H
#define _LED_H

#include "stm32f4xx.h"
/*
 * LED 数码管基于MAX7219 [考虑SPI硬件驱动]
 *  DIN  CS    CLK
 *  PB0  PB1   PB2 
 */
 
//LED的相关资源初始化
void LedConfig(void);
//设置LED的某位为数字【不大于9】
void SetLedBit(int num,int bit);
//设置LED的第一个数字和第二个数字【不大于9999】
void SetLed(int firstNum,int SecondNum);

#endif
