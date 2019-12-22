#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "stm32f10x.h"
#include "stdbool.h"
/*
 * IIC 1
 * PB9 SDA PB10 SCL
 * ¼üÂëÈçÏÂ£º
 * 		1		2		3		4		5		6		7		8	
 * A+	44	4C	54	5C	64	6C	74	N
 * A-	04	0C	14	1C	24	2C	34 	N
 * B+	45	4D	55	5D	65	6D	75	N
 * B- 05	0D	15	1D	25	2D	35	N
 * C+ 46	4E	56	5E	66	6E	76	N
 * C- 06	0E	16	1E	26	2E	36	N
 * D+ 47	4F	57	5F	67	6F	77	N
 * D- 07	0F	17	1F	27	2F	37	N
 */

void BSP_KeyBoard_Config(void);
unsigned char BSP_KeyBoard_GetCode(void);
bool BSP_KeyBoard_IsUp(unsigned char code);
bool BSP_KeyBoard_IsDown(unsigned char code);
unsigned char BSP_KeyBoard_GetCodeName(unsigned char code);

#endif
