#include "BSP.h"
#include "PIDController.h"
#include "SequenceController.h"
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
	LCDTest();
}

void TaskFunction(void)
{
	MoveToward(Orientation_X_Positive,3);
	PeekGoods();
}
