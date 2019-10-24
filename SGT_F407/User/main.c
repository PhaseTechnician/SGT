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
	//各模块的测试函数
	//USART1Send("finish init");
	//LCD12864NumDraw(222,321);
	//LineTrackTest();
	//ServerTest('C');
	//MontorDriverOutputTest('C');
	//MontorEncoderTest('M',&MONTOR_BACK_RIGHT);
	//PIDTest(&MONTOR_BACK_RIGHT);
	//MotionAnalysisTest('P');
	//SystermCallBackTest();
	//载入任务程序
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
	//设置部分
		//启动系统维护循环，周期100ms
	SetSystemFunctionCycle(SystemLoop,10);
	EnableSystemFunctionCycle(true);
	//阶段一 移入初始轨道线并做好准备姿势
	MoveToward(WHEEL_MASK_FORWARD,1);
	Open();
	StartMotion(MOTION_PEEK);
	WaitMotion(1000);//等待准备动作的完成
	//阶段二 前去扫描二维码，并同时扫略一下色块信息
	MoveToward(WHEEL_MASK_RIGHT,1);
	/*如果不能运行PEEK函数
	if(PeekGoods(goodsPosition,20000))
	{
		while(!ScanQRcode(commands,10));//扫描二维码,也许可以抖一抖
		MoveToward(WHEEL_MASK_LEFT,1);//回到色块位置,抓取
	}
	else //没有成功获得信息，只能在之后依次尝试
	{
	
	}*/
}
