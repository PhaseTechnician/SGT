#include "SerialIO.h"

#define SCLK_H() GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define SCLK_L() GPIO_ResetBits(GPIOB,GPIO_Pin_2)

#define Lock_H() GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define Lock_L() GPIO_ResetBits(GPIOD,GPIO_Pin_2)

#define Read()   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)

void BSP_SerialIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIOInitStruct.GPIO_Pin=GPIO_Pin_2;
    GPIOInitStruct.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&GPIOInitStruct);
    GPIO_Init(GPIOD,&GPIOInitStruct);
    GPIOInitStruct.GPIO_Pin=GPIO_Pin_12;
    GPIO_Init(GPIOC,&GPIOInitStruct);
}

uint8_t BSP_SerialIO_ReadByte(void)
{
}

uint16_t BSP_SerialIO_Read2Bytes(void)
{
}
