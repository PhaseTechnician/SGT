#include "BSP.h"
#include "PIDController.h"
#include "SequenceController.h"
#include "Script.h"

void DebugFunction(void);
void TaskFunction(void);

int main(void)
{
	//��ʼ��
	BSPConfig();
	if(!BSPTest())
	{
		while(1);
	}
	//�����������
	USART1Send("stm32f407 try connected");
	while(1)
	{
		if(IsUSART1Receive())
		{
			USART1Send(USART1GetOrder());
		}
	}
}

void DebugFunction(void)
{
	
}

void TaskFunction(void)
{
	MoveToward(Orientation_X_Positive,3);
	PeekGoods();
}
