#ifndef _SERVER_H
#define _SERVER_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * 舵机控制设置
 * PWM 输出 
 * TIM8  CH1 CH2 CH3 CH4
 *       PC6 PC7 PC8 PC9
 * TIM11 CH1
 *       PB9
 */

//未命名的舵机组
#define SERVER_1 1
#define SERVER_2 2
#define SERVER_3 3
#define SERVER_4 4
#define SERVER_5 5

//初始化舵机相关的驱动
void ServerConfig(void);
//设置一个舵机的角度
void ServerSetAngle(int angle,int server);

//获取一个舵机的角度[DISABLE]
int ServerGetAngle(int server);
//是否舵机到达上次设定的位置[DISABLE]
bool IsServerArrive(int server);

#endif
