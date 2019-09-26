#ifndef _PIDCONTROLLER_H
#define _PIDCONTROLLER_H

/*
 * PID ������
 * ��Ҫ���ڵ��ϵͳ���ٶȿ���
 * ͨ���ṹ����ʵ�ֿ������Ķ�ʵ��ʹ��
 */
 
typedef struct PIDInstanceStructure
{
	int goal;
	int feedback;
	int presentError;
	int lastError;
	int presentOutput;
	unsigned int lastOutput;
	float KP,KI,KD;
}PIDInstance;
 
//���һ��PID���Ʋ�������ñ��ε����ֵ
int FinishOnePIDStep(PIDInstance * instance,int feedBackValue);
//��ʼ��һ��PIDʵ��
void InitOnePIDInstance(PIDInstance * instance,int goalValue,float KP,float KI,float KD);
//��ʱ�޸�Ŀ��ֵ
void SetPIDGoalValue(PIDInstance * instance,int goalValue);


#endif
