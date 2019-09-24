#include "BSP.h"
#include "PIDController.h"
#include "SequenceController.h"
#include "Script.h"

void DebugFunction();
void TaskFunction();

int main()
{
	//初始化
	BSPConfig();
	if(!BSPTest())
	{
		while(1);
	}
	//载入任务程序
	
}

void DebugFunction()
{
	
}

void TaskFunction()
{
	MoveToward(Orientation_X_Positive,3);
	PeekGoods();
}
