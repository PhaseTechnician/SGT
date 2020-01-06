#ifndef _INTLOOPTYPE_H
#define _INTLOOPTYPE_H

#include <stdbool.h>

/*提供一种对循环变化的事物的描述*/
typedef struct LoopIntTypeStruct
{
    int maxValue;
    int minValue;
    bool antiTurning;
}LoopIntType;

int getMinDifference_INT(LoopIntType type,int valueA,int ValueB);
void LOOP_INT_ADD(LoopIntType type,int *value,int addValue);
void LOOP_INT_SUB(LoopIntType type,int *value,int subValue);

#endif
