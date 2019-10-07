#ifndef _LOCATAOR_H
#define _LOCATAOR_H

#include "LineTrack.h"
#include <stdbool.h>
/*
 * ���ζ�λ�� ����㶨λ����
 * ���õײ��Ҷȴ�������ʹ���ؾ߿��Զ�λ�Լ���λ���ڸ��֮��
 * ����ڶ�λ��ʹ�û��������ǵĸ��㶨λ��
 * ��ת���������Ҫ�����������һ�¶�λ���ĸߵͼ���ֵ��1��
 * �ӳ�һ�µ�ʱ��֮�����ü�������2�����̡�
 */
 
extern int HighPinCount;
extern int LowPinCount;

//���ö�λ���Ļص�������
void LocatorConfig(unsigned char CPmask);
//�����ص�
void LocatorCallBackFunction(unsigned char trigerPin,bool isRising);
//�رն�λ����
void LocatorModeDisable(void);
//��������������
void LocataorReset(void);
//��ȡCP���е�LowPIN
unsigned char GetLowPinInCp(unsigned char CPMask);
//��ȡCP���е�HighPIN
unsigned char GetHighPinInCp(unsigned char CPMask);
#endif
