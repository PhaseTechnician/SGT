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
		if(IsUSART1Receive())
		{
			USART1Send(USART1GetOrder());
		}
	}
}

void ServerTest(void)
{
	while(1)
	{
		ServerSetAngle(0,SERVER_1);
		ServerSetAngle(0,SERVER_2);
		ServerSetAngle(0,SERVER_3);
		ServerSetAngle(0,SERVER_4);
		ServerSetAngle(0,SERVER_5);
		DelayS(1);
		ServerSetAngle(180,SERVER_1);
		ServerSetAngle(180,SERVER_2);
		ServerSetAngle(180,SERVER_3);
		ServerSetAngle(180,SERVER_4);
		ServerSetAngle(180,SERVER_5);
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
