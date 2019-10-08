#include "BSP.h"
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
	//MontorEncoderTest();
	//LCDTest();
	LCD12864NumDraw(123,321);
	while(1);
}

void TaskFunction(void)
{

}
