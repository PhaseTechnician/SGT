#ifndef _SQUENCECONTROLLER_H
#define _SQUENCECONTROLLER_H
#include <stdbool.h>
#include "Server.h"
#include "Others.h"

/*
 * 序列控制器
 * 用于将预先编排的动作序列输出
 * 主要用于机械臂的舵机组控制
 */

//动作序列由动作帧和持续时间组成，动作节点包含四个机械臂舵机的角度信息和这个动作信号持续直到下一帧所需要的时间。
//你应该在动作的最后一帧插入一个延时为0的帧表示结束，此时显示为播放完毕,可以添加下一个帧。
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

//结束节点
extern ActionNode ActionNode_END;

//序列步进，查看是否应该到下一个动作帧，你因该相对频繁的调用它
void SequenceOnStep(int pastTime);
//设置当前队列
void SetSequence(ActionNode actions[]);
//查看队列是否完成
bool IsFinished(void);

#endif
