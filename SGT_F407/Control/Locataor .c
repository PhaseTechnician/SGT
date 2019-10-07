#include "Locataor.h"

int HighPinCount = 0;
int LowPinCount  = 0;

inline void LocatorConfig(unsigned char mask)
{
	SetTrackParam(mask,LocatorCallBackFunction);
	LocataorReset();
}

void LocatorCallBackFunction(unsigned char trigerPin,bool isRising)
{
	if(!isRising)//下降沿
	{
		if(MASK_CONTANT_BIT(HighMask,trigerPin))
		{
			HighPinCount++;
		}
		else
		{
			LowPinCount++;
		}
	}
	else//上升沿
	{
		
	}
}

inline void LocatorModeDisable(void)
{
	SetTrackParam(0X00,LocatorCallBackFunction);
}

void LocataorReset(void)
{
	HighPinCount = 0;
	LowPinCount = 0;
}

inline unsigned char GetLowPinInCp(unsigned char CPMask)
{
	return CPMask&LowMask;
}

inline unsigned char GetHighPinInCp(unsigned char CPMask)
{
	return CPMask&HighMask;
}

/* 对管模式的判断

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
