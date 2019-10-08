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
 * MOSI  PB15 RW
 * 其他引脚
 * BUA 背光正极
 * BUK 背光负极
 * VCC 5V正极逻辑
 * VSS 逻辑共地
 * PSB 串行模式 接地
 * RST 复位，接地复位
 * 
 */

//估计时间在540KHZ时钟下确定
//清除显示 4.6ms
#define CMD_Clear 0x01 x
//字符地址设定 72us
#define CMD_CHARCTER_ADDR

//配置LCD12864 在SPI2上
void LCD12864Config(void);
//使用LCD12864显示字符
void LCD12864Write(char* str);
//使用LCD12864在指定位置显示字符 X[0-8] Y[0-4]
//void LCD12864WriteAt(char* str,int x,int y);
//任务要求的数字写入【不建议频繁调用】
void LCD12864NumDraw(int num1,int num2);
#endif
