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
	MontorEncoderTest();
}

void TaskFunction(void)
{

}
