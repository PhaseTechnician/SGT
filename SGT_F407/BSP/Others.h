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
void SetSystick(void);
//����ϵͳʱ�䲽
void OnStepSystick(void);

/*
 * ERROR 
 */
//������Ϣ�Ĵ���
void ErrorMessage(char *message);

#endif
