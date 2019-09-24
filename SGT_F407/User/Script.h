#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "Bsp.h"
#include "Locataor.h"
#include "MotionAnalysis.h"

/*
 * 这里包含了高度封装的脚本函数以供完成任务调用
 * 这些函数完全是阻塞的，意味着他们必须一个一个的执行，但是他们都会在运行的过程中进行底层系统的维护
 */
typedef struct PositionStructure
{
	int x,y;
}Position;

//预定义的格点移动方向
#define Orientation_X_Positive 0
#define	Orientation_X_Negative 1
#define	Orientation_Y_Positive 2
#define	Orientation_Y_Negative 3
#define	Orientation_1_Quadrant 4
#define	Orientation_2_Quadrant 5
#define	Orientation_3_Quadrant 6
#define	Orientation_4_Quadrant 7

/*底盘驱动类*/
//带有寻路算法的移动命令
//void MoveTo(Position);
//向着 orientation 移动 tileCount 个网格点 不会旋转朝向
void MoveToward(int orientation, float tileCount);
//向着 orientation 移动 tileCount 个网格点 最终旋转朝向
//void MoveTowardR(int orientation, float tileCount);
//朝向 orientation
//void LookAt(int orientation);
//停车 【虽然一般的命令在执行完之后会自动停止】
void Stop(void);

/*舵机控制类*/
//设置机械臂姿态的关键帧
//void SetKey(int Angle1,int Angle2);
//等待动作完成
//void Wait();
//打开机械爪[需要持续一段时间后]
void Open(void);
//闭合机械爪[需要持续一段时间后]
void Close(void);

/*串口外部API类*/
//扫描二维码
void ScanQRcode(void);
//扫视物块
void PeekGoods(void);
//定位靶点
void GetSport(void);

/*组合行为*/
//获取物块
//void PickGood(void);
//释放物块
//void DropGood(void);
//调整
//void Adjust(void);

#endif
