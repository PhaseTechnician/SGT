#include "OrderClass.h"

#include "BSP.h"

void OrderDistributeTask(void)
{
	while(1)
	{
	//从队列获取指令
	
	//分发指令到其他队列
	
	

	  char order[BSP_Serial_MaxOrderLength+1]={0};
		BSP_Serial_Read(order);
		BSP_Serial_SendString(order);
	}
}

void OrderCMDTask(void)
{
	while(1)
	{
	//从队列获取CMD命令
	
	//处理CMD命令
	}
}
