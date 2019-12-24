#include "ArrayOperation.h"

float GetAverageOfIntArray(int array[], int count)
{
    float tempValue = 0;
    for (int i = 0; i < count; i++)
    {
        tempValue += array[i];
    }
    return tempValue;
}
float GetAverageOfFloatArray(float array[], int count)
{
    float tempValue = 0;
    for (int i = 0; i < count; i++)
    {
        tempValue += array[i];
    }
    return tempValue;
}
