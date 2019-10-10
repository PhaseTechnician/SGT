#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "Bsp.h"
#include "Locataor.h"
#include "Tracker.h"
#include "MotionAnalysis.h"
#include "SequenceController.h"

/*
 * ��������˸߶ȷ�װ�Ľű������Թ�����������
 * ��Щ������ȫ�������ģ���ζ�����Ǳ���һ��һ����ִ��
 * ϵͳά��ѭ����Ҫ���ú��Զ���
 */
typedef struct PositionStructure
{
	int x,y;
}Position;

/*����������*/
//����Ѱ·�㷨���ƶ�����
//void MoveTo(Position);
//���� orientation �ƶ� tileCount ������� ������ת����
void MoveToward(unsigned char orientation, int tileCount);
//���� orientation �ƶ� tileCount ������� ������ת����
//void MoveTowardR(int orientation, float tileCount);
//���� orientation
//void LookAt(int orientation);
//ͣ�� ����Ȼһ���������ִ����֮����Զ�ֹͣ��
void Stop(void);

/*���������*/
//������е�۵Ķ���
void StartMotion(ActionNode actions[]);
//�ȴ��������,��ʱ����
void WaitMotion(unsigned int waitTimeMs);
//�򿪻�еצ[��Ҫ����һ��ʱ���]
void Open(void);
//�պϻ�еצ[��Ҫ����һ��ʱ���]
void Close(void);

/*�����ⲿAPI��*/
//ɨ���ά��,���ɨ��Ľ�����������ַ���ʾ����γ����϶�����Ӧ�󽫻᷵��false
bool ScanQRcode(char* Result6char,int times);
//ɨ�����,����������ɨ�ԣ�����������ܲ�һ�������Ϊȷ�еĽ��,�ڳ����ȴ�ʱ��󣬷����ȴ�����false
bool PeekGoods(char* Result3Char,int waitTimes);
//��λ�е�
//void GetSport(void);

/*�����Ϊ*/
//��ȡ���
//void PickGood(void);
//�ͷ����
//void DropGood(void);
//����
//void Adjust(void);

#endif
