#include "RotationRelated.h"
#include <math.h>
Quaternion EulerAnglesToQuaternion(EulerAngle eulerAngle)
{
    Quaternion quaternion;
    float cosRoll = cosf(eulerAngle.roll * 0.5f);
    float sinRoll = sinf(eulerAngle.roll * 0.5f);

    float cosPitch = cosf(eulerAngle.pitch * 0.5f);
    float sinPitch = sinf(eulerAngle.pitch * 0.5f);

    float cosYam = cosf(eulerAngle.yaw * 0.5f);
    float sinYaw = sinf(eulerAngle.yaw * 0.5f);

    quaternion.w = cosRoll * cosPitch * cosYam + sinRoll * sinPitch * sinYaw;
    quaternion.x = sinRoll * cosPitch * cosYam - cosRoll * sinPitch * sinYaw;
    quaternion.y = cosRoll * sinPitch * cosYam + sinRoll * cosPitch * sinYaw;
    quaternion.z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYam;
		return quaternion;
}

RotationMatrix QuaternionToRotationMatrix(Quaternion quaternion)
{
    RotationMatrix rotationMaterix;

    float xx = quaternion.x * quaternion.x;
    float yy = quaternion.y * quaternion.y;
    float zz = quaternion.z * quaternion.z;
    float xw = quaternion.x * quaternion.w;
    float yw = quaternion.y * quaternion.w;
    float zw = quaternion.z * quaternion.w;
    float xy = quaternion.x * quaternion.y;
    float xz = quaternion.x * quaternion.z;
    float yz = quaternion.y * quaternion.z;

    rotationMaterix.matrix[0][0] = 1.0f - 2.0f * yy - 2.0f * zz;
    rotationMaterix.matrix[0][1] = 2.0f * (xy + -zw);
    rotationMaterix.matrix[0][2] = 2.0f * (xz - -yw);

    rotationMaterix.matrix[1][0] = 2.0f * (xy - -zw);
    rotationMaterix.matrix[1][1] = 1.0f - 2.0f * xx - 2.0f * zz;
    rotationMaterix.matrix[1][2] = 2.0f * (yz + -xw);

    rotationMaterix.matrix[2][0] = 2.0f * (xz + -yw);
    rotationMaterix.matrix[2][1] = 2.0f * (yz - -xw);
    rotationMaterix.matrix[2][2] = 1.0f - 2.0f * xx - 2.0f * yy;
    return rotationMaterix;
}

EulerAngle QuaternionToEulerAngles(Quaternion quaternion)
{
    EulerAngle eulerAngle;
    eulerAngle.roll = atan2f(2.0f * (quaternion.z * quaternion.y + quaternion.w * quaternion.x),
                             quaternion.w * quaternion.w - quaternion.x * quaternion.x - quaternion.y * quaternion.y + quaternion.z * quaternion.z);
    eulerAngle.pitch = asinf(2.0f * (quaternion.w * quaternion.y - quaternion.x * quaternion.z));
    eulerAngle.yaw = atan2f(2.0f * (quaternion.x * quaternion.y + quaternion.w * quaternion.z),
                            quaternion.w * quaternion.w + quaternion.x * quaternion.x - quaternion.y * quaternion.y - quaternion.z * quaternion.z);
    return eulerAngle;
}
