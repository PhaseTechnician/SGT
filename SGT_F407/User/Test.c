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

void ServerTest(char mode)
{
	if(mode=='N')
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
	else if(mode=='0')
	{
		ServerSetAngle(90,&SERVER1);
		ServerSetAngle(90,&SERVER2);
		ServerSetAngle(90,&SERVER3);
		ServerSetAngle(90,&SERVER4);
		ServerSetAngle(90,&SERVER5);
	}
	else if(mode=='C')
	{
		while(1)
		{
			if(USART1IsReceive())
			{
				char *c = USART1GetOrder();
				if(c[0]=='1')
				{
					ServerSetAngle((c[1]-'0')*100+(c[2]-'0')*10+(c[3]-'0'),&SERVER1);
					USART1Send("SERVER1\r\n");
				}
				else if(c[0]=='2')
				{
					ServerSetAngle((c[1]-'0')*100+(c[2]-'0')*10+(c[3]-'0'),&SERVER2);
					USART1Send("SERVER2\r\n");
				}
				else if(c[0]=='3')
				{
					ServerSetAngle((c[1]-'0')*100+(c[2]-'0')*10+(c[3]-'0'),&SERVER3);
					USART1Send("SERVER3\r\n");
				}
				else if(c[0]=='4')
				{
					ServerSetAngle((c[1]-'0')*100+(c[2]-'0')*10+(c[3]-'0'),&SERVER4);
					USART1Send("SERVER4\r\n");
				}
				else if(c[0]=='5')
				{
					ServerSetAngle((c[1]-'0')*100+(c[2]-'0')*10+(c[3]-'0'),&SERVER5);
					USART1Send("SERVER5\r\n");
				}
			}
		}
	}
}

void LCDTest(void)
{ 
	LCD12864Write("hello SGT LCD TEST  测试正常");
}

void LineTrackTest(void)
{/*
	if(LineTrackEnable(true))
	{
		USART1Send("init LT Finish");
	}*/
	while(1)
	{
		DelayMs(100);
		LineTrackResult=directReadLineTrackResult();
		char state[9]={0};
		state[0] = LT1+'0';
		state[1] = LT2+'0';
		state[2] = LT3+'0';
		state[3] = LT4+'0';
		state[4] = LT5+'0';
		state[5] = LT6+'0';
		state[6] = LT7+'0';
		state[7] = LT8+'0';
		state[8]= '\n';
		USART1SendLength(state,9);
	}
}

