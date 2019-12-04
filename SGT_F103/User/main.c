#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "BSP.h"
#include "Application.h"


TaskHandle_t Serial_HANDLE;

int main()
{
	//初始化硬件设备
	BSP_Modles_Config();
	BSP_Serial_SendString("STM32 INIT FINISH");
	
	//调用任务创建
	Application_TaskCreat();
	//任务调度启动	
	vTaskStartScheduler();
	return 0;
}
