#include "FloatLoopType.h"

float getMinDifference_FLOAT(LoopFloatType type, float valueA, float ValueB)
{
    float width = type.maxValue - type.minValue;
    float difference = valueA > ValueB ? valueA - ValueB : ValueB - valueA;
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
void LOOP_FLOAT_ADD(LoopFloatType type, float *value, float addValue)
{
    *value += addValue;
    while (*value > type.maxValue)
    {
        *value = *value - type.maxValue + type.minValue;
    }
}
void LOOP_FLOAT_SUB(LoopFloatType type, float *value, float subValue)
{
    *value -= subValue;
    while (*value < type.minValue)
    {
        *value = type.maxValue - type.minValue + *value;
    }
}
