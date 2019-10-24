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

void InitStartMotion(void)
{
	ServerSetAngle(0,&SERVER1);
	ServerSetAngle(0,&SERVER2);
	ServerSetAngle(0,&SERVER3);	
	ServerSetAngle(0,&SERVER4);
	ServerSetAngle(0,&SERVER5);
}

inline void StartMotion(ActionNode actions[])
{
	SetSequence(actions);
}

void WaitMotion(unsigned int waitTimeMs)
{
	unsigned int startTime = GetTotalTimeMs();
	while(!IsSequenceFinished()&&(startTime>GetTotalTimeMs()-waitTimeMs));
}

inline void Open(void)
{
	ServerSetAngle(0,&SERVER5);
}

inline void Close(void)
{
	ServerSetAngle(180,&SERVER5);
}

bool TryConnectedPi(int waitTimes)
{
	USART1ClearReceive();
	USART1Send("<PI>");
	unsigned int SendOrderTime = GetTotalTimeMs();
	while(!USART1IsReceive()&&(GetPartTimeMs()<SendOrderTime+waitTimes));
	if(USART1IsReceive())
	{
		char* resultOrder = USART1GetOrder();
		if(resultOrder[1]=='P'&&resultOrder[2]=='I')
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool ScanQRcode(char* Result6char,int times)
{
	unsigned int timeCount = 0;
	unsigned int SendOrderTime = 0;
	USART1ClearReceive();
	while(true)
	{
		USART1Send("<QR>");
		SendOrderTime = GetPartTimeMs();
		while(!USART1IsReceive()&&(GetPartTimeMs()<SendOrderTime+500));//�ȴ��ĺ�����
		if(USART1IsReceive())
		{
			char* temp = USART1GetOrder();
			for(int i=0;i<6;i++)
			{
				Result6char[i] = temp[i];
			}
			return true;
		}
		else
		{
			timeCount++;
		}
		if(timeCount>=times)
		{
			return false;
		}
	}
}

bool IsColor(int waitTimes,const char* color)
{
	USART1ClearReceive();
	USART1Send((char*)color);
	unsigned int SendOrderTime = GetTotalTimeMs();
	while(!USART1IsReceive()&&(GetPartTimeMs()<SendOrderTime+waitTimes));
	if(USART1IsReceive())
	{
		char* resultOrder = USART1GetOrder();
		if(resultOrder[1]=='y')
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool PeekGoods(char* Result3Char,int waitTimes)
{
	USART1ClearReceive();
	USART1Send("PE");
	unsigned int SendOrderTime = GetTotalTimeMs();
	while(!USART1IsReceive()&&(GetPartTimeMs()<SendOrderTime+waitTimes));
	if(USART1IsReceive())
	{
		char* resultOrder = USART1GetOrder();
		for(int i=0;i<3;i++)
		{
			Result3Char[i] = resultOrder[i];
		}
		return true;
	}
	else
	{
		return false;
	}
}

void GetSport(void)
{
	USART1ClearReceive();
	USART1Send("SP");
}
