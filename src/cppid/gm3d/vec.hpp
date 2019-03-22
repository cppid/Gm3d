#ifndef CPPID_GM3D_VEC_HPP
#define CPPID_GM3D_VEC_HPP

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <numeric>
#include <type_traits>
#include <utility>

#include "detail/type_traits.hpp"

namespace cppid::gm3d {

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
  auto
  operator=(const Vec<U, N> rhs) noexcept -> Vec&
  {
    op_assign(rhs.elems, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator+=(const Vec& rhs) noexcept -> Vec&
  {
    op_assign(rhs.elems, std::plus{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator+=(T rhs) noexcept -> Vec&
  {
    op_assign(rhs, std::plus{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator-=(const Vec& rhs) noexcept -> Vec&
  {
    op_assign(rhs.elems, std::minus{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator-=(T rhs) noexcept -> Vec&
  {
    op_assign(rhs, std::minus{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator*=(const Vec& rhs) noexcept -> Vec&
  {
    op_assign(rhs.elems, std::multiplies{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator*=(T rhs) noexcept -> Vec&
  {
    op_assign(rhs, std::multiplies{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator/=(const Vec& rhs) noexcept -> Vec&
  {
    op_assign(rhs.elems, std::divides{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator/=(T rhs) noexcept -> Vec&
  {
    op_assign(rhs, std::divides{}, std::make_index_sequence<N>());
    return *this;
  }

  auto
  operator==(const Vec& rhs) const noexcept -> bool
  {
    return is_equal(rhs.elems, std::make_index_sequence<N>());
  }

  auto
  operator!=(const Vec& rhs) const noexcept -> bool
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

  auto
  x() const noexcept -> T
  {
    return elems[0];
  }

  auto
  y() const noexcept -> T
  {
    return elems[1];
  }

  template<typename V = void, std::enable_if_t<N >= 3, V>* = nullptr>
  auto
  z() const noexcept -> T
  {
    return elems[2];
  }

  template<typename V = void, std::enable_if_t<N >= 4, V>* = nullptr>
  auto
  w() const noexcept -> T
  {
    return elems[3];
  }

  auto
  dot(const Vec& other) const noexcept -> T
  {
    return dot(other, std::make_index_sequence<N>());
  }

  auto
  magnitude() const noexcept -> T
  {
    return std::sqrt(dot(*this));
  }

  auto
  magnitude_squared() const noexcept -> T
  {
    return dot(*this);
  }

  auto
  to_unit() const noexcept -> Vec
  {
    return *this / magnitude();
  }

  auto
  reflect(const Vec& n) const noexcept -> Vec
  {
    return *this - 2 * dot(n) * n;
  }

  template<typename V = void, std::enable_if_t<N == 3, V>* = nullptr>
  auto
  cross(const Vec& other) const noexcept -> Vec
  {
    return {elems[1] * other.elems[2] - elems[2] * other.elems[1],
            elems[2] * other.elems[0] - elems[0] * other.elems[2],
            elems[0] * other.elems[1] - elems[1] * other.elems[0]};
  }

  friend auto
  operator+(const Vec& val) noexcept -> Vec
  {
    return val;
  }

  template<typename U,
           typename = std::enable_if_t<std::is_invocable_v<std::plus<>, T, U>>>
  friend auto
  operator+(const Vec& lhs, const Vec<U, N>& rhs) noexcept
   -> Vec<std::invoke_result_t<std::plus<>, T, U>, N>
  {
    return invoke_op{}(std::plus{}, lhs, rhs, std::make_index_sequence<N>());
  }

  friend auto
  operator+(const Vec& lhs, T rhs) noexcept -> Vec
  {
    return lhs + Vec{rhs};
  }

  friend auto
  operator+(T lhs, const Vec& rhs) noexcept -> Vec
  {
    return Vec{lhs} + rhs;
  }

  friend auto
  operator-(const Vec& lhs) noexcept -> Vec
  {
    return invoke_op{}(std::negate{}, lhs, std::make_index_sequence<N>());
  }

  template<typename U,
           typename = std::enable_if_t<std::is_invocable_v<std::minus<>, T, U>>>
  friend auto
  operator-(const Vec& lhs, const Vec<U, N>& rhs) noexcept
   -> Vec<std::invoke_result_t<std::minus<>, T, U>, N>
  {
    return invoke_op{}(std::minus{}, lhs, rhs, std::make_index_sequence<N>());
  }

  friend auto
  operator-(const Vec& lhs, T rhs) noexcept -> Vec
  {
    return lhs - Vec{rhs};
  }

  friend auto
  operator-(T lhs, const Vec& rhs) noexcept -> Vec
  {
    return Vec{lhs} - rhs;
  }

  template<
   typename U,
   typename = std::enable_if_t<std::is_invocable_v<std::multiplies<>, T, U>>>
  friend auto operator*(const Vec& lhs, const Vec<U, N>& rhs) noexcept
   -> Vec<std::invoke_result_t<std::multiplies<>, T, U>, N>
  {
    return invoke_op{}(
     std::multiplies{}, lhs, rhs, std::make_index_sequence<N>());
  }

  friend auto operator*(const Vec& lhs, T rhs) noexcept -> Vec
  {
    return lhs * Vec{rhs};
  }

  friend auto operator*(T lhs, const Vec& rhs) noexcept -> Vec
  {
    return Vec{lhs} * rhs;
  }

  template<
   typename U,
   typename = std::enable_if_t<std::is_invocable_v<std::divides<>, T, U>>>
  friend auto
  operator/(const Vec& lhs, const Vec<U, N>& rhs) noexcept
   -> Vec<std::invoke_result_t<std::divides<>, T, U>, N>
  {
    return invoke_op{}(std::divides{}, lhs, rhs, std::make_index_sequence<N>());
  }

  friend auto
  operator/(const Vec& lhs, T rhs) noexcept -> Vec
  {
    return lhs / Vec{rhs};
  }

  friend auto
  operator/(T lhs, const Vec& rhs) noexcept -> Vec
  {
    return Vec{lhs} / rhs;
  }

private:
  struct invoke_op {
    template<typename P, typename U, std::size_t... Ns>
    auto
    operator()(const P op,
               const Vec<U, N>& lhs,
               std::index_sequence<Ns...>) const noexcept
     -> Vec<std::invoke_result_t<P, U>, N>
    {
      static_assert(sizeof...(Ns) == N);
      return {op(lhs.elems[Ns])...};
    }

    template<typename P, typename U, typename V, std::size_t... Ns>
    auto
    operator()(const P op,
               const Vec<U, N>& lhs,
               const Vec<V, N>& rhs,
               std::index_sequence<Ns...>) const noexcept
     -> Vec<std::invoke_result_t<P, U, V>, N>
    {
      static_assert(sizeof...(Ns) == N);
      return {op(lhs.elems[Ns], rhs.elems[Ns])...};
    }
  };

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

  template<typename U, std::size_t... Ns>
  inline void
  op_assign(const U (&rhs)[N], std::index_sequence<Ns...>) noexcept
  {
    ((elems[Ns] = rhs[Ns]), ...);
  }

  template<typename U, std::size_t... Ns>
  auto
  is_equal(const U (&rhs)[N], std::index_sequence<Ns...>) const noexcept -> bool
  {
    return ((elems[Ns] == rhs[Ns]) && ... && true);
  }

  template<std::size_t... Ns>
  auto
  negate(std::index_sequence<Ns...>) const noexcept -> Vec
  {
    return Vec{(-elems[Ns])...};
  }

  template<std::size_t... Ns>
  auto
  dot(const Vec& other, std::index_sequence<Ns...>) const noexcept -> T
  {
    return ((elems[Ns] * other.elems[Ns]) + ... + 0);
  }
};

} // namespace cppid::gm3d

#endif
