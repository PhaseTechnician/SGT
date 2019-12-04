#include "MontorDriver_3PIN.h"

void BSP_MontorDriver_3Pin_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIOInitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIOInitStruct);
	
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
	
	TIM_Cmd(TIM8,ENABLE);
	
}

inline void BSP_MontorDriver_3Pin_SetABSSpeed(unsigned int ABSspeed)
{
	TIM_SetCompare1(TIM8,ABSspeed);
}

void BSP_MontorDriver_3Pin_SetRotation(bool isForward)
{
	
}

void BSP_MontorDriver_3Pin_SetOutPut(int output)
{
	BSP_MontorDriver_3Pin_SetRotation(output>0);
	BSP_MontorDriver_3Pin_SetABSSpeed(output>0?output:-output);
}

void BSP_MontorDriver_3Pin_Brake(void)
{
	
}
