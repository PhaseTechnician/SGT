#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "DebugClass.h"
#include "ExtenedFunctionClass.h"
#include "MotionControlClass.h"
#include "OrderClass.h"

extern TaskHandle_t StatePrintTaskHandler;
extern TaskHandle_t EncoderReadTaskHandler;
extern TaskHandle_t AttitudeSolutionTaskHandler;
extern TaskHandle_t MotorSpeedControlTaskHandler;
extern TaskHandle_t MotionControlTaskHandler;
extern TaskHandle_t OrderDistributeTaskHandler;
//extern TaskHandle_t OrderCMDTaskHandler;
extern TaskHandle_t LEDControlsTaskHandler;
extern TaskHandle_t BeepNoisyTaskHandler;
extern TaskHandle_t LCDDisplayTaskHandler;
extern TaskHandle_t KeyBoardScanTaskHandler;

void Application_TaskCreat(void);

extern xQueueHandle MontorSpeedHandle;
extern xQueueHandle MontorTragetSpeedHandle;
extern xQueueHandle AttitudeHandle;
extern xQueueHandle MotionControlOrderHandle;
extern xQueueHandle ExtenedLEDOrderHandle;
extern xQueueHandle ExtenedBeepOrderHandle;
extern xQueueHandle KeyCodeHandler;

void Application_PipeCreat(void);

#endif
