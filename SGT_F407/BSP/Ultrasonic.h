#ifndef _ULTRASONIC_H  
#define _ULTRASONIC_H

#include "stm32f4xx.h"

/*
 * ���������ģ��
 * ����IO 
 * PE3 PE4 PE5 PE6
 * ����IC
 * TIM12CH1 TIM12CH2 TIM13CH1 TIM14CH1
 * PB14     PB15     PA6      PA7
 */


#define ULT_FRONT 0
#define ULT_LEFT 1
#define ULT_RIGHT 2
#define ULT_Back 3

//�����Զ����ģʽ
//#define AutoGetDistance��DISABLE����INBUILD��

//��������������Դ��ʼ��
void UltrasonicConfig(void);
//����һ�β��,����Ϊ��������ζ��̫Զ��̫����Ȼ��һ�㲻��̫��
int GetDistance(int ULT);

#endif
