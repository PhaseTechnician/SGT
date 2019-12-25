#include "Vector4.h"
#include "math.h"

const Vector4 Vector4_One = {1.0f, 1.0f, 1.0f, 1.0f};
const Vector4 Vector4_Zero = {0.0f, 0.0f, 0.0f, 0.0f};

//单位化
Vector4 V4Normalize_New(Vector4 const vector)
{
    float length = V4Length(vector);
    return V4Scale_New(1 / length, vector);
}
void V4Normalize_Itself(Vector4 *vector)
{
    float length = V4Length(*vector);
    V4Scale_Itself(1 / length, vector);
}
//数乘
Vector4 V4Scale_New(float scale, Vector4 const vector)
{
    Vector4 newVector = vector;
    V4Scale_Itself(scale, &newVector);
    return newVector;
}
void V4Scale_Itself(float scale, Vector4 *vector)
{
    vector->x *= scale;
    vector->y *= scale;
    vector->z *= scale;
    vector->w *= scale;
}
//点乘
float V4Dot(Vector4 const vector1, Vector4 const vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z + vector1.w * vector2.w;
}

//求模长
inline float V4Length(Vector4 const vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z+vector.w*vector.w);
}
//求和
Vector4 V4Add(Vector4 const vector1, Vector4 const vector2)
{
    Vector4 vector;
    vector.x = vector1.x + vector2.x;
    vector.y = vector1.y + vector2.y;
    vector.z = vector1.z + vector2.z;
    vector.w = vector1.w+vector2.w;
    return vector;
}
//求差
Vector4 V4Subtract(Vector4 const vector1, Vector4 const vector2)
{
    Vector4 vector;
    vector.x = vector1.x - vector2.x;
    vector.y = vector1.y - vector2.y;
    vector.z = vector1.z - vector2.z;
    vector.w = vector1.w-vector2.w;
    return vector;
}
