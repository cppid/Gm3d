#ifndef GM3D_VEC3_HPP
#define GM3D_VEC3_HPP

#include <cmath>
#include <type_traits>

namespace gm3d {

template<typename T>
struct Vec3 {
  T elems[3];

  Vec3() noexcept = default;

  explicit Vec3(T s) noexcept
  : Vec3{s, s, s}
  {
  }

  Vec3(T x, T y, T z) noexcept
  : elems{x, y, z}
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit Vec3(Vec3<U> v) noexcept
  : Vec3(v.x(), v.y(), v.z())
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  Vec3(Vec3<U> v) noexcept
  : Vec3(v.x(), v.y(), v.z())
  {
  }

  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
  Vec3&
  operator=(const Vec3<U> rhs) noexcept
  {
    elems[0] = rhs.x();
    elems[1] = rhs.y();
    elems[2] = rhs.z();
    return *this;
  }

  Vec3&
  operator+=(const Vec3& rhs) noexcept
  {
    elems[0] += rhs.elems[0];
    elems[1] += rhs.elems[1];
    elems[2] += rhs.elems[2];
    return *this;
  }

  Vec3&
  operator+=(T rhs) noexcept
  {
    elems[0] += rhs;
    elems[1] += rhs;
    elems[2] += rhs;
    return *this;
  }

  Vec3&
  operator-=(const Vec3& rhs) noexcept
  {
    elems[0] -= rhs.elems[0];
    elems[1] -= rhs.elems[1];
    elems[2] -= rhs.elems[2];
    return *this;
  }

  Vec3&
  operator-=(T rhs) noexcept
  {
    elems[0] -= rhs;
    elems[1] -= rhs;
    elems[2] -= rhs;
    return *this;
  }

  Vec3&
  operator*=(const Vec3& rhs) noexcept
  {
    elems[0] *= rhs.elems[0];
    elems[1] *= rhs.elems[1];
    elems[2] *= rhs.elems[2];
    return *this;
  }

  Vec3&
  operator*=(T rhs) noexcept
  {
    elems[0] *= rhs;
    elems[1] *= rhs;
    elems[2] *= rhs;
    return *this;
  }

  Vec3&
  operator/=(const Vec3& rhs) noexcept
  {
    elems[0] /= rhs.elems[0];
    elems[1] /= rhs.elems[1];
    elems[2] /= rhs.elems[2];
    return *this;
  }

  Vec3&
  operator/=(T rhs) noexcept
  {
    elems[0] /= rhs;
    elems[1] /= rhs;
    elems[2] /= rhs;
    return *this;
  }

  void
  x(T val) noexcept
  {
    elems[0] = val;
  }

  void
  y(T val) noexcept
  {
    elems[1] = val;
  }

  void
  z(T val) noexcept
  {
    elems[2] = val;
  }

  T
  x() const noexcept
  {
    return elems[0];
  }

  T
  y() const noexcept
  {
    return elems[1];
  }

  T
  z() const noexcept
  {
    return elems[2];
  }

  T
  dot(const Vec3& other) const noexcept
  {
    return elems[0] * other.elems[0] + elems[1] * other.elems[1] + elems[2] * other.elems[2];
  }

  T
  magnitude() const noexcept
  {
    return std::sqrt(dot(*this));
  }

  T
  magnitude_squared() const noexcept
  {
    return dot(*this);
  }

  Vec3
  to_unit() const noexcept
  {
    return *this / magnitude();
  }

  Vec3
  cross(const Vec3& other) const noexcept
  {
    return {elems[1] * other.elems[2] - elems[2] * other.elems[1],
            elems[2] * other.elems[0] - elems[0] * other.elems[2],
            elems[0] * other.elems[1] - elems[1] * other.elems[0]};
  }

  Vec3
  reflect(const Vec3& n) const noexcept
  {
    return *this - 2 * dot(n) * n;
  }

  friend bool
  operator==(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return lhs.elems[0] == rhs.elems[0] && lhs.elems[1] == rhs.elems[1] && lhs.elems[2] == rhs.elems[2];
  }

  friend bool
  operator!=(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  friend Vec3
  operator+(const Vec3& val) noexcept
  {
    return val;
  }

  friend Vec3
  operator+(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return {lhs.elems[0] + rhs.elems[0], lhs.elems[1] + rhs.elems[1], lhs.elems[2] + rhs.elems[2]};
  }

  friend Vec3
  operator+(const Vec3& lhs, T rhs) noexcept
  {
    return lhs + Vec3{rhs};
  }

  friend Vec3
  operator+(T lhs, const Vec3& rhs) noexcept
  {
    return Vec3{lhs} + rhs;
  }

  friend Vec3
  operator-(const Vec3& lhs) noexcept
  {
    return {-lhs.elems[0], -lhs.elems[1], -lhs.elems[2]};
  }

  friend Vec3
  operator-(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return {lhs.elems[0] - rhs.elems[0], lhs.elems[1] - rhs.elems[1], lhs.elems[2] - rhs.elems[2]};
  }

  friend Vec3
  operator-(const Vec3& lhs, T rhs) noexcept
  {
    return lhs - Vec3{rhs};
  }

  friend Vec3
  operator-(T lhs, const Vec3& rhs) noexcept
  {
    return Vec3{lhs} - rhs;
  }

  friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return {lhs.elems[0] * rhs.elems[0], lhs.elems[1] * rhs.elems[1], lhs.elems[2] * rhs.elems[2]};
  }

  friend Vec3 operator*(const Vec3& lhs, T rhs) noexcept
  {
    return lhs * Vec3{rhs};
  }

  friend Vec3 operator*(T lhs, const Vec3& rhs) noexcept
  {
    return Vec3{lhs} * rhs;
  }

  friend Vec3
  operator/(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return {lhs.elems[0] / rhs.elems[0], lhs.elems[1] / rhs.elems[1], lhs.elems[2] / rhs.elems[2]};
  }

  friend Vec3
  operator/(const Vec3& lhs, T rhs) noexcept
  {
    return lhs / Vec3{rhs};
  }

  friend Vec3
  operator/(T lhs, const Vec3& rhs) noexcept
  {
    return Vec3{lhs} / rhs;
  }
};

} // namespace gm3d

#endif
