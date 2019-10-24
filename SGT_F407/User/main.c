#include "BSP.h"
#include "Script.h"
#include "Test.h"

void TaskFunction(void);

int main(void)
{
	//ģ���ʼ��
	BSPConfig();
	//�����Լ�
	if(!BSPTest())
	{
		while(1);
	}
	//׼���豸
	InitStartMotion();
	USART1ClearReceive();
	//��ģ��Ĳ��Ժ���
	//USART1Send("finish init");
	//LCD12864NumDraw(222,321);
	//LineTrackTest();
	//ServerTest('C');
	//MontorDriverOutputTest('C');
	//MontorEncoderTest('M',&MONTOR_BACK_RIGHT);
	//PIDTest(&MONTOR_BACK_RIGHT);
	//MotionAnalysisTest('P');
	//SystermCallBackTest();
	//�����������
	TaskFunction();
	while(1);
}
ActionNode nodes;
#define MOTION_PEEK &nodes
#define MOTION_QRCODE
#define MOTION_LEFT_READY
#define MOTION_LEFT_CATCH
#define MOTION_MIDDLE_READY
#define MOTION_MIDDLE_CATCH
#define MOTION_RIGHT_READY
#define MOTION_RIGHT_CATCH

char commands[6] = {0};
char goodsPosition[3] = {0};

void SystemLoop(void)
{
	CriticalDigitalLevelChange();
	SequenceOnStep(100);
	MotionAnalysisOnStep();
}

void TaskFunction(void)
{
	//���ò���
		//����ϵͳά��ѭ��������100ms
	SetSystemFunctionCycle(SystemLoop,10);
	EnableSystemFunctionCycle(true);
	//�׶�һ �����ʼ����߲�����׼������
	MoveToward(WHEEL_MASK_FORWARD,1);
	Open();
	StartMotion(MOTION_PEEK);
	WaitMotion(1000);//�ȴ�׼�����������
	//�׶ζ� ǰȥɨ���ά�룬��ͬʱɨ��һ��ɫ����Ϣ
	MoveToward(WHEEL_MASK_RIGHT,1);
	/*�����������PEEK����
	if(PeekGoods(goodsPosition,20000))
	{
		while(!ScanQRcode(commands,10));//ɨ���ά��,Ҳ����Զ�һ��
		MoveToward(WHEEL_MASK_LEFT,1);//�ص�ɫ��λ��,ץȡ
	}
	else //û�гɹ������Ϣ��ֻ����֮�����γ���
	{
	
	}*/
}
