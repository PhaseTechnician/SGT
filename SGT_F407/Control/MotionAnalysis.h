#ifndef _MOTIONANALYSIS_H
#define _MOTIONANALYSIS_H

#include "MontorDriver.h"
/*
 * �˶�����ͷ��� ����ǰδ���PID���ϡ�
 * ���ĸ����ӵ��ٶȽ��з����Ϳ���
 * �ֲ�����ϵ��
 *    +x    
 *   +yoy-
 *    -x   
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

//�������з��� 
void SetOrientation(unsigned char LocalOrientation);
//���������ٶ�
void SetSpeed(unsigned int LineSpeed);
//�߼��ں˺���[������]
void MotionAnalysisOnStep(void);
//��ȡ��ǰ���������귽��
//get()

#endif
