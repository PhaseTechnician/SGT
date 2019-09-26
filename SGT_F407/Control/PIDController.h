#ifndef _PIDCONTROLLER_H
#define _PIDCONTROLLER_H

/*
 * PID 控制器
 * 主要用于电机系统的速度控制
 * 通过结构体来实现控制器的多实例使用
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
 
//完成一次PID控制操作，获得本次的输出值
int FinishOnePIDStep(PIDInstance * instance,int feedBackValue);
//初始化一个PID实例
void InitOnePIDInstance(PIDInstance * instance,int goalValue,float KP,float KI,float KD);
//临时修改目标值
void SetPIDGoalValue(PIDInstance * instance,int goalValue);


#endif
