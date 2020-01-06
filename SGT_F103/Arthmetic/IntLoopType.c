#include "IntLoopType.h"

int getMinDifference_INT(LoopIntType type, int valueA, int ValueB)
{
    int width = type.maxValue - type.minValue;
    int difference = valueA > ValueB ? valueA - ValueB : ValueB - valueA;
    if (width / 2 > difference)
    {
        if (valueA > ValueB)
        {
            if (type.antiTurning)
            {
                return difference;
            }
            return -difference;
        }
        else
        {
            if (type.antiTurning)
            {
                return difference;
            }
            return difference;
        }
    }
    else
    {
        if (valueA < ValueB)
        {
            if (type.antiTurning)
            {
                return difference;
            }
            return -difference;
        }
        else
        {
            if (type.antiTurning)
            {
                return difference;
            }
            return difference;
        }
    }
}
void LOOP_INT_ADD(LoopIntType type, int *value, int addValue)
{
    *value += addValue;
    while (*value > type.maxValue)
    {
        *value = *value - type.maxValue + type.minValue;
    }
}
void LOOP_INT_SUB(LoopIntType type, int *value, int subValue)
{
    *value -= subValue;
    while (*value < type.minValue)
    {
        *value = type.maxValue - type.minValue + *value;
    }
}
