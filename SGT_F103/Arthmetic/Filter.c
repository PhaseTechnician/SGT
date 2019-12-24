#include "Filter.h"

#ifdef FILTER_SLIDER_USE
void SliderFilter_PushOneInt(SliderIntFilter *filterInstance, int value)
{
    filterInstance->index++;
    if (filterInstance->index == filterInstance->capicity)
    {
        filterInstance->index = 0;
    }
    filterInstance->valuePtr[filterInstance->index] = value;
}
void SliderFilter_PushOneFloat(SliderFloatFilter *filterInstance, float value)
{
    filterInstance->index++;
    if (filterInstance->index == filterInstance->capicity)
    {
        filterInstance->index = 0;
    }
    filterInstance->valuePtr[filterInstance->index] = value;
}
#endif
