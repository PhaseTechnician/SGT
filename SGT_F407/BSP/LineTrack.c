#include "LineTrack.h"

unsigned char LineTrackResult;

void LineTrackConfig(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC,ENABLE);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource1|EXTI_PinSource2|EXTI_PinSource3|EXTI_PinSource4|EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource6|EXTI_PinSource7|EXTI_PinSource8);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //���� 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI1_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
	{
		LineTrackResult &= 0b11111110;
	}
	else
	{
		LineTrackResult |= 0b00000001;
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
void EXTI2_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
	{
		LineTrackResult &= 0b11111101;
	}
	else
	{
		LineTrackResult |= 0b00000010;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}
void EXTI3_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
	{
		LineTrackResult &= 0b11111011;
	}
	else
	{
		LineTrackResult |= 0b00000100;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}
void EXTI4_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))
	{
		LineTrackResult &= 0b11110111;
	}
	else
	{
		LineTrackResult |= 0b00001000;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5))
		{
			LineTrackResult &= 0b11101111;
		}
		else
		{
			LineTrackResult |= 0b00010000;
		}
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	else if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6))
		{
			LineTrackResult &= 0b11011111;
		}
		else
		{
			LineTrackResult |= 0b00100000;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	else if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		{
			LineTrackResult &= 0b10111111;
		}
		else
		{
			LineTrackResult |= 0b0100000;
		}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	else if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))
		{
			LineTrackResult &= 0b01111111;
		}
		else
		{
			LineTrackResult |= 0b10000000;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}

