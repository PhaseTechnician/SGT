#include "MontorDriver_3PIN.h"

//TIM1 CH1 PA8ÎªÀý
void BSP_MontorDriver_L298_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIOInitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIOInitStruct);
	GPIOInitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOA,&GPIOInitStruct);
	
	TIM_TimeBaseInitTypeDef TimeBaseInitStruct;
	TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TimeBaseInitStruct.TIM_Period=0;
	TimeBaseInitStruct.TIM_Prescaler=0;
	TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TimeOCInitStruct;
	TimeOCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TimeOCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TimeOCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	TimeOCInitStruct.TIM_Pulse = 0;
	TimeOCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TimeOCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TimeOCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TimeOCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1,&TimeOCInitStruct);
	
	TIM_OC1PreloadConfig(TIM1,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
}