#include "Script.h"

Position position={0,0};

void MoveToward(unsigned char orientation,int tileCount)
{
	switch(orientation)
	{
		case WHEEL_MASK_CLOCK:
			break;//... ÉèÖÃTRACKER
	}
	while(true)
	{
		MotionAnalysisOnStep();
		if(LocataorCountFalling>5)
		{
			break;
		}
	}
}

void Stop(void)
{
	SetMontorSpeed(0,MONTOR_FRONT_RIGHT);
	SetMontorSpeed(0,MONTOR_FRONT_LEFT);
	SetMontorSpeed(0,MONTOR_BACK_RIGHT);
	SetMontorSpeed(0,MONTOR_BACK_LEFT);
}

inline void Open(void)
{
	ServerSetAngle(0,&SERVER5);
}

inline void Close(void)
{
	ServerSetAngle(180,&SERVER5);
}

void ScanQRcode(void)
{
	USART1Send("QR");
}

void PeekGoods(void)
{
	USART1Send("PE");
}

void GetSport(void)
{
	USART1Send("SP");
}
