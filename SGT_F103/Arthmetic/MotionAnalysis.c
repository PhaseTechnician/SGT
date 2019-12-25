#include "MotionAnalysis.h"

void ApplyMaskWithFactor(float *speed,unsigned char mask,float Factor)
{
	*(speed+0) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
	mask<<=1;
	*(speed+1) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
	mask<<=1;
	*(speed+2) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
	mask<<=1;
	*(speed+3) += Factor * ((mask & 0x80?1:0) - (mask & 0x08?1:0));
}
