#ifndef _LINETRACK_H
#define _LINETRACK_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * Ѱ������������ΪIO�жϴ���
 * �����Ҫ�Դ�������ʽʹ�ã�����ǰ���ú������ص�����ʹ��
 * EXTI 1  PC1              1 + 2
 * EXTI 2  PC2                x
 * EXTI 3  PA3             3  x  4 
 * EXTI 4  PC4             +yyoyy-
 * EXTI 5  PC5             5  x  6
 * EXTI 6  PB6                x
 * EXTI 7  PB7              7 - 8 
 * EXTI 8  PB8
 * ���ڵ�һ�鴫������Ϊһ��CP
 */
 
//��λ�ô���Ѱ��ģ���ȡ�Ľ�����㲻Ӧ���޸���
extern unsigned char LineTrackResult;

//Ҳ�������ʹ���������������Ѳ��ģ���ֵ��������������޸���
unsigned char GetLineTrackResult(void);
//��ʼ��Ѱ�ߵ�ģ��
void LineTrackConfig(void);
//�򿪻��߹ر�Ѱ��ģ����ж���Ӧ,������󣬶����û�����ûص�
bool LineTrackEnable(bool enable);
//����������Ϣ�ķַ�
void DistributeMassage(unsigned char trigerPin,bool isRising);
//���ö�λ����
void SetAnchorParam(unsigned char mask,void (*CallBack)(unsigned char trigerPin,bool isrising));
//���ø��ٲ���
void SetTrackParam(unsigned char mask,void (*CallBack)(unsigned char trigerPin,bool isrising));
//ͨ��λ��������ȡ��Ӧ�Ĵ�����ģ��
#define LT1 (LineTrackResult&0b00000001)
#define LT2 (LineTrackResult&0b00000010)
#define LT3 (LineTrackResult&0b00000100)
#define LT4 (LineTrackResult&0b00001000)
#define LT5 (LineTrackResult&0b00010000)
#define LT6 (LineTrackResult&0b00100000)
#define LT7 (LineTrackResult&0b01000000)
#define LT8 (LineTrackResult&0b10000000)

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
//ͳ����1��λ��
int Get1BitCount(unsigned char OBvalue);
#endif
