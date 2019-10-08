#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f4xx.h"
#include "Others.h"

/*
 * LED数码管 显示器
 * 使用SPI驱动
 * SPI2 
 * NSS   PB12 
 * SCK   PB13 
 * MISO  PB14 empty 
 * MOSI  PB15 
 */
 
//配置LCD12864 在SPI2上
void LEDMX7219Config(void);
//任务要求的数字写入【不建议频繁调用】
void LEDWrite(int num1,int num2);

#endif
