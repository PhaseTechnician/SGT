#include "Application.h"
#include "DebugClass.h"
#include "MotionControlClass.h"
#include "ExtenedFunctionClass.h"
#include "OrderClass.h"

TaskHandle_t StatePrintTaskHandler;
TaskHandle_t EncoderReadTaskHandler;
TaskHandle_t AttitudeSolutionTaskHandler;
TaskHandle_t MotorSpeedControlTaskHandler;
TaskHandle_t MotionControlTaskHandler;
TaskHandle_t OrderDistributeTaskHandler;
TaskHandle_t OrderCMDTaskHandler;
TaskHandle_t LEDControlsTaskHandler;
TaskHandle_t BeepNoisyTaskHandler;

void Application_TaskCreat(void)
{
	/*
	xTaskCreate((TaskFunction_t)StatePrintTask,(const char*)"StatePrintTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)1,(TaskHandle_t*)&StatePrintTaskHandler);*/
		
	xTaskCreate((TaskFunction_t)EncoderReadTask,(const char*)"EncoderReadTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)2,(TaskHandle_t*)&EncoderReadTaskHandler);
		
	xTaskCreate((TaskFunction_t)AttitudeSolutionTask,(const char*)"AttitudeSolutionTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)3,(TaskHandle_t*)&AttitudeSolutionTaskHandler);
		
	xTaskCreate((TaskFunction_t)MotorSpeedControlTask,(const char*)"MotorSpeedControlTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)4,(TaskHandle_t*)&MotorSpeedControlTaskHandler);
		
	xTaskCreate((TaskFunction_t)MotionControlTask,(const char*)"MotionControlTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)5,(TaskHandle_t*)&MotionControlTaskHandler);
		
	xTaskCreate((TaskFunction_t)OrderDistributeTask,(const char*)"OrderDistributeTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)6,(TaskHandle_t*)&OrderDistributeTaskHandler);
		
	xTaskCreate((TaskFunction_t)OrderCMDTask,(const char*)"OrderCMDTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)7,(TaskHandle_t*)&OrderCMDTaskHandler);
		
	xTaskCreate((TaskFunction_t)LEDControlsTask,(const char*)"LEDControlsTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)8,(TaskHandle_t*)&LEDControlsTaskHandler);
		
	xTaskCreate((TaskFunction_t)BeepNoisyTask,(const char*)"BeepNoisyTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)9,(TaskHandle_t*)&BeepNoisyTaskHandler);
	
}

