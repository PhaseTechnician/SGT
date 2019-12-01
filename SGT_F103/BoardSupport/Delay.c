#include "Delay.h"

bool ClockDelayOpen = false;

void BSP_Delay_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	//TIM6 84 000 000 hz
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_Prescaler = 84;
	TimeBase_InitStructure.TIM_Period=65535;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM6,&TimeBase_InitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void BSP_Delay_DelayMs(unsigned int ms)
{
	for(int i=0;i<ms;i++)
	BSP_Delay_DelayUs(1000);
}

void BSP_Delay_DelayUs(unsigned int us)
{
	ClockDelayOpen=true;
	TIM_SetCounter(TIM6,65535-us);
	TIM_Cmd(TIM6,ENABLE);
	while(ClockDelayOpen);
	TIM_Cmd(TIM6,DISABLE);
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET)
	{
		ClockDelayOpen = false;
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}