void MontorDriverOutputTest(char c)
{
	if(c=='N')
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
	else if(c=='C')
	{
		while(1)
		{
			if(USART1IsReceive())
			{
				char c = *USART1GetOrder();
				switch(c)
				{
					case 'Q':
						SetMontorSpeed(0,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(0,&MONTOR_BACK_RIGHT);
						break;
					case 'W':
						SetMontorSpeed(20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(20000,&MONTOR_BACK_RIGHT);
						break;
					case 'E':
						SetMontorSpeed(20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(0,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(0,&MONTOR_BACK_LEFT);
						SetMontorSpeed(20000,&MONTOR_BACK_RIGHT);
						break;
					case 'A':
						SetMontorSpeed(-20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(-20000,&MONTOR_BACK_RIGHT);
						break;
					case 'S':
						SetMontorSpeed(0,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(0,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(0,&MONTOR_BACK_LEFT);
						SetMontorSpeed(0,&MONTOR_BACK_RIGHT);
						break;
					case 'D':
						SetMontorSpeed(20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(-20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(-20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(20000,&MONTOR_BACK_RIGHT);
						break;
					case 'Z':
						SetMontorSpeed(-20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(0,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(0,&MONTOR_BACK_LEFT);
						SetMontorSpeed(-20000,&MONTOR_BACK_RIGHT);
						break;
					case 'X':
						SetMontorSpeed(-20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(-20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(-20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(-20000,&MONTOR_BACK_RIGHT);
						break;
					case 'C':
						SetMontorSpeed(0,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(-20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(-20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(0,&MONTOR_BACK_RIGHT);
						break;
					case 'O':
						SetMontorSpeed(-20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(-20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(20000,&MONTOR_BACK_RIGHT);
						break;
					case 'P':
						SetMontorSpeed(20000,&MONTOR_FRONT_LEFT);
						SetMontorSpeed(-20000,&MONTOR_FRONT_RIGHT);
						SetMontorSpeed(20000,&MONTOR_BACK_LEFT);
						SetMontorSpeed(-20000,&MONTOR_BACK_RIGHT);
						break;
				}
			}
		}
	}
}

void MontorEncoderTest(char c,const MontorInstance* instance)
{
	if(c=='A'){
		while(1)
		{
			int count = GetEncoderNum(instance);
			USART1SendNumInt(count);
			USART1SendChar('\n');
			DelayS(1);
		}
	}else if(c=='M'){
		SetMontorRotation(true,instance);
		SetMontorAbsSpeed(18000,instance);
		while(1)
		{
			int count = GetEncoderNum(instance);
			USART1SendNumInt(count);
			USART1SendChar('\n');
			ResetEncoderNum();
			DelayMs(100);
		}
	}
	else
	{
	
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

void PIDTest(const MontorInstance* montor)
{
	int speed=0; 
	//600
	PIDInstance instance={0000,0,0,0,0,0,8,0,0};
	SetMontorRotation(true,montor);
	while(1)
	{
		unsigned int count = GetMontorSpeed(montor);
		speed=FinishOnePIDStep(&instance,count);
		
		USART1SendNumInt(count);
		USART1SendChar('-');
		USART1SendNumInt(speed);
		USART1SendChar('\n');
		
		SetMontorAbsSpeed(speed,montor);
		ResetEncoderNum();
		
		DelayMs(100);
	}
}

void MotionAnalysisTest(char c)
{
	if(c=='B')
	{
		while(1)
		{
			MotionAnalysisDirectSet(300,WHEEL_MASK_FORWARD);
			DelayS(1);
			MotionAnalysisDirectSet(300,WHEEL_MASK_BACKWARD);
			DelayS(1);
		}
	}
	else if(c=='P')
	{
		MoveMask=WHEEL_MASK_LEFT;
		MoveSpeedFactor=7000;
		RotateMask=WHEEL_MASK_EMPTY;
		RotateSpeedFactor=0;
		TranslateMask=WHEEL_MASK_EMPTY;
		TranslateSpeedFactor=0;
		while(1)
		{
			MotionAnalysisOnStep();
			DelayMs(100);
		}
	}
	else if(c=='T')
	{
		MoveSpeedFactor=4000;
		MoveMask=WHEEL_MASK_FORWARD;
		RotateSpeedFactor=1300;
		TranslateSpeedFactor=1000;
		//TrackerConfig(XMask);
		//if(LineTrackEnable(true))
		//{
		//	LCD12864NumDraw(000,000);
		//}
		int k=0;
		DelayS(1);
		while(1)
		{
			k++;
			if(k>6)
			{
				CriticalDigitalLevelChange();
				k=0;
			}
			MotionAnalysisOnStep();
			DelayMs(100);
			/*
			switch(RotateMask)
			{
				case WHEEL_MASK_ANTICLOCK:
					USART1SendChar('A');break;
				case WHEEL_MASK_CLOCK:
					USART1SendChar('C');break;
				case WHEEL_MASK_LEFT:
					USART1SendChar('R');break;
				case WHEEL_MASK_RIGHT:
					USART1SendChar('L');break;
			}*/
			
		}
	}
	else if(c=='C')
	{
		MoveMask=WHEEL_MASK_LEFT;
		//MotionAnalysisDirectSet(0,WHEEL_MASK_EMPTY);
		SetSystemFunctionCycle(MotionAnalysisOnStep,10);
		EnableSystemFunctionCycle(true);
		while(1)
		{
			if(USART1IsReceive())
			{
				char c = *USART1GetOrder();
				switch(c)
				{
					case 'W':
						MoveMask=WHEEL_MASK_FORWARD;
						break;
					case 'X':
						MoveMask=WHEEL_MASK_BACKWARD;
						break;
					case 'A':
						MoveMask=WHEEL_MASK_LEFT;
						break;
					case 'D':
						MoveMask=WHEEL_MASK_RIGHT;
						break;
					case 'S':
						MoveMask=WHEEL_MASK_EMPTY;
						break;
				}
			}
		}
	}
}

void SystermCallBack(void)
{
	MotionAnalysisOnStep();
}

void SystermCallBackTest(void)
{
	MoveMask=WHEEL_MASK_FORWARD;
	SetSystemFunctionCycle(SystermCallBack,10);
	EnableSystemFunctionCycle(true);
}

