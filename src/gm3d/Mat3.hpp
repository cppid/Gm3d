#ifndef MOLPHENE_M3D_MAT3_HPP
#define MOLPHENE_M3D_MAT3_HPP

#include "Mat4.hpp"

namespace gm3d {
template<typename T>
struct Mat3 {
  T m[9];

  Mat3() noexcept = default;

  explicit Mat3(T s) noexcept
  : Mat3{s, 0, 0, 0, s, 0, 0, 0, s}
  {
  }

  Mat3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) noexcept
  : m{m00, m01, m02, m10, m11, m12, m20, m21, m22}
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit Mat3(const Mat4<U>& m4) noexcept
  : Mat3(m4.m[0],
         m4.m[1],
         m4.m[2],
         m4.m[4],
         m4.m[5],
         m4.m[6],
         m4.m[8],
         m4.m[9],
         m4.m[10])
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  Mat3(const Mat4<U>& m4) noexcept
  : Mat3(m4.m[0],
         m4.m[1],
         m4.m[2],
         m4.m[4],
         m4.m[5],
         m4.m[6],
         m4.m[8],
         m4.m[9],
         m4.m[10])
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            !std::is_convertible_v<U, T>>* = nullptr>
  explicit Mat3(const Mat3<U>& m3) noexcept
  : Mat3(m3.m[0],
         m3.m[1],
         m3.m[2],
         m3.m[3],
         m3.m[4],
         m3.m[5],
         m3.m[6],
         m3.m[7],
         m3.m[8])
  {
  }

  template<typename U,
           std::enable_if_t<std::is_constructible_v<T, U> &&
                            std::is_convertible_v<U, T>>* = nullptr>
  Mat3(const Mat3<U>& m3) noexcept
  : Mat3(m3.m[0],
         m3.m[1],
         m3.m[2],
         m3.m[3],
         m3.m[4],
         m3.m[5],
         m3.m[6],
         m3.m[7],
         m3.m[8])
  {
  }

  void
  m00(T val) noexcept
  {
    m[0] = val;
  }

  void
  m01(T val) noexcept
  {
    m[1] = val;
  }

  void
  m02(T val) noexcept
  {
    m[2] = val;
  }

  void
  m10(T val) noexcept
  {
    m[3] = val;
  }

  void
  m11(T val) noexcept
  {
    m[4] = val;
  }

  void
  m12(T val) noexcept
  {
    m[5] = val;
  }

  void
  m20(T val) noexcept
  {
    m[6] = val;
  }

  void
  m21(T val) noexcept
  {
    m[7] = val;
  }

  void
  m22(T val) noexcept
  {
    m[8] = val;
  }

  T
  m00() const noexcept
  {
    return m[0];
  }

  T
  m01() const noexcept
  {
    return m[1];
  }

  T
  m02() const noexcept
  {
    return m[2];
  }

  T
  m10() const noexcept
  {
    return m[3];
  }

  T
  m11() const noexcept
  {
    return m[4];
  }

  T
  m12() const noexcept
  {
    return m[5];
  }

  T
  m20() const noexcept
  {
    return m[6];
  }

  T
  m21() const noexcept
  {
    return m[7];
  }

  T
  m22() const noexcept
  {
    return m[8];
  }
};

} // namespace gm3d

#endif
