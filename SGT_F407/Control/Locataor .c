#include "Locataor.h"

//��һ�ε�ɨ����
unsigned char lastResult=0b00000000;
//��������,��Ҫ���ӵ�λ��1
unsigned char monitorMask=0b00000000;

//˫������
#define MonitorMask_Full_X 0b00111100
#define MonitorMask_Full_Y 0b11000011
#define MonitorMask_Full_XY 0b11111111
//��������
#define MonitorMask_Part_X 0b00111100
#define MonitorMask_Part_Y 0b11000011
#define MonitorMask_Full_XY 0b11111111

//������
int count;
//״̬ - out2  |on2|  in0  |on1|  out1 +
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
	//�鿴�Ƿ���ڱ仯
	if((lastResult^LineTrackResult)&monitorMask)
	{
		
	}
	lastResult = LineTrackResult;
}

inline int GetRemainCount(void)
{
	return count;
}
