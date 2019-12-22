#include "ExtenedFunctionClass.h"
#include "BSP.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Application.h"
#include "stdio.h"
#include "string.h"

void BeepNoisyTask(void)
{
	ExtenedBeepOrder beepOrder;
	while(1)
	{
		//获取蜂鸣器信号控制量
		xQueueReceive(ExtenedBeepOrderHandle,&beepOrder,portMAX_DELAY);
		//进行响应
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
		//获取LED信号控制量
		xQueueReceive(ExtenedLEDOrderHandle,&ledOrder,portMAX_DELAY);
		//做出效果
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

void LCDDisplayTask(void)
{
	BSP_LCD12864_Clear();
	int times = 0;
	TickType_t timeDelay = 0;
	while(1)
	{
		unsigned char code;
		static char LCDBuffer[16];
		memset(LCDBuffer, 0, sizeof(LCDBuffer));
		xQueueReceive(KeyCodeHandler,&code,0);
		sprintf(LCDBuffer,"Time is %d",times);
		BSP_LCD12864_WriteAtLine_EN(LCDBuffer,0);
		vTaskDelay(10);
		memset(LCDBuffer, 0, sizeof(LCDBuffer));
		sprintf(LCDBuffer,"KeyCode: %3X",code);
		BSP_LCD12864_WriteAtLine_EN(LCDBuffer,1);
		times++;
		vTaskDelayUntil(&timeDelay,1000);
	}
}

void KeyBoardScanTask(void)
{
	unsigned char lastCode;
	while(1)
	{
		unsigned char code = BSP_KeyBoard_GetCode();
		if(code!=lastCode)
		{
			lastCode = code;
			xQueueSend(KeyCodeHandler,&code,0);
			BSP_LED_Open();
			vTaskDelay(200);
			BSP_LED_Close();
		}
		vTaskDelay(50);
	}
}
