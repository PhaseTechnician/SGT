#include "LCD12864.h"
void LCDWrite(unsigned char mode,unsigned char data);
void LCD12864DrawLogo(void);
#define LCD_MODE_CMD  0b11111000
#define LCD_MODE_DATA 0b11111010

#define CS_High() GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CS_low() GPIO_ResetBits(GPIOB,GPIO_Pin_12)

const unsigned char logo[];
/*
const unsigned char num0[];
const unsigned char num1[];
const unsigned char num2[];
const unsigned char num3[];*/

const unsigned char num0[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x01,0xC0,0x00,
0x00,0x01,0xC0,0x00,0x00,0x01,0xC0,0x00,0x00,0x31,0xC6,0x00,0x00,0x7F,0xFF,0x00,
0x00,0x0F,0xF8,0x00,0x00,0x03,0xE0,0x00,0x00,0x03,0x60,0x00,0x00,0x06,0x30,0x00,
0x00,0x0E,0x38,0x00,0x00,0x1C,0x1C,0x00,0x00,0x0C,0x18,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};

//const unsigned char num1[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xF0,0x00,
0x00,0x07,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};

//const unsigned char num2[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xE0,0x00,0x00,0x3F,0xF8,0x00,
0x00,0x7F,0xFC,0x00,0x00,0xFF,0xFE,0x00,0x01,0xFF,0xFE,0x00,0x01,0xFF,0xFF,0x00,
0x03,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0x00,0x03,0xF8,0x7F,0x80,0x03,0xF8,0x7F,0x80,
0x03,0xFC,0xFF,0x00,0x03,0xF8,0xFF,0x00,0x01,0xF9,0xFF,0x00,0x01,0xF1,0xFE,0x00,
0x00,0xF3,0xFE,0x00,0x00,0x63,0xFC,0x00,0x00,0x27,0xFC,0x00,0x00,0x07,0xF8,0x00,
0x00,0x0F,0xF8,0x00,0x00,0x0F,0xFF,0x80,0x00,0x1F,0xFF,0x80,0x00,0x1F,0xFF,0x80,
0x00,0x3F,0xFF,0x80,0x00,0x7F,0xFF,0x80,0x00,0x7F,0xFF,0x80,0x00,0xFF,0xFF,0x80,
0x00,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};

//const unsigned char num3[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x00,0x00,0x3F,0xFF,0x00,
0x00,0x3F,0xFE,0x00,0x00,0x3F,0xFE,0x00,0x00,0x3F,0xFE,0x00,0x00,0x3F,0xFC,0x00,
0x00,0x3F,0xFC,0x00,0x00,0x3F,0xF8,0x00,0x00,0x07,0xF8,0x00,0x00,0x07,0xF8,0x00,
0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF8,0x00,0x00,0x0F,0xFC,0x00,0x00,0x07,0xFE,0x00,
0x00,0x01,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,
0x00,0x00,0xFF,0x80,0x00,0x21,0xFF,0x00,0x00,0x3F,0xFF,0x00,0x00,0x3F,0xFF,0x00,
0x00,0x3F,0xFF,0x00,0x00,0x3F,0xFE,0x00,0x00,0x3F,0xFC,0x00,0x00,0x3F,0xF8,0x00,
0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

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
	
	LCD12864DrawLogo();
	DelayS(1);
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

/*
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
}*/

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

void LCD12864DrawLogo(void)
{
	LCDWrite(LCD_MODE_CMD,0x34);
	LCDWrite(LCD_MODE_CMD,0X36);
	for(unsigned int i=0;i<32;i++)
  {
		LCDWrite(LCD_MODE_CMD,0x80+i); //先送垂直地址
    LCDWrite(LCD_MODE_CMD,0x80);   //再送水平地址，水平地址可自加1
    for(unsigned int j=0;j<16;j++) //每排128个点，所以一共要16个两位16进制数（也就是8位二进制数）才能全部控制
    {
			LCDWrite(LCD_MODE_DATA,logo[j+16*i]);
    }
  }
  for(unsigned int i=0;i<32;i++)     //下半屏的32排操作原理和上半屏一样
  { 
		LCDWrite(LCD_MODE_CMD,0x80+i);
		LCDWrite(LCD_MODE_CMD,0x88); 
    for(unsigned int j=0;j<16;j++)
    {
			LCDWrite(LCD_MODE_DATA,logo[j+16*i+32*16]);
    }
  }
	LCDWrite(LCD_MODE_CMD,0x30);
}

