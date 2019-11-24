#include "Encoder_TIM.h"

/*目前以PA0 PA1示范*/
void BSP_Encoder_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		TIM_TimeBaseInitTypeDef TimeBaseInitStruct;
		TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
		TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
		TimeBaseInitStruct.TIM_Period=65530;
		TimeBaseInitStruct.TIM_Prescaler=0;
		TIM_TimeBaseInit(TIM2,&TimeBaseInitStruct);
		
		TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
		
		TIM_ICInitTypeDef TIMICInitStruct;
		TIMICInitStruct.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
		TIMICInitStruct.TIM_ICFilter=0;
		TIMICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
		TIMICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
		TIM_ICInit(TIM2,&TIMICInitStruct);
		
		TIM_Cmd(TIM2,ENABLE);
		
		BSP_Encoder_Reset();
}

int BSP_Encoder_GetCode(void)
{
	int count = TIM_GetCounter(TIM2);
	if(count<3270)
		return count;
	else
	  return -65530+count;
}

void BSP_Encoder_Reset(void)
{
	TIM_SetCounter(TIM2,0);
}
