#include "LED.h"

#define BIT_1 0x01
#define BIT_2 0x02
#define BIT_3 0x03
#define BIT_4 0x04
#define BIT_5 0x05
#define BIT_6 0x06
#define BIT_7 0x07
#define BIT_8 0x08
#define DECODE_MODE 0x09
#define INTENSITY 0x0A
#define SCAN_LIMIT 0x0B
#define SHUT_DOWN 0x0C
#define TEST 0x0F

#define DIN_High() GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define DIN_Low()  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
#define DIN(HL) GPIO_WriteBit(GPIOB,GPIO_Pin_0,HL);
#define CS_High() GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define CS_Low()  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
#define CLK_High() GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define CLK_Low()  GPIO_ResetBits(GPIOB,GPIO_Pin_2);

void LedConfig(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

void WriteToMax7219(unsigned char address,unsigned char data)
{
	uint16_t value = address<<8|data;
	CS_Low();
	CLK_Low();
	for(int i=0;i<16;i++)
	{
		CLK_Low();
		DIN(value&0x8000);
		value<<=1;
		CLK_High();
		//delay();
	}
	CLK_Low();
	CS_High();
}

void SetLedBit(int num,int bit)
{
	
}

void SetLed(int firstNum,int SecondNum)
{
	
}