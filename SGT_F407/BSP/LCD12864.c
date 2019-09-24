#include "LCD12864.h"

#define LCD_MODE_CMD  0b11111000
#define LCD_MODE_DATA 0b11111010

#define CS_High() GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CS_low() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
void LCD12864Config(void)
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
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//[]
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;//32极限
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 2;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	CS_low();
	SPI_Cmd(SPI2,ENABLE);
	
	LCDWrite(LCD_MODE_CMD,0b00101011);
	LCDWrite(LCD_MODE_CMD,0b00101011);
	LCDWrite(LCD_MODE_CMD,0b00101011);
	LCDWrite(LCD_MODE_DATA,0b00111111);
	LCDWrite(LCD_MODE_DATA,0b00111111);
	LCDWrite(LCD_MODE_DATA,0b00111111);
}

void LCDWrite(unsigned char mode,unsigned char data)
{
	CS_High();
	while(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);
	SPI_SendData(SPI2,mode);
	while(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);
	SPI_SendData(SPI2,data&0xF0);
	while(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);
	SPI_SendData(SPI2,data<<4);
	CS_low();
}
