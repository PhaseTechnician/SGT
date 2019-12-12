#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "BSP.h"
#include "Application.h"

int main()
{
	//��ʼ��Ӳ���豸
	BSP_Modles_Config();
	BSP_Serial_SendString("BSP Load Finish\n");
	//�������񴴽�
	Application_TaskCreat();
	BSP_Serial_SendString("Application Creat Finish\n");
	//ͨ�Źܵ�����
	Application_PipeCreat();
	BSP_Serial_SendString("Pipe Creat Finish\n");
	//�����������	
	vTaskStartScheduler();
	return 0;
}
