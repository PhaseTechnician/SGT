#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "Bsp.h"
#include "Locataor.h"
#include "MotionAnalysis.h"

/*
 * ��������˸߶ȷ�װ�Ľű������Թ�����������
 * ��Щ������ȫ�������ģ���ζ�����Ǳ���һ��һ����ִ�У��������Ƕ��������еĹ����н��еײ�ϵͳ��ά��
 */
typedef struct PositionStructure
{
	int x,y;
}Position;

//Ԥ����ĸ���ƶ�����
#define Orientation_X_Positive 0
#define	Orientation_X_Negative 1
#define	Orientation_Y_Positive 2
#define	Orientation_Y_Negative 3
#define	Orientation_1_Quadrant 4
#define	Orientation_2_Quadrant 5
#define	Orientation_3_Quadrant 6
#define	Orientation_4_Quadrant 7

/*����������*/
//����Ѱ·�㷨���ƶ�����
//void MoveTo(Position);
//���� orientation �ƶ� tileCount ������� ������ת����
void MoveToward(int orientation, float tileCount);
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
void ScanQRcode(void);
//ɨ�����
void PeekGoods(void);
//��λ�е�
void GetSport(void);

/*�����Ϊ*/
//��ȡ���
//void PickGood(void);
//�ͷ����
//void DropGood(void);
//����
//void Adjust(void);

#endif
