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
ActionNode nodes;
#define PEEK_MOTION &nodes

char orders[6] = {0};
char goodsPosition[3] = {0};

void TaskFunction(void)
{
	//�׶�һ �����ʼ����߲�����׼������
	MoveToward(WHEEL_MASK_FORWARD,1);
	Open();
	StartMotion(PEEK_MOTION);
	WaitMotion(1000);//�ȴ�׼�����������
	//�׶ζ� ǰȥɨ���ά�룬��ͬʱɨ��һ��ɫ����Ϣ
	MoveToward(WHEEL_MASK_RIGHT,1);
	if(PeekGoods(goodsPosition,20000))
	{
		while(!ScanQRcode(orders,10));//ɨ���ά��,Ҳ����Զ�һ��
		MoveToward(WHEEL_MASK_LEFT,1);//�ص�ɫ��λ��,ץȡ
	}
	else //û�гɹ������Ϣ��ֻ����֮�����γ���
	{
	
	}
}
