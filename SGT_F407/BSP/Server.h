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

//δ�����Ķ����
#define SERVER_1 1
#define SERVER_2 2
#define SERVER_3 3
#define SERVER_4 4
#define SERVER_5 5

//��ʼ�������ص�����
void ServerConfig(void);
//����һ������ĽǶ�
void ServerSetAngle(int angle,int server);

//��ȡһ������ĽǶ�[DISABLE]
int ServerGetAngle(int server);
//�Ƿ��������ϴ��趨��λ��[DISABLE]
bool IsServerArrive(int server);

#endif
