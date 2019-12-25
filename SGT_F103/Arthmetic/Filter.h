#ifndef _FILTER_H
#define _FILTER_H

/*
 * 
 */
/*
typedef struct FirstOrderComplementaryFilterStruct
{
    float KP;
}FOCFilter;

float Filter_FOC_Step(FOCFilter filter,float value1,float value2);*/

/*
 * Slider 滑动滤波器
 * Capacity 滤波容量
 * 基于循环数组实现，填入新值时覆盖最为老旧的值
 */
typedef struct SliderIntFilter
{
    int capicity;
    int *valuePtr;
    int index;
} SliderIntFilter;

typedef struct SliderFloatFilter
{
    int capicity;
    float *valuePtr;
    int index;
} SliderFloatFilter;

void SliderFilter_PushOneInt(SliderIntFilter *filterInstance, int value);
void SliderFilter_PushOneFloat(SliderFloatFilter *filterInstance, float value);

#endif
