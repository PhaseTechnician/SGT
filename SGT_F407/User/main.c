#include "BSP.h"
#include "Script.h"
#include "Test.h"

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
