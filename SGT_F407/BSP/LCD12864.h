#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f4xx.h"

/*
 * LCD16824 显示器
 * 将用来显示足够大的数字，来符合比赛要求
 * 使用SPI驱动
 * SPI2 
 * NSS   PB12 RS
 * SCK   PB13 E
 * MISO  PB14
 * MOSI  PB15 RW
 */

//配置LCD12864 在SPI2上
void LCD12864Config(void);

void LCDWrite(unsigned char mode,unsigned char data);

#endif
