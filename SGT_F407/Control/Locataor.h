#ifndef _LOCATAOR_H
#define _LOCATAOR_H

#include "LineTrack.h"
#include <stdbool.h>
/*
 * ���ζ�λ�� ����㶨λ����
 * ���õײ��Ҷȴ�������ʹ���ؾ߿��Զ�λ�Լ���λ���ڸ��֮��
 * ����ڶ�λ��ʹ�û��������ǵĸ��㶨λ��
 */

//ÿһ��ϵͳ������ά��8��Ѱ��ģ��״̬�����ݷ���ͼ�¼��������״̬

//����һ���µ�������λ����
void NewO8LocataorTask(unsigned char monitor, int num);
//����һ���µĶԽǶ�λ����
void NewOxLocataorTask(unsigned char monitor, int count1,int count2);
//�߼��ں˺���
void LocataorOnStep(void);
//��ȡ��ǰʣ��ĸ���� Ϊ0���������������ln
int GetRemainCount(void);
#endif
