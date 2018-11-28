#ifndef GM3D_VEC3_HPP
#define GM3D_VEC3_HPP

#include <cmath>
#include <type_traits>

namespace gm3d {

template<typename T>
class Vec3 {
  T x_, y_, z_;

public:
  Vec3() noexcept = default;

  explicit Vec3(T s) noexcept
  : Vec3{s, s, s}
  {
  }

  Vec3(T x, T y, T z) noexcept
  : x_{x}
  , y_{y}
  , z_{z}
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
    x_ = rhs.x();
    y_ = rhs.y();
    z_ = rhs.z();
    return *this;
  }

  Vec3&
  operator+=(const Vec3& rhs) noexcept
  {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
  }

  Vec3&
  operator+=(T rhs) noexcept
  {
    x_ += rhs;
    y_ += rhs;
    z_ += rhs;
    return *this;
  }

  Vec3&
  operator-=(const Vec3& rhs) noexcept
  {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
  }

  Vec3&
  operator-=(T rhs) noexcept
  {
    x_ -= rhs;
    y_ -= rhs;
    z_ -= rhs;
    return *this;
  }

  Vec3&
  operator*=(const Vec3& rhs) noexcept
  {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;
    return *this;
  }

  Vec3&
  operator*=(T rhs) noexcept
  {
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;
    return *this;
  }

  Vec3&
  operator/=(const Vec3& rhs) noexcept
  {
    x_ /= rhs.x_;
    y_ /= rhs.y_;
    z_ /= rhs.z_;
    return *this;
  }

  Vec3&
  operator/=(T rhs) noexcept
  {
    x_ /= rhs;
    y_ /= rhs;
    z_ /= rhs;
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

  void
  z(T val) noexcept
  {
    z_ = val;
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
  z() const noexcept
  {
    return z_;
  }

  T
  dot(const Vec3& other) const noexcept
  {
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
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
    return {y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_};
  }

  Vec3
  reflect(const Vec3& n) const noexcept
  {
    return *this - 2 * dot(n) * n;
  }

  friend bool
  operator==(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
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
    return {lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_};
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
    return {-lhs.x_, -lhs.y_, -lhs.z_};
  }

  friend Vec3
  operator-(const Vec3& lhs, const Vec3& rhs) noexcept
  {
    return {lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_};
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
    return {lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_};
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
    return {lhs.x_ / rhs.x_, lhs.y_ / rhs.y_, lhs.z_ / rhs.z_};
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
