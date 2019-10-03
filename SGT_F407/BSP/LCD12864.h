#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f4xx.h"
#include "Others.h"

//显示大小和换行目前存在问题
/*
 * LCD16824 显示器
 * 将用来显示足够大的数字，来符合比赛要求
 * 使用SPI驱动
 * SPI2 
 * NSS   PB12 RS Soft
 * SCK   PB13 E
 * MISO  PB14 empty 
 * MOSI  PC3 RW
 */

//配置LCD12864 在SPI2上
void LCD12864Config(void);
//使用LCD12864显示字符
void LCD12864Write(char* str);
//使用LCD12864在指定位置显示字符 X[0-8] Y[0-4]
//void LCD12864WriteAt(char* str,int x,int y);

#endif
