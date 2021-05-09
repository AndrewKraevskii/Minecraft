#pragma once
#include <math.h>

template <typename T>
class Vector2 {
 public:
  Vector2();
  Vector2(T X, T Y);

  Vector2 unit_vector() { return *this / mod(); }

  double mod() { return sqrt(this->x * this->x + this->y * this->y); }

  template <typename U>
  explicit Vector2(const Vector2<U>& vector);
  T x;
  T y;
};

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>::Vector2() : x(0), y(0) {}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>::Vector2(T X, T Y) : x(X), y(Y) {}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vector)
    : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator-(const Vector2<T>& right) {
  return Vector2<T>(-right.x, -right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right) {
  left.x += right.x;
  left.y += right.y;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right) {
  left.x -= right.x;
  left.y -= right.y;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) {
  return Vector2<T>(left.x + right.x, left.y + right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) {
  return Vector2<T>(left.x - right.x, left.y - right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator*(const Vector2<T>& left, T right) {
  return Vector2<T>(left.x * right, left.y * right);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator*(T left, const Vector2<T>& right) {
  return Vector2<T>(right.x * left, right.y * left);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator*=(Vector2<T>& left, T right) {
  left.x *= right;
  left.y *= right;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline double operator*(const Vector2<T>& left, const Vector2<T>& right) {
  return right.x * left.x + right.y * left.y;
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator/(const Vector2<T>& left, T right) {
  return Vector2<T>(left.x / right, left.y / right);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator/=(Vector2<T>& left, T right) {
  left.x /= right;
  left.y /= right;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline bool operator==(const Vector2<T>& left, const Vector2<T>& right) {
  return (left.x == right.x) && (left.y == right.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline bool operator!=(const Vector2<T>& left, const Vector2<T>& right) {
  return (left.x != right.x) || (left.y != right.y);
}

template <typename T>
class Vector3 {
 public:
  Vector3();

  Vector3(T X, T Y, T Z);

  Vector3 unit_vector() { return *this / mod(); }

  double mod() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
  }

  template <typename U>
  explicit Vector3(const Vector3<U>& vector);

  T x;
  T y;
  T z;
};

template <typename T>
inline Vector3<T>::Vector3() : x(0), y(0), z(0) {}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T>::Vector3(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
inline Vector3<T>::Vector3(const Vector3<U>& vector)
    : x(static_cast<T>(vector.x)),
      y(static_cast<T>(vector.y)),
      z(static_cast<T>(vector.z)) {}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> operator-(const Vector3<T>& left) {
  return Vector3<T>(-left.x, -left.y, -left.z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right) {
  left.x += right.x;
  left.y += right.y;
  left.z += right.z;

  return left;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T>& first, const Vector3<T>& second) {
  return Vector3<T>(first.y * second.z - first.z * second.y,
                 first.z * second.x - first.x * second.z,
                 first.x * second.y - first.y * second.x);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right) {
  left.x -= right.x;
  left.y -= right.y;
  left.z -= right.z;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right) {
  return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) {
  return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> operator*(const Vector3<T>& left, T right) {
  return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> operator*(T left, const Vector3<T>& right) {
  return Vector3<T>(right.x * left, right.y * left, right.z * left);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T>& operator*=(Vector3<T>& left, T right) {
  left.x *= right;
  left.y *= right;
  left.z *= right;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline double operator*(const Vector3<T>& left, const Vector3<T>& right) {
  return right.x * left.x + right.y * left.y + right.z * left.z;
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> operator/(const Vector3<T>& left, T right) {
  return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T>& operator/=(Vector3<T>& left, T right) {
  left.x /= right;
  left.y /= right;
  left.z /= right;

  return left;
}

////////////////////////////////////////////////////////////
template <typename T>
inline bool operator==(const Vector3<T>& left, const Vector3<T>& right) {
  return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline bool operator!=(const Vector3<T>& left, const Vector3<T>& right) {
  return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;
