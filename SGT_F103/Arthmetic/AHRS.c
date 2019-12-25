#include "AHRS.h"
#include "RotationRelated.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>

EulerAngle GetInitalEularAngle(Vector3 acc)
{
  EulerAngle eularAngle;
  eularAngle.pitch = V2GetAngleFormV1toV2(NewV2(acc.y, acc.z), Vector2_nY);
  if (acc.y > 0)
    eularAngle.pitch = -eularAngle.pitch;
  eularAngle.roll = V2GetAngleFormV1toV2(NewV2(acc.x, acc.z), Vector2_nY);
  if (acc.x < 0)
    eularAngle.roll = -eularAngle.roll;
  eularAngle.yaw = 0;
  return eularAngle;
}

void Update()
{
  float KP = 0.8f;
  float KI = 0.001f;
  Vector3 accleration;
  Vector3 gravity;
  Vector3 omg;
  Vector3 mag;
  Vector3 error;
  Vector3 errorInt;
  Quaternion quaternion;
  float period = 1.0f;
  period += 1.0f;

  V3Normalize_Itself(&accleration);
  V3Normalize_Itself(&omg);
  V3Normalize_Itself(&mag);
  EulerAngle angle = QuaternionToEulerAngles(quaternion);
  V3Normalize_Itself((Vector3 *)&angle);

  error = V3Cross(accleration, gravity);
  errorInt = V3Add(errorInt, V3Scale_New(KI, error));
  gravity = V3Add(V3Add(gravity, V3Scale_New(KP, error)), errorInt);

  V4Normalize_Itself(&quaternion);
  angle = QuaternionToEulerAngles(quaternion);
}
