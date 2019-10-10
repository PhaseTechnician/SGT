#include "Test.h"

void DelayAndSYStickTest(void)
{
	while(1)
	{
		char time[3];
		time[0] = GetPartTimeS()%100/10+'0';
		time[1] = GetPartTimeS()%10+'0';
		time[2] = 0;
		USART1Send(time);
		DelayS(1);
	}
}

void USARTTest(void)
{
	USART1Send("stm32f407 try connected");
	while(1)
	{
		if(USART1IsReceive())
		{
			USART1Send(USART1GetOrder());
		}
	}
}

void ServerTest(void)
{
	while(1)
	{
		ServerSetAngle(0,&SERVER1);
		ServerSetAngle(0,&SERVER2);
		ServerSetAngle(0,&SERVER3);
		ServerSetAngle(0,&SERVER4);
		ServerSetAngle(0,&SERVER5);
		DelayS(1);
		ServerSetAngle(180,&SERVER1);
		ServerSetAngle(180,&SERVER2);
		ServerSetAngle(180,&SERVER3);
		ServerSetAngle(180,&SERVER4);
		ServerSetAngle(180,&SERVER5);
		DelayS(1);
	}
}

void LCDTest(void)
{
	LCD12864Write("hello SGT LCD TEST  测试正常");
}

void MontorDriverOutputTest()
{
	SetMontorRotation(true,&MONTOR_FRONT_LEFT);
	SetMontorRotation(true,&MONTOR_FRONT_RIGHT);
	SetMontorRotation(true,&MONTOR_BACK_LEFT);
	SetMontorRotation(true,&MONTOR_BACK_RIGHT);
	while(1)
	{
		for(int i=2000;i<20000;i++)
		{
			SetMontorAbsSpeed(i,&MONTOR_FRONT_LEFT);
			SetMontorAbsSpeed(i,&MONTOR_FRONT_RIGHT);
			SetMontorAbsSpeed(i,&MONTOR_BACK_LEFT);
			SetMontorAbsSpeed(i,&MONTOR_BACK_RIGHT);
			Delay(2000);
		}
		for(int i=20000;i>2000;i--)
		{
			SetMontorAbsSpeed(i,&MONTOR_FRONT_LEFT);
			SetMontorAbsSpeed(i,&MONTOR_FRONT_RIGHT);
			SetMontorAbsSpeed(i,&MONTOR_BACK_LEFT);
			SetMontorAbsSpeed(i,&MONTOR_BACK_RIGHT);
			Delay(2000);
		}
	}
}

void MontorEncoderTest()
{
	int kp=0;
	SetMontorRotation(true,&MONTOR_FRONT_LEFT);
	SetMontorRotation(true,&MONTOR_FRONT_RIGHT);
	SetMontorRotation(true,&MONTOR_BACK_LEFT);
	SetMontorRotation(true,&MONTOR_BACK_RIGHT);
	while(1)
	{
		for(int i=2000;i<20000;i+=10)
		{
			SetMontorAbsSpeed(i,&MONTOR_FRONT_LEFT);
			SetMontorAbsSpeed(i,&MONTOR_FRONT_RIGHT);
			SetMontorAbsSpeed(i,&MONTOR_BACK_LEFT);
			SetMontorAbsSpeed(i,&MONTOR_BACK_RIGHT);
			Delay(20000);
			if(kp==50)
			{
				char str[7] ={0,0,0,0,0,'\n',0};
				unsigned int count = GetEncoderNum(&MONTOR_FRONT_LEFT);
				str[4]=count%10+'0';
				str[3]=count%100/10+'0';
				str[2]=count%1000/100+'0';
				str[1]=count%10000/1000+'0';
				str[0]=count/10000+'0';
				USART1Send(str);
				kp=0;
				ResetEncoderNum();
			}
			kp++;
		}
		DelayS(1);
	}
}

void UltrasonicTest(void)
{
	while(1)
	{
		StartOnceDetecte(&ULT1);
		int distance1 = GetCM(GetDistance(&ULT1));
		/*
		StartOnceDetecte(&ULT2);
		int distance2 = GetCM(GetDistance(&ULT2));
		StartOnceDetecte(&ULT3);
		int distance3 = GetCM(GetDistance(&ULT3));
		StartOnceDetecte(&ULT4);
		int distance4 = GetCM(GetDistance(&ULT4));*/
		char str[6] = {0};
		str[0] = distance1/100+'0';
		str[1] = distance1%100/10+'0';
		str[2] = distance1%10+'0';
		str[3] = '\r';
		str[4] = '\n';
		USART1Send(str);/*
		str[0] = distance2/100+'0';
		str[1] = distance2%100/10+'0';
		str[2] = distance2%10+'0';
		str[3] = '\r';
		str[4] = '\n';
		USART1Send(str);
		str[0] = distance3/100+'0';
		str[1] = distance3%100/10+'0';
		str[2] = distance3%10+'0';
		str[3] = '\r';
		str[4] = '\n';
		USART1Send(str);
		str[0] = distance4/100+'0';
		str[1] = distance4%100/10+'0';
		str[2] = distance4%10+'0';
		str[3] = '\r';
		str[4] = '\n';
		USART1Send(str);*/
		DelayS(1);
	}
}

void SequenceControllerTest(void)
{
	//准备关键帧
	ActionFrame Frame1 = {0,70,24,90};
	ActionFrame Frame2 = {34,140,180,180};
	ActionFrame Frame3 = {140,140,0,0};
	ActionFrame Frame4 = {72,10,50,70};
	ActionFrame Frame5 = {30,140,0,10};
	//为关键帧赋予持续时间
	ActionNode node1 = {&Frame1,1000};
	ActionNode node2 = {&Frame2,1000};
	ActionNode node3 = {&Frame3,1000};
	ActionNode node4 = {&Frame4,1000};
	ActionNode node5 = {&Frame5,1000};
	//组装
	ActionNode actions[7] = {ActionNode_Empty,node1,node2,node3,node4,node5,ActionNode_Empty};
	
	unsigned int ms = 0;
	unsigned int diff = 0;
	while(1)
	{
		ms = GetTotalTimeMs();
		if(IsSequenceFinished())
		{
			USART1Send("FINISH");
			SetSequence(actions);
		}
		SequenceOnStep(diff);
		Delay(10000);
		diff = GetTotalTimeMs() - ms;
	}
}
