#include "OrderClass.h"

#include "BSP.h"

void OrderDistributeTask(void)
{
	while(1)
	{
	//�Ӷ��л�ȡָ��
	
	//�ַ�ָ���������
	
	

	  char order[BSP_Serial_MaxOrderLength+1]={0};
		BSP_Serial_Read(order);
		BSP_Serial_SendString(order);
	}
}

void OrderCMDTask(void)
{
	while(1)
	{
	//�Ӷ��л�ȡCMD����
	
	//����CMD����
	}
}
