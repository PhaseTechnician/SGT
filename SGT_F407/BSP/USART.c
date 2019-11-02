#include "USART.h"

#define MaxLengthOfOrder 1
#define MaxAmountOfOrder 10

char orders[MaxAmountOfOrder][MaxLengthOfOrder+1]={0};
unsigned int startIndex=0;
unsigned int endIndex=0;
unsigned int orderInnerIndex = 0;

void USART1Config(int baud)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
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
}


void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
	  char c = USART_ReceiveData(USART1);
		if(c==' ')//指令分割字符[单字符指令模式]
		{
			orders[endIndex][orderInnerIndex]=0;
			endIndex++;
			orderInnerIndex = 0;
		}
		else
		{
		orders[endIndex][orderInnerIndex]=c;
			orderInnerIndex++;
			if(orderInnerIndex==MaxLengthOfOrder)
			{
				orders[endIndex][orderInnerIndex]=0;
				endIndex++;//超过预定的指令长度，指令直接截断
				orderInnerIndex = 0;
			}
		}
		if(endIndex==MaxAmountOfOrder)
		{
			endIndex=0;
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

void USART1SendChar(char c)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	USART_SendData(USART1,c);
}

void USART1Send(char* stringPtr)
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

void USART1SendLength(char* stringPtr,int num)
{
	for(int i=0;i<num;i++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,*stringPtr);
		stringPtr++;
	}
}

void USART1SendNumInt(int num)
{
  int count = num; 
	if(num<0)
	{
		USART1SendChar('-');
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
	USART1SendLength(str+i,7-i);
}

inline bool USART1IsReceive(void)
{
	return startIndex != endIndex;
}
char* USART1GetOrder(void)
{
  char* order = orders[startIndex];
	startIndex++;
	if(startIndex==MaxAmountOfOrder)
	{
			startIndex=0;
	}
	return order;
}

void USART1ClearReceive(void)
{
	startIndex=0;
	endIndex=0;
}
