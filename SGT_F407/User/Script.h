#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "Bsp.h"
#include "Locataor.h"
#include "Tracker.h"
#include "MotionAnalysis.h"
#include "SequenceController.h"

/*
 * 这里包含了高度封装的脚本函数以供完成任务调用
 * 这些函数完全是阻塞的，意味着他们必须一个一个的执行
 * 系统维护循环需要设置和自定义
 */
typedef struct PositionStructure
{
	int x,y;
}Position;

/*底盘驱动类*/
//带有寻路算法的移动命令
//void MoveTo(Position);
//向着 orientation 移动 tileCount 个网格点 不会旋转朝向
void MoveToward(unsigned char orientation, int tileCount);
//向着 orientation 移动 tileCount 个网格点 最终旋转朝向
//void MoveTowardR(int orientation, float tileCount);
//朝向 orientation
//void LookAt(int orientation);
//停车 【虽然一般的命令在执行完之后会自动停止】
void Stop(void);

/*舵机控制类*/
//初始化舵机的位置
void InitStartMotion(void);
//启动机械臂的动作
void StartMotion(ActionNode actions[]);
//等待动作完成,超时跳过
void WaitMotion(unsigned int waitTimeMs);
//打开机械爪[需要持续一段时间后]
void Open(void);
//闭合机械爪[需要持续一段时间后]
void Close(void);

/*串口外部API类*/
//测试通讯频道 期待的回复 "<PI>"
bool TryConnectedPi(int waitTimes);
//扫描二维码,获得扫描的结果，以六个字符表示，多次尝试上端无响应后将会返回false
bool ScanQRcode(char* Result6char,int times);
//判断当前的颜色是否正确 期待的回复 "<yes>" "<no>"
#define COLOR_RED "<WR>"
#define COLOR_GREEN "<WG>"
#define COLOR_BLUE "<WB>"
bool IsColor(int waitTimes,const char* color);
//扫视物块,由于运行中扫略，这个函数可能不一定获得最为确切的结果,在超过等待时间后，放弃等待返回false
bool PeekGoods(char* Result3Char,int waitTimes);
//定位靶点
//void GetSport(void);

/*组合行为*/
//获取物块
//void PickGood(void);
//释放物块
//void DropGood(void);
//调整
//void Adjust(void);

#endif
