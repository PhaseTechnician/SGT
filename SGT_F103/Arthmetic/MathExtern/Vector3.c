#include "Vector3.h"
#include "math.h"

const Vector3 Vector3_One = {1.0f, 1.0f, 1.0f};
const Vector3 Vector3_Zero = {0.0f, 0.0f, 0.0f};
const Vector3 Vector3_Forward = {0.0f, 1.0f, 0.0f};
const Vector3 Vector3_Backward = {0.0f, -1.0f, 0.0f};
const Vector3 Vector3_Left = {-1.0f, 0.0f, 0.0f};
const Vector3 Vector3_Right = {1.0f, 0.0f, 0.0f};
const Vector3 Vector3_Up = {0.0f, 0.0f, 1.0f};
const Vector3 Vector3_Down = {0.0f, 0.0f, -1.0f};

//单位化
Vector3 V3Normalize_New(Vector3 const vector)
{
    float length = V3Length(vector);
    return V3Scale_New(1 / length, vector);
}
void V3Normalize_Itself(Vector3 *vector)
{
    float length = V3Length(*vector);
    V3Scale_Itself(1 / length, vector);
}
//数乘
Vector3 V3Scale_New(float scale, Vector3 const vector)
{
    Vector3 newVector = vector;
    V3Scale_Itself(scale, &newVector);
    return newVector;
}
void V3Scale_Itself(float scale, Vector3 *vector)
{
    vector->x *= scale;
    vector->y *= scale;
    vector->z *= scale;
}
//点乘
float V3Dot(Vector3 const vector1, Vector3 const vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}
//叉乘
Vector3 V3Cross(Vector3 const vector1, Vector3 const vector2)
{
    Vector3 crossVector;
    crossVector.x = vector1.y * vector2.z - vector2.y * vector1.z;
    crossVector.y = vector1.z * vector2.x - vector2.z * vector1.x;
    crossVector.z = vector1.x * vector2.y - vector2.x * vector1.y;
    return crossVector;
}
//求模长
inline float V3Length(Vector3 const vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
//求和
Vector3 V3Add(Vector3 const vector1, Vector3 const vector2)
{
    Vector3 vector;
    vector.x = vector1.x + vector2.x;
    vector.y = vector1.y + vector2.y;
    vector.z = vector1.z + vector2.z;
    return vector;
}
//求差
Vector3 V3Subtract(Vector3 const vector1, Vector3 const vector2)
{
    Vector3 vector;
    vector.x = vector1.x - vector2.x;
    vector.y = vector1.y - vector2.y;
    vector.z = vector1.z - vector2.z;
    return vector;
}
