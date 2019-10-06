#include "Tracker.h"

int PinCount = 0;

inline void TrackerConfig(unsigned char mask)
{
	SetTrackParam(mask,TrackCallBackFunction);
	PinCount = Get1BitCount(LineTrackResult&mask);
}

void TrackCallBackFunction(unsigned char trigerPin,bool isRising)
{
	if(isRising)
	{
		PinCount--;
	}
	else
	{
		PinCount++;
		if(PinCount==0)
		{
			TranslateMask = WHEEL_MASK_EMPTY;
		}
		else if(PinCount==2)
		{
			if(LT1&&LT7)
			{
				TranslateMask = WHEEL_MASK_LEFT;
				return;
			}
			else if(LT2&&LT8)
			{
				TranslateMask = WHEEL_MASK_RIGHT;
				return;
			}
			else if(LT3&&LT4)
			{
				TranslateMask = WHEEL_MASK_FORWARD;
				return;
			}
			else if(LT5&&LT6)
			{
				TranslateMask = WHEEL_MASK_BACKWARD;
				return;
			}
		}
		switch(trigerPin)
		{
			case PIN1:
			case PIN4:
			case PIN5:
			case PIN8:
				TranslateMask = WHEEL_MASK_ANTICLOCK;
				break;
			case PIN2:
			case PIN3:
			case PIN6:
			case PIN7:
				TranslateMask = WHEEL_MASK_CLOCK;
				break;
		}
	}
}

inline void TrackModeDisable(void)
{
	SetTrackParam(0X00,TrackCallBackFunction);
}
