#include "OrderClass.h"

#include "BSP.h"
#include "Application.h"


void OrderDistributeTask(void)
{
	while(1)
	{
		char order[BSP_Serial_MaxOrderLength+1]={0};
		//�Ӷ��л�ȡָ��
		BSP_Serial_Read(order);
		//�ַ�ָ���������
		bool Error=false;
		switch(order[0])
		{
			case '>'://CMD����
				break;
			case 'L'://��Դ����
				switch(order[1])
				{
					ExtendLEDOrder LEDOrder;
					case 'O'://���ع�Դ����
						if(order[2]=='O')
						{
							LEDOrder=ExtenedOrder_LED_Board_On;
							if(!xQueueSend(ExtenedLEDOrderHandle,&LEDOrder,10))
							{
								BSP_Serial_SendString("ERROR LED QUEUE");
							}
						}
						else if(order[2]=='C')
						{
							LEDOrder=ExtenedOrder_LED_Board_Off;
							if(!xQueueSend(ExtenedLEDOrderHandle,&LEDOrder,10))
							{
								BSP_Serial_SendString("ERROR LED QUEUE");
							}
						}
						else if(order[2]=='B')
						{
							LEDOrder=ExtenedOrder_LED_Board_Blink;
							if(!xQueueSend(ExtenedLEDOrderHandle,&LEDOrder,10))
							{
								BSP_Serial_SendString("ERROR LED QUEUE");
							}
						}
						else
							Error=true;
						break;
					default:
						Error=true;
						break;
				}
				break;
			default:
				Error=true;
				break;
		}
		if(Error)
		{
			BSP_Serial_SendString("ERROR ORDER\n");
		}
	}
}

void OrderCMDTask(void)
{
	while(1)
	{
	//�Ӷ��л�ȡCMD����
	vTaskDelay(500);
	//����CMD����
	}
}
