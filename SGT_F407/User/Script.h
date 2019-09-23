#ifndef _SCRIPT_H
#define _SCRIPT_H

#include "Bsp.h"
/*
 * ��������˸߶ȷ�װ�Ľű������Թ�����������
 * ��Щ������ȫ�������ģ���ζ�����Ǳ���һ��һ����ִ�У��������Ƕ��������еĹ����н��еײ�ϵͳ��ά��
 */
typedef struct PositionStructure
{
	int x,y;
}Position;

//Ԥ����ĸ���ƶ�����
#define Oritation_X_Positive 0
#define	Oritation_X_Negative 1
#define	Oritation_Y_Positive 2
#define	Oritation_Y_Negative 3
#define	Oritation_1_Quadrant 4
#define	Oritation_2_Quadrant 5
#define	Oritation_3_Quadrant 6
#define	Oritation_4_Quadrant 7

/*����������*/
//����Ѱ·�㷨���ƶ�����
void MoveTo(Position);
//���� orientation �ƶ� tileCount ������� ������ת����
void MoveToward(int orientation, float tileCount);
//���� orientation �ƶ� tileCount ������� ������ת����
void MoveTowardR(int orientation, float tileCount);
//���� orientation
void LookAt(int orientation);
//ͣ�� ����Ȼһ���������ִ����֮����Զ�ֹͣ��
void Stop();

/*���������*/
//���û�е����̬�Ĺؼ�֡
void SetKey(int Angle1,int Angle2);
//�ȴ��������
void Wait();
//�򿪻�еצ
void Open();
//�պϻ�еצ
void Close();

/*������Ϊ��*/
//ɨ���ά��
void ScanQRcode();//��ɨ��֮������������Ϣ���ö�Ӧ�Ľű�
//ɨ�����
void PeekGoods();
//��ȡ���
void PickGood();
//�ͷ����
void DropGood();
//����
void Adjust();

#endif
