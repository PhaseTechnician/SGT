#include "MontorDriver_3PIN.h"

void BSP_MontorDriver_3Pin_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIOInitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIOInitStruct);
	
	GPIOInitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIOInitStruct);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIOInitStruct);
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStruct;
	TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBaseInitStruct.TIM_Period=3000;
	TimeBaseInitStruct.TIM_Prescaler=71;
	TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM8,&TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TimeOCInitStruct;
	TimeOCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TimeOCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TimeOCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	TimeOCInitStruct.TIM_Pulse = 0;
	TimeOCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TimeOCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TimeOCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TimeOCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM8,&TimeOCInitStruct);
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM8,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
	TIM_SetCompare1(TIM8,0);
	TIM_SetCompare2(TIM8,0);
	TIM_SetCompare3(TIM8,0);
	TIM_SetCompare4(TIM8,0);
	
	TIM_Cmd(TIM8,ENABLE);
	
}

void BSP_MontorDriver_3Pin_SetABSSpeed(unsigned int ABSspeed,Montor montor)
{
	switch(montor)
	{
		case MontorFL:
			TIM_SetCompare1(TIM8,ABSspeed);break;
		case MontorFR:
			TIM_SetCompare2(TIM8,ABSspeed);break;
		case MontorBL:
			TIM_SetCompare3(TIM8,ABSspeed);break;
		case MontorBR:
			TIM_SetCompare4(TIM8,ABSspeed);break;
	}
}

void BSP_MontorDriver_3Pin_SetRotation(bool isForward,Montor montor)
{
	switch(montor)
	{
		case MontorFL:
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			break;
		case MontorFR:
			GPIO_SetBits(GPIOC,GPIO_Pin_2);
			GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			break;
		case MontorBL:
			GPIO_SetBits(GPIOC,GPIO_Pin_4);
			GPIO_ResetBits(GPIOC,GPIO_Pin_5);
			break;
		case MontorBR:
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			break;
	}
}

void BSP_MontorDriver_3Pin_SetOutPut(int output,Montor montor)
{
	BSP_MontorDriver_3Pin_SetRotation(output>0,montor);
	BSP_MontorDriver_3Pin_SetABSSpeed(output>0?output:-output,montor);
}

void BSP_MontorDriver_3Pin_Brake(Montor montor)
{
	
}
