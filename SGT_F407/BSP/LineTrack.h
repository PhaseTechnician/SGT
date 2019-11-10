#ifndef _LINETRACK_H
#define _LINETRACK_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * 寻迹传感器，作为IO中断存在
 * 如果想要以触发的形式使用，请提前设置好两个回调，再使能
 * EXTI 1  PC1              1 + 2
 * EXTI 2  PC2                x
 * EXTI 3  PC3             3  x  4 
 * EXTI 4  PC4             +yyoyy-
 * EXTI 5  PC5             5  x  6
 * EXTI 6  PB6                x
 * EXTI 7  PB7              7 - 8 
 * EXTI 8  PB8
 * 相邻的一组传感器称为一个CP,用对应位置1的MASK表示
 */
 
//各位置代表寻迹模块读取的结果，你不应该修改它
extern unsigned char LineTrackResult;

//也许你因该使用这个函数来传递巡线模块的值，避免你意外的修改它
unsigned char GetLineTrackResult(void);
//初始化寻线的模块
void LineTrackConfig(void);
//打开或者关闭寻迹模块的中断响应,如果错误，多半是没有设置回调
bool LineTrackEnable(bool enable);
//触发引脚信息的分发[不向外部开放]
//void DistributeMassage(unsigned char trigerPin,bool isRising);
//设置定位参数
void SetAnchorParam(unsigned char mask,void (*CallBack)(unsigned char trigerPin,bool isrising));
//设置跟踪参数
void SetTrackParam(unsigned char mask,void (*CallBack)(unsigned char trigerPin,bool isrising));
//直接读取
unsigned char directReadLineTrackResult(void);
//判断是否出现电位变化
void CriticalDigitalLevelChange(void);
//通过位操作来获取对应的传感器模块
#define LT1 (LineTrackResult&0b00000001?1:0)
#define LT2 (LineTrackResult&0b00000010?1:0)
#define LT3 (LineTrackResult&0b00000100?1:0)
#define LT4 (LineTrackResult&0b00001000?1:0)
#define LT5 (LineTrackResult&0b00010000?1:0)
#define LT6 (LineTrackResult&0b00100000?1:0)
#define LT7 (LineTrackResult&0b01000000?1:0)
#define LT8 (LineTrackResult&0b10000000?1:0)
#define BIT_AT(OD,N) (OD&(0x01<<(N-1))?1:0)

#define PIN1 0x01
#define PIN2 0x02
#define PIN3 0x04
#define PIN4 0x08
#define PIN5 0x10
#define PIN6 0x20
#define PIN7 0x40
#define PIN8 0x80

#define YMask 0b00111100
#define XMask 0b11000011

#define CPMaskXP 0b00000011
#define CPMaskYP 0b00010100
#define CPMaskXN 0b11000000
#define CPMaskYN 0b00101000

#define HighMask 0b00010111
#define LowMask  0b11101000

#define MASK_CONTANT_BIT(mask,pin) (mask&pin)

#define LINE_TRACK_RESUT(pin) (LineTrackResult&pin)
//统计置1的位数
int Get1BitCount(unsigned char OBvalue);
#endif
