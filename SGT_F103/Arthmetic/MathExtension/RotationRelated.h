#ifndef _ROTATIONRELATED_H
#define _ROTATIONRELATED_H

#include "MathExtensionType.h"

Quaternion EulerAnglesToQuaternion(EulerAngle eulerAngle);
RotationMatrix QuaternionToRotationMatrix(Quaternion quaternion);
EulerAngle QuaternionToEulerAngles(Quaternion quaternion);

#endif
