#ifndef GM3D_VEC_HPP
#define GM3D_VEC_HPP

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

#include "detail/type_traits.hpp"

namespace gm3d {

template<typename T, std::size_t N>
struct Vec {
  T elems[N];

  Vec() noexcept = default;

  explicit Vec(T s) noexcept
  : Vec{s, std::make_index_sequence<N>()}
  {
  }

  template<std::size_t... Ns, typename = std::enable_if_t<(sizeof...(Ns) == N)>>
  Vec(T s, std::index_sequence<Ns...>) noexcept
  : elems{(static_cast<void>(Ns), s)...}
  {
  }

  template<typename... Us,
           typename = std::enable_if_t<((sizeof...(Us) == N) && ... &&
                                        std::is_convertible_v<Us, T>)>>
  Vec(Us... args) noexcept
  : elems{T(args)...}
  {
  }

  template<
   typename U,
   std::enable_if_t<detail::is_explicit_constructible_v<T, U>>* = nullptr>
  explicit Vec(Vec<U, N> v) noexcept
  : Vec{v, std::make_index_sequence<N>()}
  {
  }

  template<
   typename U,
   std::size_t... Ns,
   std::enable_if_t<(sizeof...(Ns) == N) &&
                    detail::is_explicit_constructible_v<T, U>>* = nullptr>
  Vec(Vec<U, N> v, std::index_sequence<Ns...>) noexcept
  : elems{v.elems[Ns]...}
  {
  }

  template<
   typename U,
   std::enable_if_t<detail::is_implicit_constructible_v<T, U>>* = nullptr>
  Vec(Vec<U, N> v) noexcept
  : Vec{v, std::make_index_sequence<N>()}
  {
  }

  template<
   typename U,
   std::size_t... Ns,
   std::enable_if_t<(sizeof...(Ns) == N) &&
                    detail::is_implicit_constructible_v<T, U>>* = nullptr>
  Vec(Vec<U, N> v, std::index_sequence<Ns...>) noexcept
  : elems{T(v.elems[Ns])...}
  {
  }

  template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
  Vec&
  operator=(const Vec<U, N> rhs) noexcept
  {
    op_assign(rhs.elems, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator+=(const Vec& rhs) noexcept
  {
    op_assign(rhs.elems, std::plus{}, std::make_index_sequence<N>());
    return *this;
  }

  template<typename U, typename P, std::size_t... Ns>
  inline void
  op_assign(const U (&rhs)[N], P op, std::index_sequence<Ns...>) noexcept
  {
    ((elems[Ns] = op(elems[Ns], rhs[Ns])), ...);
  }

  template<typename U, typename P, std::size_t... Ns>
  inline void
  op_assign(U rhs, P op, std::index_sequence<Ns...>) noexcept
  {
    ((elems[Ns] = op(elems[Ns], rhs)), ...);
  }

  Vec&
  operator+=(T rhs) noexcept
  {
    op_assign(rhs, std::plus{}, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator-=(const Vec& rhs) noexcept
  {
    op_assign(rhs.elems, std::minus{}, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator-=(T rhs) noexcept
  {
    op_assign(rhs, std::minus{}, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator*=(const Vec& rhs) noexcept
  {
    op_assign(rhs.elems, std::multiplies{}, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator*=(T rhs) noexcept
  {
    op_assign(rhs, std::multiplies{}, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator/=(const Vec& rhs) noexcept
  {
    op_assign(rhs.elems, std::divides{}, std::make_index_sequence<N>());
    return *this;
  }

  Vec&
  operator/=(T rhs) noexcept
  {
    op_assign(rhs, std::divides{}, std::make_index_sequence<N>());
    return *this;
  }

  bool
  operator==(const Vec& rhs) const noexcept
  {
    return is_equal(rhs.elems, std::make_index_sequence<N>());
  }

  bool
  operator!=(const Vec& rhs) const noexcept
  {
    return !((*this) == rhs);
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

  template<typename V = void, std::enable_if_t<N >= 3, V>* = nullptr>
  void
  z(T val) noexcept
  {
    elems[2] = val;
  }

  template<typename V = void, std::enable_if_t<N >= 4, V>* = nullptr>
  void
  w(T val) noexcept
  {
    elems[3] = val;
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

  template<typename V = void, std::enable_if_t<N >= 3, V>* = nullptr>
  T
  z() const noexcept
  {
    return elems[2];
  }

  template<typename V = void, std::enable_if_t<N >= 4, V>* = nullptr>
  T
  w() const noexcept
  {
    return elems[3];
  }

  T
  dot(const Vec& other) const noexcept
  {
    return std::inner_product(elems, elems + N, other.elems, 0);
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

  Vec
  to_unit() const noexcept
  {
    return *this / magnitude();
  }

  Vec
  reflect(const Vec& n) const noexcept
  {
    return *this - 2 * dot(n) * n;
  }

  template<typename V = void, std::enable_if_t<N == 3, V>* = nullptr>
  Vec
  cross(const Vec& other) const noexcept
  {
    return {elems[1] * other.elems[2] - elems[2] * other.elems[1],
            elems[2] * other.elems[0] - elems[0] * other.elems[2],
            elems[0] * other.elems[1] - elems[1] * other.elems[0]};
  }

  friend Vec
  operator+(const Vec& val) noexcept
  {
    return val;
  }

  friend Vec
  operator+(const Vec& lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} += rhs;
  }

  friend Vec
  operator+(const Vec& lhs, T rhs) noexcept
  {
    return lhs + Vec{rhs};
  }

  friend Vec
  operator+(T lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} + rhs;
  }

  friend Vec
  operator-(const Vec& lhs) noexcept
  {
    return {-lhs.elems[0], -lhs.elems[1]};
  }

  friend Vec
  operator-(const Vec& lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} -= rhs;
  }

  friend Vec
  operator-(const Vec& lhs, T rhs) noexcept
  {
    return lhs - Vec{rhs};
  }

  friend Vec
  operator-(T lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} - rhs;
  }

  friend Vec operator*(const Vec& lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} *= rhs;
  }

  friend Vec operator*(const Vec& lhs, T rhs) noexcept
  {
    return lhs * Vec{rhs};
  }

  friend Vec operator*(T lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} * rhs;
  }

  friend Vec
  operator/(const Vec& lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} /= rhs;
  }

  friend Vec
  operator/(const Vec& lhs, T rhs) noexcept
  {
    return lhs / Vec{rhs};
  }

  friend Vec
  operator/(T lhs, const Vec& rhs) noexcept
  {
    return Vec{lhs} / rhs;
  }

private:
  template<typename U, std::size_t... Ns>
  inline void
  op_assign(const U (&rhs)[N], std::index_sequence<Ns...>) noexcept
  {
    ((elems[Ns] = rhs[Ns]), ...);
  }

  template<typename U, std::size_t... Ns>
  bool
  is_equal(const U (&rhs)[N], std::index_sequence<Ns...>) const noexcept
  {
    return ((elems[Ns] == rhs[Ns]) && ... && true);
  }
};

} // namespace gm3d

#endif
