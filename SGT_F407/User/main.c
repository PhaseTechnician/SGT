#include "BSP.h"
#include "PIDController.h"
#include "SequenceController.h"
#include "Script.h"

void DebugFunction();
void TaskFunction();

int main()
{
	//��ʼ��
	BSPConfig();
	if(!BSPTest())
	{
		while(1);
	}
	//�����������
	
}

void DebugFunction()
{
	
}

void TaskFunction()
{
	MoveToward(Orientation_X_Positive,3);
	PeekGoods();
}
