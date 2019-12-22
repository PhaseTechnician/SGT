#ifndef _LCD12864_H
#define _LCD12864_H

#include "stm32f10x.h"
#include "Delay.h"

/*
 * LCD16824 ��ʾ��
 * ʹ��SPI����
 * SPI2 
 * NSS   PB12 RS Soft
 * SCK   PB13 E
 * MISO  PB14 empty 
 * MOSI  PB15 RW
 * ��������
 * BUA ��������
 * BUK ���⸺��
 * VCC 5V�����߼�
 * VSS �߼�����
 * PSB ����ģʽ �ӵ�
 * RST ��λ���ӵظ�λ
 */

//����LCD12864 ��SPI2��
void BSP_LCD12864_Config(void);
//ʹ��LCD12864��ʾ�ַ�
void BSP_LCD12864_Write_EN(char* str);
void BSP_LCD12864_WriteAtLine_EN(char* str,int line);
void LCD12864WriteAt_EN(char* str,int x,int y);
//LCD12864����
void BSP_LCD12864_Clear(void);
//LCD12864����ͼƬ
void BSP_LCD12864_DrawImage(const unsigned char* image);
#endif
