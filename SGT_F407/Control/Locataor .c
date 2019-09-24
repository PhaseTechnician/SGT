#include "Locataor.h"

//上一次的扫描结果
unsigned char lastResult=0b00000000;
//监视掩码,需要监视的位置1
unsigned char monitorMask=0b00000000;

//双边掩码
#define MonitorMask_Full_X 0b00111100
#define MonitorMask_Full_Y 0b11000011
#define MonitorMask_Full_XY 0b11111111
//单边掩码
#define MonitorMask_Part_X 0b00111100
#define MonitorMask_Part_Y 0b11000011
#define MonitorMask_Full_XY 0b11111111

//计数器
int count;
//状态 - out2  |on2|  in0  |on1|  out1 +
int state;
#define State_Out_1 1
#define State_On_1  2
#define State_In_0  3
#define State_On_2  4
#define State_Out_2 5

void NewO8LocataorTask(unsigned char monitor, int num)
{
	lastResult = LineTrackResult;
	count = num;
}

void LocataorOnStep(void)
{
	//查看是否存在变化
	if((lastResult^LineTrackResult)&monitorMask)
	{
		
	}
	lastResult = LineTrackResult;
}

inline int GetRemainCount(void)
{
	return count;
}
