#ifndef _USART_H
#define _USART_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * USART1 
 * RX PA10 TX PA10
 * ָ��ĵ���ʽ���н��� Ҫ�����һ���ֽ�Ϊ0
 * �յ�0֮�󣬸���ָ��洢��������  
 */

//����1�ĳ�ʼ������
void USART1Config(int baud);
//����1�������ݣ��ⲻ�����̷��Ͷ������뻷�λ���
void USART1Send(char* stringPtr);
//����1�������ݣ��ⲻ�����̷��Ͷ������뻷�λ���
void USART1SendLength(char* stringPtr,int num);
//�Ƿ��ڻ������µ�ָ��
bool USART1IsReceive(void);
//����1�������ݣ��ӻ����ȡһ��ָ��,����þ���ʹ�ã�����ᱻ����
char* USART1GetOrder(void);
//�������1�ϵ������ѽ��յ���ָ��
void USART1ClearReceive(void);

#endif
