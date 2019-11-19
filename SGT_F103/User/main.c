#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "BSP.h"

void LED_Blink_Task(void)
{
	while(1)
	{
		BSP_LED_Open();
		vTaskDelay(500);
		BSP_LED_Close();
		vTaskDelay(500);
	}
}

void Serial_Task(void)
{
	while(1)
	{
	  char order[BSP_Serial_MaxOrderLength+1]={0};
		BSP_Serial_Read(order);
		BSP_Serial_SendString(order);
	}
}

TaskHandle_t LED_HANDLE;
TaskHandle_t Serial_HANDLE;


int main()
{
	//��ʼ��Ӳ���豸
	BSP_Modles_Config();
	
	BSP_Serial_SendString("STM32 INIT FINISH");
	
	//������ʼ����
  xTaskCreate((TaskFunction_t )LED_Blink_Task,         //������
                (const char*    )"LED_Blink",          //��������
                (uint16_t       )50,        						//�����ջ��С
                (void*          )NULL,      						//���ݸ��������Ĳ���
                (UBaseType_t    )3,         						//�������ȼ�
                (TaskHandle_t*  )&LED_HANDLE);   			//������  
	xTaskCreate((TaskFunction_t )Serial_Task,         //������
                (const char*    )"Serial",          //��������
                (uint16_t       )50,        						//�����ջ��С
                (void*          )NULL,      						//���ݸ��������Ĳ���
                (UBaseType_t    )2,         						//�������ȼ�
                (TaskHandle_t*  )&Serial_HANDLE);   			//������  		
	vTaskStartScheduler();
	return 0;
}
