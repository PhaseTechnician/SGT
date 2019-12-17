#ifndef _FUNCTIONCMD_H
#define _FUNCTIONCMD_H

#include "FreeRTOS_CLI.h"

//首次调用CMD指令需要花一些时间挂载CMD

//调用一个CMD指令
void CallCMD(char *order);

#endif
