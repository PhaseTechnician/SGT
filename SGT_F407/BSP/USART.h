#ifndef _USART_H
#define _USART_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 *USART1 RX PA10 TX PA10
 */
//����1�ĳ�ʼ������
void USART1Config(int baud);
//����1�������ݣ��ⲻ�����̷��Ͷ������뻷�λ���
void USART1Send(char* stringPtr);
//�Ƿ��ڻ������µ��ַ�
bool IsUSART1Receive(void);
//����1�������ݣ��ӻ����ȡһ���ַ�
char USART1GetChar(void);

//������������DISABLE��
//������������DISABLE��

#endif
