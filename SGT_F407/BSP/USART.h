#ifndef _USART_H
#define _USART_H

#include "stm32f4xx.h"
#include <stdbool.h>
/*
 * USART1 
 * RX PA10 TX PA10
 * 指令报文的形式进行接收 要求最后一个字节为0
 * 收到0之后，该条指令被存储到缓存区  
 */

//串口1的初始化设置
void USART1Config(int baud);
//串口1发送数据，这不会立刻发送而是填入环形缓冲
void USART1Send(char* stringPtr);
//是否在缓冲有新的指令
bool IsUSART1Receive(void);
//串口1接收数据，从缓冲读取一个指令
char* USART1GetOrder(void);


#endif
