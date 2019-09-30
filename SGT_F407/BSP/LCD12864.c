#include "LCD12864.h"
void LCDWrite(unsigned char mode,unsigned char data);
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
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//32极限
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 2;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	CS_low();
	SPI_Cmd(SPI2,ENABLE);
	
	DelayS(1);
	LCDWrite(LCD_MODE_CMD,0X30);
	Delay(1000);
	LCDWrite(LCD_MODE_CMD,0X0C);
	Delay(1000);
	LCDWrite(LCD_MODE_CMD,0X01);
	Delay(30000);
	LCDWrite(LCD_MODE_CMD,0X06);
	Delay(5000);
}

void LCD12864Write(char* str)
{
	LCDWrite(LCD_MODE_CMD,0X80);
	for(int i=0;i<64;i++)
	{
		if(str[i]==0)
		{
			break;
		}
		LCDWrite(LCD_MODE_DATA,str[i]);
	}
}

void LCD12864WriteAt(char* str,int x,int y)
{
	LCDWrite(LCD_MODE_CMD,0X80+x*2+y*16);
	for(int i=0;i<64-x*2+y*16;i++)
	{
		if(str[i]==0)
		{
			break;
		}
		LCDWrite(LCD_MODE_DATA,str[i]);
	}
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
