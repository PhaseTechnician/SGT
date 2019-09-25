#ifndef _OTHERS_H
#define _OTHERS_H

#include "stm32f4xx.h"
/*
 * NVIC
 */
//NVIC�ĳ�ʼ������
void NVICConfig(void);

/*
 * SYSTICK
 */
//ϵͳʱ�������س�ʼ��
void SystickConfig(void);
//��ȡ��Ӧ��λȡ����ʱ��
unsigned int GetPartTimeS(void);
unsigned int GetPartTimeMs(void);
unsigned int GetPartTimeUs(void);
//��ȡ�ö�Ӧ��λ��ʾ��ȫ��ʱ��
unsigned int GetTotalTimeMs(void);
/*
 * �ṩ�߾��ȵ�ʱ����
 * TIM6
 * DelayUs();
 */
//��ʼ����ʱ���������ö�Ӧ��ʱ��
void DelayFunctionConfig(void);
//��������һ��ʱ�� 
void Delay(int16_t us);
//�ϳ�ʱ�������
void DelayS(unsigned int s);
/*
 * ERROR 
 */
//������Ϣ�Ĵ���
void ErrorMessage(char *message);

#endif
