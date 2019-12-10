#ifndef _MOTIONCONTROLCLASS_H
#define _MOTIONCONTROLCLASS_H

typedef struct MontorSpeedStruct
{
	float speed1;
	float speed2;
	float speed3;
	float speed4;
}MontorSpeed;
typedef MontorSpeed MontorTragetSpeed;

typedef enum MotionTypeEnum
{
	MotionType_Translate_Forward,
	MotionType_Translate_Backward,
	MotionType_Translate_Left,
	MotionType_Translate_Right,
	MotionType_Rotate_Clock,
	MotionType_Rotate_AntiClock,
	MotionType_Speed_Up,
	MotionType_Speed_Down,
	MotionType_Speed_Brake
}MotionType;

typedef struct MotionControlOrderStruct
{
	MotionType motion;
	float value;
}MotionControlOrder;

//±àÂëÆ÷¶ÁÈ¡ºÍ½âÎö
void EncoderReadTask(void);

void AttitudeSolutionTask(void);

void MotorSpeedControlTask(void);

void MotionControlTask(void);

#endif
