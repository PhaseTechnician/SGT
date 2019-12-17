#include "FunctionCMD.h"
#include "BSP.h"

#include "stdio.h"

bool IsCMDCallFirst = true;
#define CMDLineLength 100//一行最多多长
static char OutPutBuffer[CMDLineLength] = {0};

/*任务编写部分*/

static BaseType_t HelloCMD( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
	snprintf(pcWriteBuffer,xWriteBufferLen,"Hello,CMD is online\n");
	return pdFALSE;
}
static const CLI_Command_Definition_t HelloCommand =
{
	"hello",
	"hello:\n Just a Test Function\n",
	HelloCMD,
	0
};

static BaseType_t PrintCMD( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
	const char* paramter;
	BaseType_t lengthOfParam;
	paramter=FreeRTOS_CLIGetParameter(pcCommandString,1,&lengthOfParam);//1代表第一个参数
	if(paramter!=NULL)
	{
		snprintf(pcWriteBuffer,lengthOfParam+1,"%s\n",paramter);
	}
	return pdFALSE;
}
static const CLI_Command_Definition_t PrintCommand =
{
	"print",
	"print <string>:\n FeedBack your input message\n",
	PrintCMD,
	1
};

/*调用系统部分*/
void InitCMD(void)
{
	BSP_Serial_SendString("Strat load CMD function\n");
	FreeRTOS_CLIRegisterCommand(&HelloCommand);
	FreeRTOS_CLIRegisterCommand(&PrintCommand);
	BSP_Serial_SendString("Load fineshed\n");
}

void CallCMD(char *order)
{
	if(IsCMDCallFirst)
	{
		InitCMD();
		IsCMDCallFirst=false;
	}
	BaseType_t Return;
	do
	{
		Return = FreeRTOS_CLIProcessCommand(order,OutPutBuffer,CMDLineLength );
		BSP_Serial_SendString(OutPutBuffer);
	} while( Return != pdFALSE );
}
