#include "Beep.h"

void BSP_Beep_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void BSP_Beep_Enable(bool enable)
{
    if (enable)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_8);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    }
}
