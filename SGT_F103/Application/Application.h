#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "DebugClass.h"
#include "MotionControlClass.h"
#include "ExtenedFunctionClass.h"
#include "OrderClass.h"

extern TaskHandle_t StatePrintTaskHandler;
extern TaskHandle_t EncoderReadTaskHandler;
extern TaskHandle_t AttitudeSolutionTaskHandler;
extern TaskHandle_t MotorSpeedControlTaskHandler;
extern TaskHandle_t MotionControlTaskHandler;
extern TaskHandle_t BeepNoisyTaskHandler;
extern TaskHandle_t OrderDistributeTaskHandler;
//extern TaskHandle_t OrderCMDTaskHandler;

void Application_TaskCreat(void);

extern xQueueHandle MontorSpeedHandle;
extern xQueueHandle MontorTragetSpeedHandle;
extern xQueueHandle AttitudeHandle;
extern xQueueHandle MotionControlOrderHandle;
extern xQueueHandle ExtenedLEDOrderHandle;
extern xQueueHandle ExtenedBeepOrderHandle;

void Application_PipeCreat(void);

#endif
