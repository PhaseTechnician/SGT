#include "Serial.h"
#include "FreeRTOS.h"
#include "queue.h"

//串行接收缓冲
char BSP_Serial_ReceiveBuffer[BSP_Serial_MaxOrderLength+1]={0};
//缓冲使用计数
uint16_t BSP_Serial_ReceiveBufferIndex=0;

QueueHandle_t BSP_Serial_ReceiveFIFO;
QueueHandle_t BSP_Serial_SendFIFO;

BaseType_t Receive_TaskSwitch;

void BSP_Serial_Config(int baud)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=baud;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	//USART_ITConfig(USART1,USART_IT_CTS,ENABLE);//发送完中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//接收中断
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
	/*OS*/
	BSP_Serial_ReceiveFIFO = xQueueCreate(BSP_Serial_MaxReceiveNum,BSP_Serial_MaxOrderLength);
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
	  char c = USART_ReceiveData(USART1);
		BSP_Serial_ReceiveBuffer[BSP_Serial_ReceiveBufferIndex] = c;
		if(c!=0&&c!=10&&c!=13&&BSP_Serial_ReceiveBufferIndex<=BSP_Serial_MaxOrderLength)
		{
			BSP_Serial_ReceiveBufferIndex++;
		}
		else if(BSP_Serial_ReceiveBufferIndex!=0)
		{
			BSP_Serial_ReceiveBuffer[BSP_Serial_ReceiveBufferIndex] = 0;
			BSP_Serial_ReceiveBufferIndex=0;
			if(xQueueSendFromISR(BSP_Serial_ReceiveFIFO,BSP_Serial_ReceiveBuffer,&Receive_TaskSwitch)!=pdTRUE)
			{
				//消息发送失败
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

inline void BSP_Serial_Read(char* orderPtr)
{
	xQueueReceive(BSP_Serial_ReceiveFIFO,orderPtr,portMAX_DELAY);
}

inline void BSP_Serial_Peek(char* orderPtr)
{
	xQueuePeek(BSP_Serial_ReceiveFIFO,orderPtr,portMAX_DELAY);
}


void BSP_Serial_SendChar(char c)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_SendData(USART1,c);
}

void BSP_Serial_SendString(char* stringPtr)
{
	while(true)
	{
		if(*stringPtr!=0)
		{
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
			USART_SendData(USART1,*stringPtr);
			stringPtr++;
		}
		else
		{
			return;
		}
	}
}

void BSP_Serial_SendLength(char* stringPtr,int num)
{
	for(int i=0;i<num;i++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,*stringPtr);
		stringPtr++;
	}
}

void BSP_Serial_SendInt(int num)
{
  int count = num; 
	if(num<0)
	{
		BSP_Serial_SendChar('-');
		count =-num;
	}
	char str[7] ={0,0,0,0,0,0,0};
	str[6]=count%10+'0';
	str[5]=count%100/10+'0';
	str[4]=count%1000/100+'0';
	str[3]=count%10000/1000+'0';
	str[2]=count%100000/10000+'0';
	str[1]=count%1000000/100000+'0';
	str[0]=count/10000000+'0';
	int i=0;
	for(i=0;i<7;i++)
	{
		if(str[i]!='0')
		break;
	}
	BSP_Serial_SendLength(str+i,7-i);
}
