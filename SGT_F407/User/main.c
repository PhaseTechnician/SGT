#include "BSP.h"
#include "PIDController.h"
#include "SequenceController.h"
#include "Script.h"
#include "Test.h"

void TaskFunction(void);

int main(void)
{
	//初始化
	BSPConfig();
	if(!BSPTest())
	{
		while(1);
	}
	//载入任务程序
	//USART1Send("finish init");
	//MontorDriverOutputTest();
	MontorEncoderTest();
}

void TaskFunction(void)
{
}
