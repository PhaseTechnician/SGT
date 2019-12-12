#include <stdio.h>
#include "CLI.h"

typedef enum ParamTypeEnum
{
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_BOOL,
	TYPE_STRING,
	TYPE_CHAR
}ParamType;

typedef enum ErrorTypeEnum
{
	ERROR_UNDEFINE,
}ErrorType;

typedef struct CMDStruct
{
	const char* functionName;
	const int paramCount;
	ParamType typeList[3];
	void * FunctionPtr;
}CMD;

const CMD* CMDList = {0};
//临时处理变量
char* functionName;
int paramsCount;
ParamType typeList[3];
char* paramList[3];

bool DivideString(char *string)
{

}

float FloatPhrase(char* floatString)
{

}

int IntPhrase(char* IntString)
{

}

bool DealOneOrder(char* orderString)
{
	if(!DivideString(orderString))
	{
		for(int i = 0; i < sizeof(CMDList)/sizeof(CMD*); i++)
		{
			if (CMDList[i].functionName == functionName && paramsCount == CMDList[i].paramCount)
			{

			}
			else
			{

			}
		}
	}
}