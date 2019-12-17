#include "ExtenedFunctionClass.h"
#include "BSP.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Application.h"

void BeepNoisyTask(void)
{
	ExtenedBeepOrder beepOrder;
	while(1)
	{
		//��ȡ�������źſ�����
		xQueueReceive(ExtenedBeepOrderHandle,&beepOrder,portMAX_DELAY);
		//������Ӧ
		if(beepOrder==ExtenedOrder_Beep_On)
		{
				
		}
		else
		{
				
		}
	}
}

void LED_Board_Blink(void)
{
	while(1)
	{
		BSP_LED_Open();
		vTaskDelay(400);
		BSP_LED_Close();
		vTaskDelay(400);
	}
}

TaskHandle_t LED_Board_BlinkHandler;

void LEDControlsTask(void)
{
	ExtendLEDOrder ledOrder;
	xTaskCreate((TaskFunction_t)LED_Board_Blink,(const char*)"LED_OnBoard_Blink",
		(uint16_t)50,(void*)NULL,(UBaseType_t)1,(TaskHandle_t*)&LED_Board_BlinkHandler);
	vTaskSuspend(LED_Board_BlinkHandler);
	while(1)
	{
		//��ȡLED�źſ�����
		xQueueReceive(ExtenedLEDOrderHandle,&ledOrder,portMAX_DELAY);
		//����Ч��
		switch(ledOrder)
		{
			case ExtenedOrder_LED_Board_On:
				vTaskSuspend(LED_Board_BlinkHandler);
				BSP_LED_Open();
				break;
			case ExtenedOrder_LED_Board_Off:
				vTaskSuspend(LED_Board_BlinkHandler);
				BSP_LED_Close();
				break;
			case ExtenedOrder_LED_Board_Blink:
				vTaskResume(LED_Board_BlinkHandler);
				break;
			default:
				break;	
		}
		
	}
}

