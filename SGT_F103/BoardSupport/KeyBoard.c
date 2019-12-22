#include "KeyBoard.h"

#ifndef KEY_BOARD_HARD

#include "Delay.h"
#define SCL_H() GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define SCL_L() GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define SDA()   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define SDA_H() GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define SDA_L() GPIO_ResetBits(GPIOB,GPIO_Pin_9)

void BSP_KeyBoard_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	SCL_H();
	SDA_H();
}

inline bool BSP_KeyBoard_IsUp(unsigned char code)
{
	return code&0x40;
}
bool BSP_KeyBoard_IsDown(unsigned char code)
{
	return !code&0x40;
}
unsigned char BSP_KeyBoard_GetCodeName(unsigned char code)
{
	return code&0x2f;
}

void SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void SDA_IN()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void ACK()
{
	SDA_IN();
	SCL_L();
	BSP_Delay_DelayUs(1);
	if(SDA())
	{
		SCL_H();
		BSP_Delay_DelayUs(5);
		SCL_L();
	}
}

void Start()
{
	SDA_OUT();
	SDA_H();
	SCL_H();
	
	SDA_L();
	BSP_Delay_DelayUs(5);
	SCL_L();
	BSP_Delay_DelayUs(5);
}

void Stop()
{
	SDA_OUT();
	SCL_L();
	SDA_L();
	SCL_H();
	BSP_Delay_DelayUs(5);
	SDA_H();
	BSP_Delay_DelayUs(5);
}

void WriteH(void)
{
	SDA_H();
	BSP_Delay_DelayUs(5);
	SCL_H();
	BSP_Delay_DelayUs(5);
	SCL_L();
	BSP_Delay_DelayUs(5);
}

void WriteL(void)
{
	SDA_L();
	BSP_Delay_DelayUs(5);
	SCL_H();
	BSP_Delay_DelayUs(5);
	SCL_L();
	BSP_Delay_DelayUs(5);
}

void WriteByte(unsigned char byte)
{
	SDA_OUT();
	SCL_L();
	for(int i=0;i<8;i++)
	{
		(byte&0x80)?WriteH():WriteL();
		byte<<=1;
	}
}

unsigned char ReadByte()
{
	unsigned char temp = 0X00;
	SDA_IN();
	SCL_L();
	for(int i=0;i<9;i++)
	{
		SCL_H();
		temp<<=1;
		if(SDA())
			temp++;
		BSP_Delay_DelayUs(5);
		SCL_L();
		BSP_Delay_DelayUs(5);
	}
	return temp;
}

unsigned char BSP_KeyBoard_GetCode()
{
	Start();
	WriteByte(0x49);
	ACK();
	unsigned char code = ReadByte();
	ACK();
	Stop();
	return code;
}

#endif
