#ifndef GM3D_VEC2_HPP
#define GM3D_VEC2_HPP

#include <cmath>
#include <type_traits>

namespace gm3d {

template<typename T>
struct Vec2 {
  T elems[2];

  Vec2() noexcept = default;

  explicit Vec2(T s) noexcept
  : Vec2{s, s}
  {
  }

  Vec2(T x, T y) noexcept
  : elems{x, y}
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit Vec2(Vec2<U> v) noexcept
  : Vec2(v.x(), v.y())
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  Vec2(Vec2<U> v) noexcept
  : Vec2(v.x(), v.y())
  {
  }

  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
  Vec2&
  operator=(const Vec2<U> rhs) noexcept
  {
    elems[0] = rhs.x();
    elems[1] = rhs.y();
    return *this;
  }

  Vec2&
  operator+=(const Vec2& rhs) noexcept
  {
    elems[0] += rhs.elems[0];
    elems[1] += rhs.elems[1];
    return *this;
  }

  Vec2&
  operator+=(T rhs) noexcept
  {
    elems[0] += rhs;
    elems[1] += rhs;
    return *this;
  }

  Vec2&
  operator-=(const Vec2& rhs) noexcept
  {
    elems[0] -= rhs.elems[0];
    elems[1] -= rhs.elems[1];
    return *this;
  }

  Vec2&
  operator-=(T rhs) noexcept
  {
    elems[0] -= rhs;
    elems[1] -= rhs;
    return *this;
  }

  Vec2&
  operator*=(const Vec2& rhs) noexcept
  {
    elems[0] *= rhs.elems[0];
    elems[1] *= rhs.elems[1];
    return *this;
  }

  Vec2&
  operator*=(T rhs) noexcept
  {
    elems[0] *= rhs;
    elems[1] *= rhs;
    return *this;
  }

  Vec2&
  operator/=(const Vec2& rhs) noexcept
  {
    elems[0] /= rhs.elems[0];
    elems[1] /= rhs.elems[1];
    return *this;
  }

  Vec2&
  operator/=(T rhs) noexcept
  {
    elems[0] /= rhs;
    elems[1] /= rhs;
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
  dot(const Vec2& other) const noexcept
  {
    return elems[0] * other.elems[0] + elems[1] * other.elems[1];
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

  Vec2
  to_unit() const noexcept
  {
    return *this / magnitude();
  }

  Vec2
  reflect(const Vec2& n) const noexcept
  {
    return *this - 2 * dot(n) * n;
  }

  friend bool
  operator==(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return lhs.elems[0] == rhs.elems[0] && lhs.elems[1] == rhs.elems[1];
  }

  friend bool
  operator!=(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  friend Vec2
  operator+(const Vec2& val) noexcept
  {
    return val;
  }

  friend Vec2
  operator+(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return {lhs.elems[0] + rhs.elems[0], lhs.elems[1] + rhs.elems[1]};
  }

  friend Vec2
  operator+(const Vec2& lhs, T rhs) noexcept
  {
    return lhs + Vec2{rhs};
  }

  friend Vec2
  operator+(T lhs, const Vec2& rhs) noexcept
  {
    return Vec2{lhs} + rhs;
  }

  friend Vec2
  operator-(const Vec2& lhs) noexcept
  {
    return {-lhs.elems[0], -lhs.elems[1]};
  }

  friend Vec2
  operator-(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return {lhs.elems[0] - rhs.elems[0], lhs.elems[1] - rhs.elems[1]};
  }

  friend Vec2
  operator-(const Vec2& lhs, T rhs) noexcept
  {
    return lhs - Vec2{rhs};
  }

  friend Vec2
  operator-(T lhs, const Vec2& rhs) noexcept
  {
    return Vec2{lhs} - rhs;
  }

  friend Vec2 operator*(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return {lhs.elems[0] * rhs.elems[0], lhs.elems[1] * rhs.elems[1]};
  }

  friend Vec2 operator*(const Vec2& lhs, T rhs) noexcept
  {
    return lhs * Vec2{rhs};
  }

  friend Vec2 operator*(T lhs, const Vec2& rhs) noexcept
  {
    return Vec2{lhs} * rhs;
  }

  friend Vec2
  operator/(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return {lhs.elems[0] / rhs.elems[0], lhs.elems[1] / rhs.elems[1]};
  }

  friend Vec2
  operator/(const Vec2& lhs, T rhs) noexcept
  {
    return lhs / Vec2{rhs};
  }

  friend Vec2
  operator/(T lhs, const Vec2& rhs) noexcept
  {
    return Vec2{lhs} / rhs;
  }
};

} // namespace gm3d

#endif
