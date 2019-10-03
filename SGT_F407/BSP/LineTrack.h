#ifndef _LINETRACK_H
#define _LINETRACK_H

#include "stm32f4xx.h"
/*
 * Ѱ������������ΪIO�жϴ���
 * EXTI 1  PC1              1 + 2
 * EXTI 2  PC2                x
 * EXTI 3  PA3            3  x  4 
 * EXTI 4  PC4             +yyoyy-
 * EXTI 5  PC5             5  x  6
 * EXTI 6  PB6                x
 * EXTI 7  PB7              7 - 8 
 * EXTI 8  PB8
 */
 
//��λ�ô���Ѱ��ģ���ȡ�Ľ�����㲻Ӧ���޸���
extern unsigned char LineTrackResult;

//Ҳ�������ʹ���������������Ѳ��ģ���ֵ��������������޸���
unsigned char GetLineTrackResult(void);
//��ʼ��Ѱ�ߵ�ģ��
void LineTrackConfig(void);

//ͨ��λ��������ȡ��Ӧ�Ĵ�����ģ��
#define LT1 (LineTrackResult&0b00000001)
#define LT2 (LineTrackResult&0b00000010)
#define LT3 (LineTrackResult&0b00000100)
#define LT4 (LineTrackResult&0b00001000)
#define LT5 (LineTrackResult&0b00010000)
#define LT6 (LineTrackResult&0b00100000)
#define LT7 (LineTrackResult&0b01000000)
#define LT8 (LineTrackResult&0b10000000)

#endif
