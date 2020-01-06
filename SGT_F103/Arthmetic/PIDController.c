#include "PIDController.h"

int FinishOnePIDStep(PIDInstance *instance, int feedbackValue)
{
	instance->feedback = feedbackValue;
	instance->lastError = instance->presentError;
	instance->presentError = instance->goal - instance->feedback;
	instance->presentOutput = instance->lastOutput + instance->KP * instance->presentError + instance->KI * (instance->lastError + instance->presentError) + instance->KD * (instance->presentError - instance->lastError);
	instance->lastOutput = instance->presentOutput;
	//范围保证
	if (instance->presentOutput > edge.MAXOUT)
	{
		return edge.MAXOUT;
	}
	else if (instance->presentOutput < edge.MINOUT)
	{
		return edge.MINOUT;
	}
	return instance->presentOutput;
}

int FinishOnePDStep(PIDInstance *instance, int feedbackValue)
{
	instance->feedback = feedbackValue;
	instance->lastError = instance->presentError;
	instance->presentError = instance->goal - instance->feedback;
	instance->presentOutput = instance->lastOutput + instance->KP * instance->presentError + instance->KD * (instance->presentError - instance->lastError);
	instance->lastOutput = instance->presentOutput;
	//范围保证
	if (instance->presentOutput > edge.MAXOUT)
	{
		return edge.MAXOUT;
	}
	else if (instance->presentOutput < edge.MINOUT)
	{
		return edge.MINOUT;
	}
	return instance->presentOutput;
}

int FinishOneLogicalPDStep(PIDInstance *instance, int feedbackValue)
{
	if ((feedbackValue - instance->goal) > 0 ? (feedbackValue - instance->goal) : (instance->goal - feedbackValue) < edge.MAXDIFF)
	{
		return FinishOnePDStep(instance, feedbackValue);
	}
	else
	{
		return instance->goal > feedbackValue ? edge.MINOUT : edge.MAXOUT;
	}
}

void InitOnePIDInstance(PIDInstance *instance, int goalValue, float KP, float KI, float KD)
{
	instance->goal = goalValue;
	instance->feedback = 0;
	instance->presentError = 0;
	instance->lastError = 0;
	instance->presentOutput = 0;
	instance->lastError = 0;
	instance->KP = KP;
	instance->KI = KI;
	instance->KD = KD;
}

inline void ResetPIDGoalValue(PIDInstance *instance, int goalValue)
{
	instance->goal = goalValue;
}
