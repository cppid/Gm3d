#ifndef GM3D_VEC2_HPP
#define GM3D_VEC2_HPP

#include <cmath>
#include <type_traits>

namespace gm3d {

template<typename T>
class Vec2 {
  T x_, y_;

public:
  Vec2() noexcept = default;

  explicit Vec2(T s) noexcept
  : Vec2{s, s}
  {
  }

  Vec2(T x, T y) noexcept
  : x_{x}
  , y_{y}
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
    x_ = rhs.x();
    y_ = rhs.y();
    return *this;
  }

  Vec2&
  operator+=(const Vec2& rhs) noexcept
  {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }

  Vec2&
  operator+=(T rhs) noexcept
  {
    x_ += rhs;
    y_ += rhs;
    return *this;
  }

  Vec2&
  operator-=(const Vec2& rhs) noexcept
  {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  Vec2&
  operator-=(T rhs) noexcept
  {
    x_ -= rhs;
    y_ -= rhs;
    return *this;
  }

  Vec2&
  operator*=(const Vec2& rhs) noexcept
  {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    return *this;
  }

  Vec2&
  operator*=(T rhs) noexcept
  {
    x_ *= rhs;
    y_ *= rhs;
    return *this;
  }

  Vec2&
  operator/=(const Vec2& rhs) noexcept
  {
    x_ /= rhs.x_;
    y_ /= rhs.y_;
    return *this;
  }

  Vec2&
  operator/=(T rhs) noexcept
  {
    x_ /= rhs;
    y_ /= rhs;
    return *this;
  }

  void
  x(T val) noexcept
  {
    x_ = val;
  }

  void
  y(T val) noexcept
  {
    y_ = val;
  }

  T
  x() const noexcept
  {
    return x_;
  }

  T
  y() const noexcept
  {
    return y_;
  }

  T
  dot(const Vec2& other) const noexcept
  {
    return x_ * other.x_ + y_ * other.y_;
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
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
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
    return {lhs.x_ + rhs.x_, lhs.y_ + rhs.y_};
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
    return {-lhs.x_, -lhs.y_};
  }

  friend Vec2
  operator-(const Vec2& lhs, const Vec2& rhs) noexcept
  {
    return {lhs.x_ - rhs.x_, lhs.y_ - rhs.y_};
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
    return {lhs.x_ * rhs.x_, lhs.y_ * rhs.y_};
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
    return {lhs.x_ / rhs.x_, lhs.y_ / rhs.y_};
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
