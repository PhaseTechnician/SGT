#include "MotionAnalysis.h"
unsigned char orientation;
unsigned int speed;

void SetOrientation(unsigned char LocalOrientation)
{
	orientation = LocalOrientation;
	SetMontorRotation(LocalOrientation&0b00001000,MONTOR_FRONT_LEFT);
	SetMontorRotation(LocalOrientation&0b00000100,MONTOR_FRONT_RIGHT);
	SetMontorRotation(LocalOrientation&0b00000010,MONTOR_BACK_LEFT);
	SetMontorRotation(LocalOrientation&0b00000001,MONTOR_BACK_RIGHT);
}

inline void SetSpeed(unsigned int LineSpeed)
{
	speed = LineSpeed;
}

void MotionAnalysisOnStep(void)
{
	SetMontorSpeed(speed,MONTOR_FRONT_LEFT);
	SetMontorSpeed(speed,MONTOR_FRONT_RIGHT);
	SetMontorSpeed(speed,MONTOR_BACK_LEFT);
	SetMontorSpeed(speed,MONTOR_BACK_RIGHT);
}
