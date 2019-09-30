#ifndef _SERVER_H
#define _SERVER_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * �����������
 * PWM ��� 
 * TIM8  CH1 CH2 CH3 CH4
 *       PC6 PC7 PC8 PC9
 * TIM11 CH1
 *       PB9
 */

typedef struct ServerInstanceStructure
{
	TIM_TypeDef* TIM;
	void (*setFunction)(TIM_TypeDef*,uint32_t);
	unsigned int base;
	unsigned int PWMRange;
	unsigned int angleRange;
}ServerInstance;

typedef ServerInstance* Server; 
extern const ServerInstance SERVER1;
extern const ServerInstance SERVER2;
extern const ServerInstance SERVER3;
extern const ServerInstance SERVER4;
extern const ServerInstance SERVER5;


//��ʼ�������ص�����
void ServerConfig(void);
//����һ������ĽǶ�
void ServerSetAngle(int angle,const ServerInstance* server);

//��ȡһ������ĽǶ�[DISABLE]
//int ServerGetAngle(int server);
//�Ƿ��������ϴ��趨��λ��[DISABLE]
//bool IsServerArrive(int server);

#endif
