#include "BSP.h"
#include "Script.h"
#include "Test.h"

void TaskFunction(void);

int main(void)
{
	//模块初始化
	BSPConfig();
	//尝试自检
	if(!BSPTest())
	{
		while(1);
	}
	//准备设备
	InitStartMotion();
	USART1ClearReceive();
	//DelayS(1);
	//各模块的测试函数
	//USART1Send("finish init");
	//LCD12864NumDraw(222,321);
	//LineTrackTest();
	//ServerTest('C');
	//MontorDriverOutputTest('C');
	//MontorEncoderTest('A',&MONTOR_FRONT_LEFT);
	//PIDTest(&MONTOR_FRONT_LEFT);
  //MotionAnalysisTest('T');
	//SystermCallBackTest();
	//载入任务程序
	TaskFunction();
	while(1);
}
ActionNode nodes;
#define MOTION_PEEK &nodes
#define MOTION_QRCODE &nodes
#define MOTION_LEFT_READY
#define MOTION_LEFT_CATCH
#define MOTION_MIDDLE_READY
#define MOTION_MIDDLE_CATCH
#define MOTION_RIGHT_READY
#define MOTION_RIGHT_CATCH

char commands[6] = {0};

//										 Red Gre Blu
unsigned char R_Pos[3]={0};
unsigned char P_Pos[3]={3,2,1};
unsigned char S_Pos[3]={1,2,3};

int TRACKCOUNT=0;
void SystemLoop(void)
{
/*
	TRACKCOUNT++;
	if(TRACKCOUNT>6)
	{
		CriticalDigitalLevelChange();
		TRACKCOUNT=0;
	}*/
	//SequenceOnStep(100);
	//MotionAnalysisOnStep();
}

void MoveForwardEasy()
{
	MotionAnalysisDirectSet(4000,WHEEL_MASK_FORWARD);
	while(1)
	{
		unsigned char result = directReadLineTrackResult();
		if(BIT_AT(result,3)||BIT_AT(result,4))
		{
			DelayMs(10);
			result = directReadLineTrackResult();
			if(BIT_AT(result,4)||BIT_AT(result,4))
			{
				MotionAnalysisDirectSet(1000,WHEEL_MASK_BACKWARD);
				break;
			}
		}
	}
	MotionAnalysisDirectSet(0,WHEEL_MASK_EMPTY);
}

void MoveRightEasy(int length)
{
	int k=0;
	MotionAnalysisDirectSet(6000,WHEEL_MASK_RIGHT);
	while(1);
	while(1)
	{
		unsigned char result = directReadLineTrackResult();
		if(BIT_AT(result,2))
		{
			DelayMs(10);
			result = directReadLineTrackResult();
			if(BIT_AT(result,2))
			{
				k++;
				if(k>=length)
					break;
				DelayS(1);
			}
		}
	}
	MotionAnalysisDirectSet(1000,WHEEL_MASK_LEFT);
	DelayMs(100);
	MotionAnalysisDirectSet(0,WHEEL_MASK_EMPTY);
}

void TaskFunction(void)
{
	Close();
	DelayMs(100);
	//设置部分
		//启动系统维护循环，周期100ms
	SetSystemFunctionCycle(SystemLoop,10);
	EnableSystemFunctionCycle(true);
	//阶段一 移入初始轨道线并做好准备姿势
	MoveForwardEasy();
	//MoveToward(WHEEL_MASK_FORWARD,1);
	Open();
	
	MoveRightEasy(3);
	
	while(1);
	
	StartMotion(MOTION_QRCODE);
	//阶段二 抵达中线，判断物料颜色
	MoveToward(WHEEL_MASK_RIGHT,4);
		WaitMotion(1000);
		if(IsColor(1000,COLOR_BLUE))
		StartMotion(MOTION_QRCODE);
		WaitMotion(1000);
		if(IsColor(1000,COLOR_BLUE))
	//阶段三 前去扫描二维码
	StartMotion(MOTION_QRCODE);
	MoveToward(WHEEL_MASK_RIGHT,2);
	WaitMotion(1000);//最多等待1秒的时间
	while(!ScanQRcode(commands,10));//扫描二维码,也许可以抖一抖
	//阶段四 前往R区域
	StartMotion(MOTION_QRCODE);
	Open();
	MoveToward(WHEEL_MASK_LEFT,R_Pos[commands[0]-'0']);
	WaitMotion(1000);
	StartMotion(MOTION_QRCODE);
	WaitMotion(1000);
	StartMotion(MOTION_QRCODE);
	WaitMotion(1000);
	Close();
	
}


