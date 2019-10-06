#ifndef _LOCATAOR_H
#define _LOCATAOR_H

#include "LineTrack.h"
#include <stdbool.h>
/*
 * 整形定位器 【格点定位器】
 * 利用底部灰度传感器，使得载具可以定位自己的位置于格点之上
 * 格点内定位请使用基于陀螺仪的浮点定位器
 */

extern int LocataorCountRising;
extern int LocataorCountFalling;

//设置定位器的回调和掩码
void LocatorConfig(unsigned char mask);
//触发回调
void LocatorCallBackFunction(unsigned char trigerPin,bool isRising);
//关闭定位功能
void LocatorModeDisable(void);

#endif
