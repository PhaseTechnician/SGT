#include "LEDMX7219.h"

 #define DECODE_MODE 0X09
 #define INTENSITY   0x0A
 #define SCAN_LIMIT  0x0B
 #define SHUT_DOWN   0x0C
 #define TEST        0x0F

#define CS_High() GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CS_low() GPIO_ResetBits(GPIOB,GPIO_Pin_12)

void SPI2Write(unsigned char address,unsigned char data);

void LEDMX7219Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//[]
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 2;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	CS_High();
	SPI_Cmd(SPI2,ENABLE);
	
	DelayS(1);
	
	
	SPI2Write(DECODE_MODE,0X00);
	SPI2Write(INTENSITY,0x03);
	SPI2Write(SCAN_LIMIT,0X07);
	SPI2Write(SHUT_DOWN,0X01);
	SPI2Write(TEST,0x00);
	
	Delay(2000);
	
	SPI2Write(0x01,0x00);
	Delay(2000);
	SPI2Write(0x02,0xff);
}

void SPI2Write(unsigned char address,unsigned char data)
{
	CS_low();
	while(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);
	SPI_SendData(SPI2,address);
	while(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);
	SPI_SendData(SPI2,data);
	while(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);
	CS_High();
}

void LEDWrite(int num1,int num2)
{
	
}
