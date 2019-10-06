#include "Locataor.h"

int LocataorCountRising = 0;
int LocataorCountFalling = 0;

inline void LocatorConfig(unsigned char mask)
{
	SetTrackParam(mask,LocatorCallBackFunction);
}

void LocatorCallBackFunction(unsigned char trigerPin,bool isRising)
{
	//单一管计数模式
	if(isRising)
	{
		LocataorCountRising++;
	}
	else
	{
		LocataorCountFalling--;
	}
}

inline void LocatorModeDisable(void)
{
	SetTrackParam(0X00,LocatorCallBackFunction);
}



/* 对管模式的判断

#define BIT_CONTANT(mask,pin) (mask&pin)

#define CPMaskXP 0b00000011
#define CPMaskYP 0b00010100
#define CPMaskXN 0b11000000
#define CPMaskYN 0b00101000

#define HighMask 0b00010111
#define LowMask  0b11101000

#define AnotherPinInCP(pin,CP) (CP&(!pin))
unsigned char getMask(unsigned char pin);
#define CPMask(pin) getMask(pin)
#define IsHigh(pin) (HighMask&pin)
#define IsLow(pin) (LowMask&pin)
unsigned char TrigPinMemory = 0;

unsigned char getMask(unsigned char pin)
{
	if(BIT_CONTANT(CPMaskXP,pin))
		return CPMaskXP;
	else if(BIT_CONTANT(CPMaskXN,pin))
		return CPMaskXN;
	else if(BIT_CONTANT(CPMaskYP,pin))
		return CPMaskYP;
	else
		return CPMaskYN;
}

	if(isRising)
		return;//暂时不处理上升沿
	if(BIT_CONTANT(XMask,trigerPin))
	{
		TrigPinMemory |= trigerPin;
		unsigned char CPmask = CPMask(trigerPin);
		if(BIT_CONTANT(TrigPinMemory,AnotherPinInCP(trigerPin,CPmask)))//对应组内的另一个引脚已经被触发
		{
			if(IsHigh(trigerPin))
			{
				XCoordinate--;
			}
			else
			{
				XCoordinate++;
			}
			TrigPinMemory &= (!CPmask);
		}
	}
	else
	{
		TrigPinMemory |= trigerPin;
		unsigned char CPmask = CPMask(trigerPin);
		if(BIT_CONTANT(TrigPinMemory,AnotherPinInCP(trigerPin,CPmask)))//对应组内的另一个引脚已经被触发
		{
			if(IsHigh(trigerPin))
			{
				YCoordinate--;
			}
			else
			{
				YCoordinate++;
			}
			TrigPinMemory &= (!CPmask);
		}
	}
*/
