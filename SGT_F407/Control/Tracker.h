#ifndef _TRACKER_H
#define _TRACKER_H

#include "LineTrack.h"
#include "MotionAnalysis.h"
#include <stdbool.h>
/*
 * 巡线器
 * 利用底部灰度传感器，使得载具可以在移动时跟随线条移动
 */

//设置巡线器的回调和掩码
void TrackerConfig(unsigned char XYmask);
//触发回调
void TrackCallBackFunction(unsigned char trigerPin,bool isRising);
//关闭巡线功能
void TrackModeDisable(void);

#endif
