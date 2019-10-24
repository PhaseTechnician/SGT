#include "LineTrack.h"

unsigned char LineTrackResultLast=0xff;
unsigned char LineTrackResult=0xff;
bool enableLineTrackChangeSend=false;
void (*AnchorCallBack)(unsigned char trigerPin,bool isrising) = 0;
void (*TrackCallBack)(unsigned char trigerPin,bool isrising) = 0;
unsigned char AnchorMask = 0;
unsigned char TrackMask = 0;

#define BIT_CONTANT(mask,pin) (mask&pin) 

void LineTrackConfig(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

bool LineTrackEnable(bool enable)
{
	enableLineTrackChangeSend = false;/*
	if(AnchorMask!=0&&AnchorCallBack==0)
		return false;*/
	if(TrackMask!=0&&TrackCallBack==0)
		return false;
	enableLineTrackChangeSend = enable;
	return true;
}

void DistributeMassage(unsigned char trigerPin,bool isRising)
{
	if(BIT_CONTANT(AnchorMask,trigerPin))
	{
		AnchorCallBack(trigerPin,isRising);
	}
	else if(BIT_CONTANT(TrackMask,trigerPin))
	{
		TrackCallBack(trigerPin,isRising);
	}
}

void SetAnchorParam(unsigned char mask,void (*CallBack)(unsigned char trigerPin,bool isrising))
{
	AnchorMask = mask;
	AnchorCallBack = CallBack;
}

void SetTrackParam(unsigned char mask,void (*CallBack)(unsigned char trigerPin,bool isrising))
{
	TrackMask = mask;
	TrackCallBack = CallBack;
}

int Get1BitCount(unsigned char OBvalue)
{
	int count = 0;
	for(int i=0;i<8;i++)
	{
		if(OBvalue&0x80)
			count++;
		OBvalue<<=1;
	}
	return count;
}

unsigned char directReadLineTrackResult()
{
	unsigned char valueB = GPIO_ReadInputData(GPIOB)>>1;
	unsigned char valueC = GPIO_ReadInputData(GPIOC)>>1;
	return (valueC&0b00011111)|(valueB&0b11100000);
}

void CriticalDigitalLevelChange(void)
{
	LineTrackResultLast = LineTrackResult;
	LineTrackResult = ~directReadLineTrackResult();//决定是否反码
	unsigned char changePin = LineTrackResult^LineTrackResultLast;
	if(changePin&&enableLineTrackChangeSend)
	{
		for(int i=0;i<8;i++)//[0/7]
		{
			if(changePin&(1<<i))
			{
				DistributeMassage(1<<i,LineTrackResult&(1<<i)?true:false);
			}
		}
	}
}
