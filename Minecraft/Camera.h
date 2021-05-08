#pragma once

#include "vectors.h"

class Camera {
  Vector3d position;
  Vector3d direction;
  Vector3d up_vector;

 public:
  Camera() : position{0, 0, 0}, direction{0, 0, 0}, up_vector{0, 0, 1} {}
  Camera(Vector3d position, Vector3d rotation, Vector3d up_vector = {0, 0, 1})
      : position{position}, direction{rotation}, up_vector{up_vector} {}

  void moveglobal(Vector3d shift);
  void movelocal(Vector3d shift);

  void move() {}
};
