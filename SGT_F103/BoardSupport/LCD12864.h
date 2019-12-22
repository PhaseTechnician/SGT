#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f10x.h"
#include "Delay.h"

/*
 * LCD16824 显示器
 * 使用SPI驱动
 * SPI2 
 * NSS   PB12 RS Soft
 * SCK   PB13 E
 * MISO  PB14 empty 
 * MOSI  PB15 RW
 * 其他引脚
 * BUA 背光正极
 * BUK 背光负极
 * VCC 5V正极逻辑
 * VSS 逻辑共地
 * PSB 串行模式 接地
 * RST 复位，接地复位
 */

//配置LCD12864 在SPI2上
void BSP_LCD12864_Config(void);
//使用LCD12864显示字符
void BSP_LCD12864_Write_EN(char* str);
void BSP_LCD12864_WriteAtLine_EN(char* str,int line);
void LCD12864WriteAt_EN(char* str,int x,int y);
//LCD12864清屏
void BSP_LCD12864_Clear(void);
//LCD12864绘制图片
void BSP_LCD12864_DrawImage(const unsigned char* image);
#endif
