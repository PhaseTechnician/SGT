#ifndef _SQUENCECONTROLLER_H
#define _SQUENCECONTROLLER_H
#include <stdbool.h>
#include "Server.h"
#include "Others.h"

/*
 * ���п�����
 * ���ڽ�Ԥ�ȱ��ŵĶ����������
 * ��Ҫ���ڻ�е�۵Ķ�������
 */

//���������ɶ���֡�ͳ���ʱ����ɣ������ڵ�����ĸ���е�۶���ĽǶ���Ϣ����������źų���ֱ����һ֡����Ҫ��ʱ�䡣
//��Ӧ���ڶ��������һ֡����һ����ʱΪ0��֡��ʾ��������ʱ��ʾΪ�������,���������һ��֡��
typedef struct ActionFrameStructure
{
	int angle1;
	int angle2;
	int angle3;
	int angle4;
}ActionFrame;
typedef struct ActionNodeStructure
{
	ActionFrame *frame;
	int delayTimes;
}ActionNode;

//�����ڵ�
extern ActionNode ActionNode_END;

//���в������鿴�Ƿ�Ӧ�õ���һ������֡����������Ƶ���ĵ�����
void SequenceOnStep(int pastTime);
//���õ�ǰ����
void SetSequence(ActionNode actions[]);
//�鿴�����Ƿ����
bool IsFinished(void);

#endif
