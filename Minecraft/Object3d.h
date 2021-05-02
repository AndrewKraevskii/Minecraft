#pragma once

#include <fstream>
#include <string>
#include <vector>

template <typename T>
class Vector2 {
 public:
  Vector2() : x(0), y(0) {}
  Vector2(T X, T Y) : x(X), y(Y) {}

  template <typename U>
  explicit Vector2(const Vector2<U>& vector) : x((T)vector.x), y((T)vector.y) {}
  T x;
  T y;
};

template <typename T>
class Vector3 {
 public:
  Vector3() : x(0), y(0), z(0) {}

  Vector3(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

  template <typename U>
  explicit Vector3(const Vector3<U>& vector)
      : x((T)vector.x), y((T)vector.y), z((T)vector.z) {}
  T x;
  T y;
  T z;
};

typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;

class Object3d {
  uint32_t texture[1];
  std::vector<Vector3d> vertexes;
  std::vector<Vector2d> UVs;
  std::vector<Vector3d> normals;
  std::vector<std::vector<Vector3i>> faces;

  void loadOBJ(std::string file_name);

 public:
  Object3d(std::string file_name);

  void draw();

  ~Object3d();
};
