#ifndef _LINETRACK_H
#define _LINETRACK_H

#include "stm32f4xx.h"
/*
 * 寻迹传感器，作为IO中断存在
 * EXTI 1  PC1              1 + 2
 * EXTI 2  PC2                x
 * EXTI 3  PA3            3  x  4 
 * EXTI 4  PC4             +yyoyy-
 * EXTI 5  PC5             5  x  6
 * EXTI 6  PB6                x
 * EXTI 7  PB7              7 - 8 
 * EXTI 8  PB8
 */
 
//各位置代表寻迹模块读取的结果，你不应该修改它
extern unsigned char LineTrackResult;

//也许你因该使用这个函数来传递巡线模块的值，避免你意外的修改它
unsigned char GetLineTrackResult(void);
//初始化寻线的模块
void LineTrackConfig(void);

//通过位操作来获取对应的传感器模块
#define LT1 (LineTrackResult&0b00000001)
#define LT2 (LineTrackResult&0b00000010)
#define LT3 (LineTrackResult&0b00000100)
#define LT4 (LineTrackResult&0b00001000)
#define LT5 (LineTrackResult&0b00010000)
#define LT6 (LineTrackResult&0b00100000)
#define LT7 (LineTrackResult&0b01000000)
#define LT8 (LineTrackResult&0b10000000)

#endif
