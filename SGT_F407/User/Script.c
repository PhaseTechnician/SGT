#include "Script.h"

Position position={0,0};
unsigned char LOWPIN;
unsigned char HIGHPIN;
void MoveToward(unsigned char orientation,int tileCount)
{
	//���ٶȷ���ʹ�С������
	MoveMask = orientation;
	MoveSpeedFactor = 10;
	//�����������Ѳ����//�Ͷ�λ��
	switch(orientation)
	{
		case WHEEL_MASK_FORWARD:
		case WHEEL_MASK_BACKWARD:
			TrackerConfig(XMask);
			LocatorConfig(CPMaskYP);
			LOWPIN = GetLowPinInCp(CPMaskYP);
			HIGHPIN = GetHighPinInCp(CPMaskYP);
			break;//... ����TRACKER
		case WHEEL_MASK_LEFT:
		case WHEEL_MASK_RIGHT:
			TrackerConfig(YMask);
			LocatorConfig(CPMaskXP);
			LOWPIN = GetLowPinInCp(CPMaskXP);
			HIGHPIN = GetHighPinInCp(CPMaskXP);
			break;
	}
	Delay(20000);//ʹ�ô����������ʼʱ��֮�ڵĲ�ȷ�����
	LocataorReset();
	
	while(true)
	{
		if(HighPinCount==tileCount)
		{
			if(LowPinCount!=HighPinCount)
			{
				//�˳�
				MoveMask = !orientation;
				while(!LINE_TRACK_RESUT(LOWPIN));
			}
			break;
		}
	}
	//�ۼӵ�λ������
	switch(orientation)
	{
		case WHEEL_MASK_FORWARD:
			position.x += tileCount;
			break;
		case WHEEL_MASK_BACKWARD:
			position.x -= tileCount;
			break;
		case WHEEL_MASK_LEFT:
			position.y += tileCount;
			break;
		case WHEEL_MASK_RIGHT:
			position.y -= tileCount;
			break;
	}
}

void Stop(void)
{
	SetMontorSpeed(0,&MONTOR_FRONT_RIGHT);
	SetMontorSpeed(0,&MONTOR_FRONT_LEFT);
	SetMontorSpeed(0,&MONTOR_BACK_RIGHT);
	SetMontorSpeed(0,&MONTOR_BACK_LEFT);
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
