#ifndef _MOTIONANALYSIS_H
#define _MOTIONANALYSIS_H

#include "MontorDriver.h"
#include "PIDController.h"

/*
 * �˶�����ͷ��� ����ǰδ���PID���ϡ�
 * ���ĸ����ӵ��ٶȽ��з����Ϳ���
 * �ֲ�����ϵ��
 *   1+x 2   
 *   +yoy-
 *   3-x 4  
 * ���ֵ����Ӧ����������������Ե���
 *   ������--���Ƕ�ƫ��--����ת����
 * Ѱ��ģ��--��λ��ƫ��--��ƽ�Ʒ���
 * ����ָ��--��ǰ������--���ƶ�����
 */

//�ֲ������� ����λ����ʹ�� ����λ����ʹ��
#define WHEEL_MASK_CLOCK          0b10100101
#define WHEEL_MASK_ANTICLOCK      0b01011010
#define WHEEL_MASK_FORWARD        0b11110000
#define WHEEL_MASK_BACKWARD       0b00001111
#define WHEEL_MASK_LEFT           0b01101001
#define WHEEL_MASK_RIGHT          0b10010110
#define WHEEL_MASK_LEFT_FORWARD   0b01100000
#define WHEEL_MASK_RIGHT_FORWARD  0b10010000
#define WHEEL_MASK_LEFT_BACKWARD  0b00001001
#define WHEEL_MASK_RIGHT_BACKWARD 0b00000110
#define WHEEL_MASK_EMPTY          0b00000000

//ע��������Σ�����֮�Ͳ��ó���������ٶ�
//ͬʱ����Ҫ����һ���ķ�ΧΪPID�����ṩ��������

extern int MoveSpeedFactor;
extern int RotateSpeedFactor;
extern int TranslateSpeedFactor;
extern unsigned char MoveMask;
extern unsigned char TranslateMask;
extern unsigned char RotateMask;

//��ʼ������
void MontionAnalysisConfig(void);
//���õ��̵��ٶȺͷ���,�����Զ�ά��ֱ�Ӹ�ֵ
void MotionAnalysisDirectSet(int speed,unsigned char WHEEL_MASK);
//�߼��ں˺���[������]��������100ms������á���̫С�ļ�����±��������ܻ����㹻�����ֵ����ƽ����̫���ļ��Ӱ���߼������С�
void MotionAnalysisOnStep(void);

#endif
