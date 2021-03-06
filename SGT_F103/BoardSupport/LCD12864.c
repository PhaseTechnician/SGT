#include "LCD12864.h"

void LCD12864DrawLogo(void);
void LCDWrite(unsigned char mode,unsigned char data);

#define LCD_MODE_CMD  0xF8
#define LCD_MODE_DATA 0xFA

#define CS_High() GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CS_low() 	GPIO_ResetBits(GPIOB,GPIO_Pin_12)

const unsigned char logo[];
const unsigned char LCDAddress[4]={0x80,0x90,0x88,0x98};

void BSP_LCD12864_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
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
	
	BSP_Delay_DelayMs(500);
	LCDWrite(LCD_MODE_CMD,0X30);
	BSP_Delay_DelayUs(1000);
	LCDWrite(LCD_MODE_CMD,0X0C);
	BSP_Delay_DelayMs(1000);
	LCDWrite(LCD_MODE_CMD,0X01);
	BSP_Delay_DelayUs(30000);
	LCDWrite(LCD_MODE_CMD,0X06);
	BSP_Delay_DelayUs(5000);
	
	BSP_LCD12864_DrawImage(logo);
	BSP_Delay_DelayMs(500);
}

void BSP_LCD12864_Write_EN(char* str)
{
	for(int i=0;i<64;i++)
	{
		if(str[i]==0)
		{
			break;
		}
		if(i%16==0){
			LCDWrite(LCD_MODE_CMD,LCDAddress[i/16]);
		}
		LCDWrite(LCD_MODE_DATA,str[i]);
	}
}

void BSP_LCD12864_WriteAtLine_EN(char* str,int line)
{
	LCDWrite(LCD_MODE_CMD,LCDAddress[line]);
	for(int i=0;i<16;i++)
	{
		if(str[i]==0)
		{
			break;
		}
		LCDWrite(LCD_MODE_DATA,str[i]);
	}
}

void LCD12864WriteAt_EN(char* str,int x,int y)
{
	LCDWrite(LCD_MODE_CMD,LCDAddress[y]+x);
	for(int i=x;i<16-x;i++)
	{
		if(str[i]==0)
		{
			break;
		}
		LCDWrite(LCD_MODE_DATA,str[i]);
	}
}

void BSP_LCD12864_Clear(void)
{
	LCDWrite(LCD_MODE_CMD,0x34);
	LCDWrite(LCD_MODE_CMD,0X36);
	for(unsigned int i=0;i<32;i++)
  {
		LCDWrite(LCD_MODE_CMD,0x80+i); //先送垂直地址
    LCDWrite(LCD_MODE_CMD,0x80);   //再送水平地址，水平地址可自加1
    for(unsigned int j=0;j<16;j++) //每排128个点，所以一共要16个两位16进制数（也就是8位二进制数）才能全部控制
    {
			LCDWrite(LCD_MODE_DATA,0x00);
    }
  }
  for(unsigned int i=0;i<32;i++)     //下半屏的32排操作原理和上半屏一样
  { 
		LCDWrite(LCD_MODE_CMD,0x80+i);
		LCDWrite(LCD_MODE_CMD,0x88); 
    for(unsigned int j=0;j<16;j++)
    {
			LCDWrite(LCD_MODE_DATA,0x00);
    }
  }
	LCDWrite(LCD_MODE_CMD,0x30);
}

void BSP_LCD12864_DrawImage(const unsigned char* image)
{
	LCDWrite(LCD_MODE_CMD,0x34);
	LCDWrite(LCD_MODE_CMD,0X36);
	for(unsigned int i=0;i<32;i++)
  {
		LCDWrite(LCD_MODE_CMD,0x80+i); //先送垂直地址
    LCDWrite(LCD_MODE_CMD,0x80);   //再送水平地址，水平地址可自加1
    for(unsigned int j=0;j<16;j++) //每排128个点，所以一共要16个两位16进制数（也就是8位二进制数）才能全部控制
    {
			LCDWrite(LCD_MODE_DATA,image[j+16*i]);
    }
  }
  for(unsigned int i=0;i<32;i++)     //下半屏的32排操作原理和上半屏一样
  { 
		LCDWrite(LCD_MODE_CMD,0x80+i);
		LCDWrite(LCD_MODE_CMD,0x88); 
    for(unsigned int j=0;j<16;j++)
    {
			LCDWrite(LCD_MODE_DATA,image[j+16*i+32*16]);
    }
  }
	LCDWrite(LCD_MODE_CMD,0x30);
}

