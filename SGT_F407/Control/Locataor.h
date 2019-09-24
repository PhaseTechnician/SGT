#ifndef _LOCATAOR_H
#define _LOCATAOR_H

#include "LineTrack.h"
#include <stdbool.h>
/*
 * 整形定位器 【格点定位器】
 * 利用底部灰度传感器，使得载具可以定位自己的位置于格点之上
 * 格点内定位请使用基于陀螺仪的浮点定位器
 */

//每一个系统周期内维护8个寻线模块状态，根据方向和记录更新运行状态

//创建一个新的正交定位任务
void NewO8LocataorTask(unsigned char monitor, int num);
//创建一个新的对角定位任务
void NewOxLocataorTask(unsigned char monitor, int count1,int count2);
//逻辑内核函数
void LocataorOnStep(void);
//获取当前剩余的格点数 为0表明本次行走完成ln
int GetRemainCount(void);
#endif
