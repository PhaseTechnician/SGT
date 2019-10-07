#ifndef _LOCATAOR_H
#define _LOCATAOR_H

#include "LineTrack.h"
#include <stdbool.h>
/*
 * 整形定位器 【格点定位器】
 * 利用底部灰度传感器，使得载具可以定位自己的位置于格点之上
 * 格点内定位请使用基于陀螺仪的浮点定位器
 * 在转换方向后，需要根据情况修正一下定位器的高低计数值【1】
 * 延迟一下点时间之后重置计数器【2】【√】
 */
 
extern int HighPinCount;
extern int LowPinCount;

//设置定位器的回调和掩码
void LocatorConfig(unsigned char CPmask);
//触发回调
void LocatorCallBackFunction(unsigned char trigerPin,bool isRising);
//关闭定位功能
void LocatorModeDisable(void);
//重置两个计数器
void LocataorReset(void);
//获取CP组中的LowPIN
unsigned char GetLowPinInCp(unsigned char CPMask);
//获取CP组中的HighPIN
unsigned char GetHighPinInCp(unsigned char CPMask);
#endif
