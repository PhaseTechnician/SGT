#include "Application.h"
#include "BSP.h"

TaskHandle_t StatePrintTaskHandler;
TaskHandle_t EncoderReadTaskHandler;
TaskHandle_t AttitudeSolutionTaskHandler;
TaskHandle_t MotorSpeedControlTaskHandler;
TaskHandle_t MotionControlTaskHandler;
TaskHandle_t OrderDistributeTaskHandler;
//TaskHandle_t OrderCMDTaskHandler;
TaskHandle_t LEDControlsTaskHandler;
TaskHandle_t BeepNoisyTaskHandler;
TaskHandle_t LCDDisplayTaskHandler;
TaskHandle_t KeyBoardScanTaskHandler;

void Application_TaskCreat(void)
{

//	xTaskCreate((TaskFunction_t)StatePrintTask,(const char*)"StatePrintTask",
//		(uint16_t)50,(void*)NULL,(UBaseType_t)1,(TaskHandle_t*)&StatePrintTaskHandler);
	
	xTaskCreate((TaskFunction_t)EncoderReadTask,(const char*)"EncoderReadTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)2,(TaskHandle_t*)&EncoderReadTaskHandler);

//	xTaskCreate((TaskFunction_t)AttitudeSolutionTask,(const char*)"AttitudeSolutionTask",
//		(uint16_t)50,(void*)NULL,(UBaseType_t)3,(TaskHandle_t*)&AttitudeSolutionTaskHandler);

	xTaskCreate((TaskFunction_t)MotorSpeedControlTask,(const char*)"MotorSpeedControlTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)4,(TaskHandle_t*)&MotorSpeedControlTaskHandler);

	xTaskCreate((TaskFunction_t)MotionControlTask,(const char*)"MotionControlTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)5,(TaskHandle_t*)&MotionControlTaskHandler);

	xTaskCreate((TaskFunction_t)OrderDistributeTask,(const char*)"OrderDistributeTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)6,(TaskHandle_t*)&OrderDistributeTaskHandler);

//  CMD 目前只会直接调用目标函数一次
//	xTaskCreate((TaskFunction_t)OrderCMDTask,(const char*)"OrderCMDTask",
//		(uint16_t)50,(void*)NULL,(UBaseType_t)7,(TaskHandle_t*)&OrderCMDTaskHandler);

	xTaskCreate((TaskFunction_t)LEDControlsTask,(const char*)"LEDControlsTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)1,(TaskHandle_t*)&LEDControlsTaskHandler);

	xTaskCreate((TaskFunction_t)BeepNoisyTask,(const char*)"BeepNoisyTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)1,(TaskHandle_t*)&BeepNoisyTaskHandler);
	
	xTaskCreate((TaskFunction_t)LCDDisplayTask,(const char*)"LCDDisplayTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)1,(TaskHandle_t*)&LCDDisplayTaskHandler);
		
	xTaskCreate((TaskFunction_t)KeyBoardScanTask,(const char*)"KeyBoardScanTask",
		(uint16_t)50,(void*)NULL,(UBaseType_t)2,(TaskHandle_t*)&KeyBoardScanTaskHandler);
}

xQueueHandle MontorSpeedHandle;
xQueueHandle MontorTragetSpeedHandle;
xQueueHandle AttitudeHandle;
xQueueHandle MotionControlOrderHandle;
xQueueHandle ExtenedLEDOrderHandle;
xQueueHandle ExtenedBeepOrderHandle;
xQueueHandle KeyCodeHandler;

#define CreatNewPipe(handler,length,messageStruct,pipeName) {handler=xQueueCreate(length,sizeof(messageStruct));if(handler==NULL){BSP_Serial_SendString("Application_Pipe_Creat_Failed\n");BSP_Serial_SendString(pipeName);BSP_Serial_SendChar('\n');}}

void Application_PipeCreat(void)
{
	CreatNewPipe(MontorSpeedHandle,1,MontorSpeed,"MontorSpeed");
	CreatNewPipe(MontorTragetSpeedHandle,1,MontorSpeed,"MontorTragetSpeed");
	CreatNewPipe(AttitudeHandle,1,float,"Attitude");
	CreatNewPipe(MotionControlOrderHandle,1,MotionControlOrder,"MotionControlOrder");
	CreatNewPipe(ExtenedLEDOrderHandle,3,ExtendLEDOrder,"ExtenedLEDOrder");
	CreatNewPipe(ExtenedBeepOrderHandle,1,ExtenedBeepOrder,"ExtenedBeepOrder");
	CreatNewPipe(KeyCodeHandler,20,unsigned char,"KeyCode");
}

