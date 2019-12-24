#ifndef _VECTOR3_H
#define _VECTOR3_H

typedef struct Vector3Struct
{
    float x;
    float y;
    float z;
} Vector3;

//以下基础定义基于 右手系 左右为X，前后为Y，上下为Z
extern const Vector3 Vector3_One;
extern const Vector3 Vector3_Zero;
extern const Vector3 Vector3_Forward;
extern const Vector3 Vector3_Backward;
extern const Vector3 Vector3_Left;
extern const Vector3 Vector3_Right;
extern const Vector3 Vector3_Up;
extern const Vector3 Vector3_Down;

//单位化
Vector3 V3Normalize_New(Vector3 const vector);
void V3Normalize_Itself(Vector3 *vector);
//数乘
Vector3 V3Scale_New(float scale, Vector3 const vector);
void V3Scale_Itself(float scale, Vector3 *vector);
//点乘
float V3Dot(Vector3 const vector1, Vector3 const vector2);
//叉乘
Vector3 V3Cross(Vector3 const vector1, Vector3 const vector2);
//求模长
float V3Length(Vector3 const vector);
//求和
Vector3 V3Add(Vector3 const vector1, Vector3 const vector2);
//求差
Vector3 V3Subtract(Vector3 const vector1, Vector3 const vector2);

#endif