void LCD12864NumDraw(int num1,int num2)
{
	int nums[8] ={
	num1/100,
	num1%100/10,
	num1%10,
	0,
	num2/100,
	num2%100/10,
	num2%10,
	0,
	};
	
	LCDWrite(LCD_MODE_CMD,0x34);
	LCDWrite(LCD_MODE_CMD,0X36);
	for(unsigned int i=0;i<32;i++)
  {
		LCDWrite(LCD_MODE_CMD,0x80+i); //先送垂直地址
    LCDWrite(LCD_MODE_CMD,0x80);   //再送水平地址，水平地址可自加1
    for(unsigned int j=0;j<16;j++) //每排128个点，所以一共要16个两位16进制数（也就是8位二进制数）才能全部控制
    {
			LCDWrite(LCD_MODE_DATA,num0[j%4+4*i+nums[j/4]*4*32]);
		/*
			if(nums[j/4]==0)
			{
				LCDWrite(LCD_MODE_DATA,num0[j%4+4*i]);
			}
			else if(nums[j/4]==1)
			{
				LCDWrite(LCD_MODE_DATA,num1[j%4+4*i]);
			}
			else if(nums[j/4]==2)
			{
				LCDWrite(LCD_MODE_DATA,num2[j%4+4*i]);
			}
			else
			{
				LCDWrite(LCD_MODE_DATA,num3[j%4+4*i]);
			}*/
    }
  }
  for(unsigned int i=0;i<32;i++)     //下半屏的32排操作原理和上半屏一样
  { 
		LCDWrite(LCD_MODE_CMD,0x80+i);
		LCDWrite(LCD_MODE_CMD,0x88); 
    for(unsigned int j=0;j<16;j++)
    {
			LCDWrite(LCD_MODE_DATA,num0[j%4+4*i+nums[j/4+4]*4*32]);
			/*
			if(nums[j/4]==0)
			{
				LCDWrite(LCD_MODE_DATA,num0[j%4+4*i]);
			}
			else if(nums[j/4]==1)
			{
				LCDWrite(LCD_MODE_DATA,num1[j%4+4*i]);
			}
			else if(nums[j/4]==2)
			{
				LCDWrite(LCD_MODE_DATA,num2[j%4+4*i]);
			}
			else
			{
				LCDWrite(LCD_MODE_DATA,num3[j%4+4*i]);
			}*/
    }
  }
	LCDWrite(LCD_MODE_CMD,0x30);
}


const unsigned char logo[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0xFC,0x03,0xFE,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,
0x00,0x00,0x40,0x04,0x07,0xFE,0x00,0x7F,0xFF,0xFF,0xFF,0xFC,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x0F,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x1F,0xFE,0x01,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x3F,0xFE,0x03,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x3F,0xFE,0x07,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0xFC,0x7F,0xFE,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x7F,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xF8,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x7F,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,0xF8,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x7F,0xE2,0x0F,0xFF,0x0F,0xFF,0xFF,0xF8,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x7F,0xE0,0x1F,0xFE,0x02,0x07,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x7F,0xF0,0x1F,0xFC,0xFF,0x87,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x7F,0xF0,0x1F,0xF8,0xFF,0xC7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x3F,0xF8,0x1F,0xF8,0xFF,0xE7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x3F,0xF8,0x1F,0xF8,0xFF,0xE7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x3F,0xFC,0x1F,0xF8,0xFF,0xE7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x80,0x1F,0xFC,0x1F,0xFC,0xFF,0xF7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0x1F,0xFC,0x1F,0xFF,0xFF,0xF7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xCF,0xFC,0x0F,0xFF,0xFF,0xF7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xFC,0x0F,0xFF,0xFF,0xF7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xFC,0x0F,0xFF,0xFF,0xF7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xFC,0x07,0xFF,0xFF,0xF7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xF8,0x07,0xFF,0xFF,0xE7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xF8,0x03,0xFF,0xFF,0xE7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xF0,0x01,0xFF,0xFF,0xC7,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0x81,0xFF,0xE0,0x00,0xFF,0xFF,0x87,0xFE,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x40,0xFD,0xFF,0xE0,0x00,0x7F,0xFF,0x07,0xFE,0x07,0xE0,0x20,0x00,0x00,
0x00,0x00,0x40,0x05,0xFF,0x80,0x00,0x1F,0xFE,0x07,0xFE,0x04,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x7E,0x00,0x00,0x07,0xF8,0x00,0x00,0x04,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x00,
0x00,0x00,0x40,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x00,
0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xE0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


