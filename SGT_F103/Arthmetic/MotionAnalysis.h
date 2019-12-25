#ifndef _MOTIONANALYSIS_H
#define _MOTIONANALYSIS_H

/*
 * 对四个轮子的速度进行分析和控制
 * 局部坐标系：
 *   1+x 2   
 *   +yoy-
 *   3-x 4  
 */

//轮操作掩码 高四位正向使能 低四位反向使能
#define WHEEL_MASK_CLOCK          0XA5//0b10100101
#define WHEEL_MASK_ANTICLOCK      0X5A//0b01011010
#define WHEEL_MASK_FORWARD        0XF0//0b11110000
#define WHEEL_MASK_BACKWARD       0X0F//0b00001111
#define WHEEL_MASK_LEFT           0X69//0b01101001
#define WHEEL_MASK_RIGHT          0X96//0b10010110
#define WHEEL_MASK_LEFT_FORWARD   0X60//0b01100000
#define WHEEL_MASK_RIGHT_FORWARD  0X90//0b10010000
#define WHEEL_MASK_LEFT_BACKWARD  0X09//0b00001001
#define WHEEL_MASK_RIGHT_BACKWARD 0X06//0b00000110
#define WHEEL_MASK_EMPTY          0X00//0b00000000

//注意无论如何，三项之和不得超过最大电机速度
//同时，需要留出一定的范围为PID控制提供操作余量

void ApplyMaskWithFactor(float *speed,unsigned char mask,float Factor);

#endif
