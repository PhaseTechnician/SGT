#ifndef _MATHEXTENSIONTYPE_H
#define _MATHEXTENSIONTYPE_H

typedef struct Vector2Struct
{
    float x;
    float y;
} Vector2;

typedef struct Vector3Struct
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct Vector4Struct
{
    float x;
    float y;
    float z;
    float w;
} Vector4;

typedef struct EulerAngleStruct
{
    float roll;
    float yaw;
    float pitch;
} EulerAngle;

typedef struct RotationMatrixStructure
{
    float matrix[3][3];
} RotationMatrix;

typedef Vector4 Quaternion;

Vector2 NewV2(float x, float y);
Vector3 NewV3(float x, float y, float z);
Vector4 NewV4(float x,float y,float z,float w);

#endif
