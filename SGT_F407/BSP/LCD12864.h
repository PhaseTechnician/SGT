#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f4xx.h"
#include "Others.h"

//��ʾ��С�ͻ���Ŀǰ��������
/*
 * LCD16824 ��ʾ��
 * ��������ʾ�㹻������֣������ϱ���Ҫ��
 * ʹ��SPI����
 * SPI2 
 * NSS   PB12 RS Soft
 * SCK   PB13 E
 * MISO  PB14 empty 
 * MOSI  PC3 RW
 */

//����LCD12864 ��SPI2��
void LCD12864Config(void);
//ʹ��LCD12864��ʾ�ַ�
void LCD12864Write(char* str);
//ʹ��LCD12864��ָ��λ����ʾ�ַ� X[0-8] Y[0-4]
//void LCD12864WriteAt(char* str,int x,int y);

#endif
