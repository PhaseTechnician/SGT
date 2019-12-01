#include "LED.h"

void BSP_LED_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void BSP_LED_Open(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

void BSP_LED_Close(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
