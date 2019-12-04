#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "BSP.h"
#include "Application.h"


TaskHandle_t Serial_HANDLE;

int main()
{
	//��ʼ��Ӳ���豸
	BSP_Modles_Config();
	BSP_Serial_SendString("STM32 INIT FINISH");
	
	//�������񴴽�
	Application_TaskCreat();
	//�����������	
	vTaskStartScheduler();
	return 0;
}
