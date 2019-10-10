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
ActionNode nodes;
#define PEEK_MOTION &nodes

char orders[6] = {0};
char goodsPosition[3] = {0};

void TaskFunction(void)
{
	//阶段一 移入初始轨道线并做好准备姿势
	MoveToward(WHEEL_MASK_FORWARD,1);
	Open();
	StartMotion(PEEK_MOTION);
	WaitMotion(1000);//等待准备动作的完成
	//阶段二 前去扫描二维码，并同时扫略一下色块信息
	MoveToward(WHEEL_MASK_RIGHT,1);
	if(PeekGoods(goodsPosition,20000))
	{
		while(!ScanQRcode(orders,10));//扫描二维码,也许可以抖一抖
		MoveToward(WHEEL_MASK_LEFT,1);//回到色块位置,抓取
	}
	else //没有成功获得信息，只能在之后依次尝试
	{
	
	}
}
