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

//����λ������ת�򡾲����ơ�
#define LocalOrientation_X_Positive 5;
#define LocalOrientation_X_Negitive 6;
#define LocalOrientation_Y_Positive 7;
#define LocalOrientation_Y_Negitive 8;
#define LocalOrientation_XY_1 1;
#define LocalOrientation_XY_2 2;  
#define LocalOrientation_XY_3 3;
#define LocalOrientation_XY_4 4;

//�ֲ������� ����λ����ʹ�� ����λ����ʹ��
#define WHEEL_MASK_Clock          0b10100101
#define WHEEL_MASK_ANTICLOCK      0b01011010
#define WHEEL_MASK_FORWARD        0b11110000
#define WHEEL_MASK_BACKWARD       0b00001111
#define WHEEL_MASK_LEFT           0b01101001
#define WHEEL_MASK_Right          0b10010110
#define WHEEL_MASK_LEFT_FORWARD   0b01100000
#define WHEEL_MASK_RIGHT_FORWARD  0b10010000
#define WHEEL_MASK_LEFT_BACKWARD  0b00001001
#define WHEEL_MASK_RIGHT_BACKWARD 0b00000110
//��ʼ������
void MontionAnalysisConfig(void);
//�������з��� 
void SetOrientation(unsigned char LocalOrientation);
//���������ٶ�
void SetSpeed(unsigned int LineSpeed);
//�߼��ں˺���[������]
void MotionAnalysisOnStep(void);
//��ȡ��ǰ���������귽��
//get()

#endif
