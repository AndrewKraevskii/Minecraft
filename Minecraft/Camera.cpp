#include "Camera.h"

#include <glut.h>
#include <math.h>

void Camera::moveglobal(Vector3d shift) { position += shift; }

void Camera::movelocal(Vector3d shift) {
  position += shift.x * direction.unit_vector();
  position += (up_vector - (direction * up_vector / direction.mod()) *
                               direction.unit_vector()).unit_vector() *
              shift.z;
  position += (cross(up_vector, direction)).unit_vector() * shift.y;
}

void Camera::setglobal_pos(Vector3d pos) { position = pos; }

void Camera::setlocal_pos(Vector3d pos) {
  position = {0, 0, 0};
  position += pos.x * direction.unit_vector();
  position += (up_vector - (direction * up_vector / direction.mod()) *
                               direction.unit_vector()) *
              pos.z;
  position += cross(up_vector, direction).unit_vector() * pos.y;
}

void Camera::setupvector(Vector3d vec) { up_vector = vec; }

void Camera::rotate_g(radian angle) {
  double cos_theta = cos(angle);
  double sin_theta = sin(angle);

  direction =
      (direction * cos_theta) +
      (cross(up_vector.unit_vector(), direction) * sin_theta) +
      (up_vector.unit_vector() * (up_vector.unit_vector() * direction)) *
          (1 - cos_theta);
}

void Camera::rotate_v(radian angle) {
  double cur_angle = acos((direction.unit_vector() * up_vector.unit_vector()));

  if (cur_angle - angle <= 0.01 && -angle < 0) {
    return;
  }
  if (cur_angle - angle >= atan(1) * 4 - 0.01 && -angle > 0) {
    return;
  }

  Vector3d v = cross(direction, up_vector).unit_vector();

  double cos_theta = cos(angle);
  double sin_theta = sin(angle);

  direction = (direction * cos_theta) + (cross(v, direction) * sin_theta) +
              (v * (v * direction)) * (1 - cos_theta);
}

void Camera::put_camera() {
  gluLookAt(position.x, position.y, position.z, position.x + direction.x,
            position.y + direction.y, position.z + direction.z, up_vector.x,
            up_vector.y, up_vector.z);
}
