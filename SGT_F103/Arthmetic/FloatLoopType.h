#ifndef _FLOATLOOPTYPE_H
#define _FLOATLOOPTYPE_H

#include <stdbool.h>

/*提供一种对循环变化的事物的描述*/
typedef struct LoopFloatTypeStruct
{
    float maxValue;
    float minValue;
    bool antiTurning;
}LoopFloatType;

float getMinDifference_FLOAT(LoopFloatType type,float valueA,float ValueB);
void LOOP_FLOAT_ADD(LoopFloatType type,float *value,float addValue);
void LOOP_FLOAT_SUB(LoopFloatType type,float *value,float subValue);

#endif
