#include "Vector2.h"
#include "math.h"

const Vector2 Vector2_One = {1.0f, 1.0f};
const Vector2 Vector2_Zero = {0.0f, 0.0f};
const Vector2 Vector2_pX = {1.0f, 0.0f};
const Vector2 Vector2_pY = {0.0f, 1.0f};
const Vector2 Vector2_nX = {-1.0f, 0.0f};
const Vector2 Vector2_nY = {0.0f, -1.0f};

//单位化
Vector2 V2Normalize_New(Vector2 const vector)
{
    float length = V2Length(vector);
    return V2Scale_New(1 / length, vector);
}
void V2Normalize_Itself(Vector2 *vector)
{
    float length = V2Length(*vector);
    V2Scale_Itself(1 / length, vector);
}
//数乘
Vector2 V2Scale_New(float scale, Vector2 const vector)
{
    Vector2 newVector = vector;
    V2Scale_Itself(scale, &newVector);
    return newVector;
}
void V2Scale_Itself(float scale, Vector2 *vector)
{
    vector->x *= scale;
    vector->y *= scale;
}
//点乘
float V2Dot(Vector2 const vector1, Vector2 const vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y;
}
//叉乘
float V2Cross(Vector2 const vector1, Vector2 const vector2)
{
    return vector1.x * vector2.y - vector2.x * vector1.y;
}
//求模长
inline float V2Length(Vector2 const vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y );
}
//求和
Vector2 V2Add(Vector2 const vector1, Vector2 const vector2)
{
    Vector2 vector;
    vector.x = vector1.x + vector2.x;
    vector.y = vector1.y + vector2.y;
    return vector;
}
//求差
Vector2 V2Subtract(Vector2 const vector1, Vector2 const vector2)
{
    Vector2 vector;
    vector.x = vector1.x - vector2.x;
    vector.y = vector1.y - vector2.y;
    return vector;
}
//求取夹角
float V2GetAngleFormV1toV2(Vector2 const vector1, Vector2 const vector2)
{
    return acosf(V2Dot(vector1, vector2) / V2Length(vector1) / V2Length(vector2));
}
