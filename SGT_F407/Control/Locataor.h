#ifndef _LOCATAOR_H
#define _LOCATAOR_H

#include "LineTrack.h"
#include <stdbool.h>
/*
 * ���ζ�λ�� ����㶨λ����
 * ���õײ��Ҷȴ�������ʹ���ؾ߿��Զ�λ�Լ���λ���ڸ��֮��
 * ����ڶ�λ��ʹ�û��������ǵĸ��㶨λ��
 */

extern int LocataorCountRising;
extern int LocataorCountFalling;

//���ö�λ���Ļص�������
void LocatorConfig(unsigned char mask);
//�����ص�
void LocatorCallBackFunction(unsigned char trigerPin,bool isRising);
//�رն�λ����
void LocatorModeDisable(void);

#endif
