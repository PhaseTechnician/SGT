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
//ϵͳʱ����
#define sysInterval 10
//ϵͳʱ�������س�ʼ��
void SystickConfig(void);
//����ϵͳʱ�䲽
void OnStepSystick(void);

/*
 * ERROR 
 */
//������Ϣ�Ĵ���
void ErrorMessage(char *message);

#endif
