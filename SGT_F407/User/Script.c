#include "Script.h"

Position position={0,0};

void MoveToward(int orientation, float tileCount)
{
	NewO8LocataorTask(orientation,tileCount);
	while(GetRemainCount()==0)
	{
		//¿ØÖÆ³µÁ¾ÒÆ¶¯
		//SetOrientation(LocalOrientation_X_Positive);
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
	ServerSetAngle(0,SERVER_5);
}

inline void Close(void)
{
	ServerSetAngle(180,SERVER_5);
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
