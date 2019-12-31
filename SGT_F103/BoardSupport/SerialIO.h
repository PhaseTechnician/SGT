#ifndef _SERIALIO_H
#define _SERIALIO_H

/*
 * 使用74LS165十六位IO并行转串行
 * PB2  SCLK
 * PD2  LOCK
 * PC12 QHIN
 */
#include "stm32f10x.h"

//初始化扩展IO
void BSP_SerialIO_Config(void);
//读取一个字节数据
uint8_t BSP_SerialIO_ReadByte(void);
//读取两个字节数据
uint16_t BSP_SerialIO_Read2Bytes(void);

#endif
