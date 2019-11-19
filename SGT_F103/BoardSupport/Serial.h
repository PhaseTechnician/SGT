#ifndef _SERIAL_H
#define _SERIAL_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * USART1 
 * RX PA10 TX PA9
 * 0 ��Ϊ��ֹ�ַ�
 */

#define BSP_Serial_MaxOrderLength 20
#define BSP_Serial_MaxReceiveNum 10

//����1�ĳ�ʼ������
void BSP_Serial_Config(int baud);
//���ڶ�ȡһ��ָ��
void BSP_Serial_Read(char* orderPtr);
//����Ԥ��һ��ָ��
void BSP_Serial_Peek(char* orderPtr);

//����1�����ַ�
void BSP_Serial_SendChar(char c);
//����1��������
void BSP_Serial_SendString(char* stringPtr);
//����1���Ͷ�������
void BSP_Serial_SendLength(char* stringPtr,int num);
//����һ����һ������
void BSP_Serial_SendInt(int num);

#endif
