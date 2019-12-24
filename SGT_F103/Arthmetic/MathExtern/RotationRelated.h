#ifndef _ROTATIONRELATED_H
#define _ROTATIONRELATED_H

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

typedef struct QuaternionStructure
{
    float x;
    float y;
    float z;
    float w;
} Quaternion;

Quaternion EulerAnglesToQuaternion(EulerAngle eulerAngle);
RotationMatrix QuaternionToRotationMatrix(Quaternion quaternion);
EulerAngle QuaternionToEulerAngles(Quaternion quaternion);

#endif
