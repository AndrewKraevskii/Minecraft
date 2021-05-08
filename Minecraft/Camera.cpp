#include "Camera.h"

#include <math.h>

void Camera::moveglobal(Vector3d shift) { position += shift; }

void Camera::movelocal(Vector3d shift) {
  position += shift.x * direction.unit_vector();
  position += (up_vector - (direction * up_vector / direction.mod()) *
                               direction.unit_vector()) *
              shift.z;
  position += up_vector.vmul(direction) * shift.y;
}
