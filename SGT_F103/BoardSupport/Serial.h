#ifndef _SERIAL_H
#define _SERIAL_H

#include "stm32f10x.h"
#include <stdbool.h>

/*
 * USART1 
 * RX PA10 TX PA9
 * 0 作为终止字符
 */

#define BSP_Serial_MaxOrderLength 20
#define BSP_Serial_MaxReceiveNum 10

//串口1的初始化设置
void BSP_Serial_Config(int baud);
//串口读取一个指令
void BSP_Serial_Read(char* orderPtr);
//串口预读一个指令
void BSP_Serial_Peek(char* orderPtr);

//串口1发送字符
void BSP_Serial_SendChar(char c);
//串口1发送数据
void BSP_Serial_SendString(char* stringPtr);
//串口1发送定长数据
void BSP_Serial_SendLength(char* stringPtr,int num);
//串口一发送一个数字
void BSP_Serial_SendInt(int num);

#endif
