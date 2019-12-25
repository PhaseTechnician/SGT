#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "MathExtensionType.h"

//以下基础定义基于 右手系 左右为X，前后为Y，上下为Z
extern const Vector2 Vector2_One;
extern const Vector2 Vector2_Zero;
extern const Vector2 Vector2_pX;
extern const Vector2 Vector2_pY;
extern const Vector2 Vector2_nX;
extern const Vector2 Vector2_nY;


//单位化
Vector2 V2Normalize_New(Vector2 const vector);
void V2Normalize_Itself(Vector2 *vector);
//数乘
Vector2 V2Scale_New(float scale, Vector2 const vector);
void V2Scale_Itself(float scale, Vector2 *vector);
//点乘
float V2Dot(Vector2 const vector1, Vector2 const vector2);
//叉乘
float V2Cross(Vector2 const vector1, Vector2 const vector2);
//求模长
float V2Length(Vector2 const vector);
//求和
Vector2 V2Add(Vector2 const vector1, Vector2 const vector2);
//求差
Vector2 V2Subtract(Vector2 const vector1, Vector2 const vector2);
//求角度
float V2GetAngleFormV1toV2(Vector2 const vector1, Vector2 const vector2);

#endif
