#ifndef _VECTOR4_H
#define _VECTOR4_H

#include "MathExtensionType.h"

extern const Vector4 Vector4_One;
extern const Vector4 Vector4_Zero;

//单位化
Vector4 V4Normalize_New(Vector4 const vector);
void V4Normalize_Itself(Vector4 *vector);
//数乘
Vector4 V4Scale_New(float scale, Vector4 const vector);
void V4Scale_Itself(float scale, Vector4 *vector);
//点乘
float V4Dot(Vector4 const vector1, Vector4 const vector2);
//叉乘
//Vector4 V4Cross(Vector4 const vector1, Vector4 const vector2);
//求模长
float V4Length(Vector4 const vector);
//求和
Vector4 V4Add(Vector4 const vector1, Vector4 const vector2);
//求差
Vector4 V4Subtract(Vector4 const vector1, Vector4 const vector2);

#endif
