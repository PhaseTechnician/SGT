#include "Tracker.h"

int PinCount = 0;
unsigned char XYmask=0x00;
inline void TrackerConfig(unsigned char mask)
{
	SetTrackParam(mask,TrackCallBackFunction);
	XYmask=mask;
}

void TrackCallBackFunction(unsigned char trigerPin,bool isRising)
{
	if(!isRising)
	{
		PinCount = Get1BitCount(LineTrackResult&XYmask);
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
			//这里缺乏认真的思考
			TranslateMask = WHEEL_MASK_EMPTY;
		}
		switch(trigerPin)//1PIN或者2PIN
		{
			case PIN1:
			case PIN4:
			case PIN5:
			case PIN8:
				RotateMask = WHEEL_MASK_ANTICLOCK;
				break;
			case PIN2:
			case PIN3:
			case PIN6:
			case PIN7:
				RotateMask = WHEEL_MASK_CLOCK;
				break;
		}
	}
}

inline void TrackModeDisable(void)
{
	SetTrackParam(0X00,TrackCallBackFunction);
}
