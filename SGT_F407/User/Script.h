#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "Bsp.h"
#include "Locataor.h"
#include "Tracker.h"
#include "MotionAnalysis.h"

/*
 * ��������˸߶ȷ�װ�Ľű������Թ�����������
 * ��Щ������ȫ�������ģ���ζ�����Ǳ���һ��һ����ִ�У��������Ƕ��������еĹ����н��еײ�ϵͳ��ά��
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
//���û�е����̬�Ĺؼ�֡
//void SetKey(int Angle1,int Angle2);
//�ȴ��������
//void Wait();
//�򿪻�еצ[��Ҫ����һ��ʱ���]
void Open(void);
//�պϻ�еצ[��Ҫ����һ��ʱ���]
void Close(void);

/*�����ⲿAPI��*/
//ɨ���ά��
//void ScanQRcode(void);
//ɨ�����
//void PeekGoods(void);
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
