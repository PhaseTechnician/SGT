#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "BSP.h"
#include "Application.h"

//256KB ROM 48KB RAM

int main()
{
	//初始化硬件设备
	BSP_Modles_Config();
	BSP_Serial_SendString("BSP Load Finish\n");
	BSP_MPU_WakeUp();
	//工作任务创建
	Application_TaskCreat();
	BSP_Serial_SendString("Application Creat Finish\n");
	//通信管道建立
	Application_PipeCreat();
	BSP_Serial_SendString("Pipe Creat Finish\n");
	//任务调度启动	
	vTaskStartScheduler();
	return 0;
}
