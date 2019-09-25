#include "SequenceController.h"

ActionNode *tempArrays = 0;
bool stateFinish = true;
int tempTick = 0;

ActionNode ActionNode_Empty = {0,0};

void SequenceOnStep(int pastTime)
{
	if(!stateFinish)
	{
		tempTick-=pastTime;
		if(tempTick <= 0)//继续当前动作
		{
			tempArrays++;
			if(tempArrays->delayTimes!=0)
			{
				tempTick = tempArrays->delayTimes;
				ServerSetAngle(tempArrays->frame->angle1,SERVER_1);
				ServerSetAngle(tempArrays->frame->angle2,SERVER_2);
				ServerSetAngle(tempArrays->frame->angle3,SERVER_3);
				ServerSetAngle(tempArrays->frame->angle4,SERVER_4);
			}
			else
			{
				//序列播放完毕
				tempTick=0;
				tempArrays=0;
				stateFinish = true;
			}
		}
	}
}

void SetSequence(ActionNode actions[])
{
	if(stateFinish)
	{
		tempArrays = actions;
		stateFinish = false;
	}
	else
	{
		ErrorMessage("Sequence Un Finished");
	}
}

inline bool IsSequenceFinished(void)
{
	return stateFinish;
}
