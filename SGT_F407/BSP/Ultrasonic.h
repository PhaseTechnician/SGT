#ifndef _ULTRASONIC_H  
#define _ULTRASONIC_H

#include "stm32f4xx.h"
#include "Others.h"
#include <stdbool.h>
/*
 * ���������ģ��
 * ����IO 
 * PE3 PE4 PE5 PE6
 * ����IC
 * TIM12CH1 TIM12CH2 TIM13CH1 TIM14CH1����
 * PB14     PB15     PA6      PA7����
 * ���ڵ�һ��ʱ���Ĳ�����в��������������ѭ�����������Ʋ���Ƶ��
 */

typedef struct UltrasonicInstanceStructure
{
	GPIO_TypeDef* TIM;
	uint16_t pin;
	uint16_t echoLength;
}UltrasoniceInstance;

//�����Զ����ģʽ
//#define AutoGetDistance��DISABLE����INBUILD��

extern UltrasoniceInstance ULT1,ULT2,ULT3,ULT4;

//��������������Դ��ʼ��
void UltrasonicConfig(void);
//����һ�β��,����Ϊ��������ζ��̫Զ��̫����Ȼ��һ�㲻��̫��
int GetDistance(UltrasoniceInstance* instance);//[Ŀǰ�Ƕ�����]
//�ж��Ƿ�����µ����ݡ�DISABLE��
bool IsUltrasonicFinish(UltrasoniceInstance* instance);
//����һ�β��
void StartOnceDetecte(UltrasoniceInstance* instance);
//�Ӽ���ֵת�������׵�λ
int GetCM(int count);
//�������߼�ѭ����DISABLE��
void UltrasonicOnStep(void);

#endif
