#ifndef _AHRS_H
#define _AHRS_H
/*
 * PITCH    - x
 * ROLL     - y
 * YAW      - z
 */
#include "MathExtensionType.h"
 
//获取初始的欧拉角
EulerAngle GetInitalEularAngle(Vector3 acc);

void Update(void);

#endif