void LCDWrite(unsigned char mode,unsigned char data)
{
	CS_High();
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,mode);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,data&0xF0);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,data<<4);
	CS_low();
}

const unsigned char logo[] = {
0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x1F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0x80,0x03,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0x80,0x1F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xC0,0x3F,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xF0,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xE1,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xC3,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xC3,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0x87,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0x07,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0x07,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFE,0x0F,0xE0,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFE,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFE,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x00,0xFC,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0x00,0xFC,0x0E,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xF0,0x00,0x7C,0x0E,0x01,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x78,0x1C,0x3E,0x0E,0x07,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0xFC,0x3E,0x0C,0x1F,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x3F,0xFC,0x1E,0x0C,0x78,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x3F,0xFC,0x07,0x03,0x60,0x1F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x1F,0xFE,0x03,0x8F,0x80,0x0F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x1F,0xFE,0x00,0xFF,0xC0,0x07,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0F,0xFF,0x00,0x7F,0xC0,0x07,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0F,0xFF,0x80,0x1F,0xD8,0x03,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x07,0xFF,0x80,0x0F,0xDE,0x03,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0xFF,0xC0,0x07,0x8F,0x81,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0xFF,0xF0,0x30,0x07,0xC1,0xFF,0xF0,0x7F,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0xE1,0x83,0xE0,0xFF,0xF0,0x78,0x70,0x38,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xFF,0xC1,0x81,0xF0,0xE1,0xF0,0x78,0x70,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0xFF,0x01,0xC1,0xF8,0xC0,0x78,0x7F,0xFF,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0xF8,0x01,0x81,0xF8,0x00,0x38,0x07,0xF7,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x81,0xF8,0x00,0x1C,0x07,0xF7,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x03,0x81,0xFC,0x00,0x00,0x7F,0xFF,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x07,0x81,0xFC,0x00,0x00,0x7F,0xFF,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x0F,0x81,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xC0,0x3F,0x83,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xFF,0x03,0xFE,0x7F,0x83,0xFF,0xEF,0x83,0xE0,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xFF,0x07,0xFE,0x7F,0xC3,0xFF,0xE7,0xC7,0xE0,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xFF,0x0F,0xFE,0x7F,0xC3,0xE0,0x07,0xC7,0xC0,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xFE,0x0F,0xFE,0x7F,0xE3,0xE0,0x07,0xC7,0xC0,0x00,0x00,
0x00,0x00,0x00,0x03,0xFF,0xFC,0x1F,0xFC,0xFF,0xE3,0xE0,0x03,0xEF,0xC0,0x00,0x00,
0x00,0x00,0x00,0x07,0xFF,0xF8,0x3F,0xFC,0xFB,0xE3,0xE0,0x03,0xEF,0x80,0x00,0x00,
0x00,0x00,0x00,0x1F,0xFF,0xF0,0x3F,0xFC,0xFB,0xE3,0xFF,0x83,0xEF,0x80,0x00,0x00,
0x00,0x00,0x00,0x7F,0xFF,0xE0,0x0F,0xF8,0xFB,0xE3,0xFF,0xE1,0xFF,0x80,0x00,0x00,
0x00,0x00,0x01,0xFF,0xFF,0x80,0x07,0xF8,0xFF,0xF3,0xFF,0xE1,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xFC,0x00,0x07,0xF0,0xFF,0xF3,0xE3,0xE1,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xF1,0xF1,0xF3,0xE3,0xE0,0xFE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE1,0xF1,0xF3,0xE3,0xE0,0xFE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE1,0xF1,0xF3,0xE3,0xE0,0xFE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC1,0xF1,0xFB,0xFF,0xE0,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x81,0xF0,0xFB,0xFF,0xE0,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


