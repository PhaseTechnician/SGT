#ifndef _TRACKER_H
#define _TRACKER_H

#include "LineTrack.h"
#include "MotionAnalysis.h"
#include <stdbool.h>
/*
 * Ѳ����
 * ���õײ��Ҷȴ�������ʹ���ؾ߿������ƶ�ʱ���������ƶ�
 */

//����Ѳ�����Ļص�������
void TrackerConfig(unsigned char XYmask);
//�����ص�
void TrackCallBackFunction(unsigned char trigerPin,bool isRising);
//�ر�Ѳ�߹���
void TrackModeDisable(void);

#endif
