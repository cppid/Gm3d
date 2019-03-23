#ifndef CPPID_GM3D_DETAIL_BASIC_VECTOR_ND_HPP
#define CPPID_GM3D_DETAIL_BASIC_VECTOR_ND_HPP

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <numeric>
#include <type_traits>
#include <utility>

#include <boost/qvm/all.hpp>

#include "basic_point_vector.hpp"
#include "type_traits.hpp"

namespace cppid::gm3d::detail {

template<typename T, std::size_t N>
struct basic_vector_nd
: public basic_point_vector<basic_vector_nd<T, N>, T, N> {
  using typename basic_point_vector<basic_vector_nd<T, N>, T, N>::scalar_type;

  using basic_point_vector<basic_vector_nd<T, N>, T, N>::dimensions;

  basic_vector_nd() noexcept = default;

  explicit basic_vector_nd(scalar_type s) noexcept
  : basic_vector_nd{s, std::make_index_sequence<dimensions>()}
  {
  }

  template<std::size_t... Ns,
           typename = std::enable_if_t<(sizeof...(Ns) == dimensions)>>
  basic_vector_nd(scalar_type s, std::index_sequence<Ns...>) noexcept
  : basic_vector_nd{(static_cast<void>(Ns), s)...}
  {
  }

  template<
   typename... Us,
   typename = std::enable_if_t<((sizeof...(Us) == dimensions) && ... &&
                                std::is_convertible_v<Us, scalar_type>)>>
  basic_vector_nd(Us... args) noexcept
  : basic_point_vector<basic_vector_nd<T, N>, T, N>::basic_point_vector{args...}
  {
  }

  template<typename U,
           std::enable_if_t<
            detail::is_explicit_constructible_v<scalar_type, U>>* = nullptr>
  explicit basic_vector_nd(basic_vector_nd<U, dimensions> v) noexcept
  : basic_vector_nd{v, std::make_index_sequence<dimensions>()}
  {
  }

  template<typename U,
           std::size_t... Ns,
           std::enable_if_t<
            (sizeof...(Ns) == dimensions) &&
            detail::is_explicit_constructible_v<scalar_type, U>>* = nullptr>
  basic_vector_nd(basic_vector_nd<U, dimensions> v,
                  std::index_sequence<Ns...>) noexcept
  : basic_vector_nd{v.elems[Ns]...}
  {
  }

  template<typename U,
           std::enable_if_t<
            detail::is_implicit_constructible_v<scalar_type, U>>* = nullptr>
  basic_vector_nd(basic_vector_nd<U, dimensions> v) noexcept
  : basic_vector_nd{v, std::make_index_sequence<dimensions>()}
  {
  }

  template<typename U,
           std::size_t... Ns,
           std::enable_if_t<
            (sizeof...(Ns) == dimensions) &&
            detail::is_implicit_constructible_v<scalar_type, U>>* = nullptr>
  basic_vector_nd(basic_vector_nd<U, dimensions> v,
                  std::index_sequence<Ns...>) noexcept
  : basic_vector_nd{scalar_type(v.elems[Ns])...}
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_convertible_v<U, scalar_type>>>
  auto operator=(const basic_vector_nd<U, dimensions> rhs) noexcept
   -> basic_vector_nd&
  {
    op_assign(rhs.elems, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator+=(const basic_vector_nd& rhs) noexcept -> basic_vector_nd&
  {
    op_assign(rhs.elems, std::plus{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator+=(scalar_type rhs) noexcept -> basic_vector_nd&
  {
    op_assign(rhs, std::plus{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator-=(const basic_vector_nd& rhs) noexcept -> basic_vector_nd&
  {
    op_assign(rhs.elems, std::minus{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator-=(scalar_type rhs) noexcept -> basic_vector_nd&
  {
    op_assign(rhs, std::minus{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator*=(const basic_vector_nd& rhs) noexcept -> basic_vector_nd&
  {
    op_assign(
     rhs.elems, std::multiplies{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator*=(scalar_type rhs) noexcept -> basic_vector_nd&
  {
    op_assign(rhs, std::multiplies{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator/=(const basic_vector_nd& rhs) noexcept -> basic_vector_nd&
  {
    op_assign(
     rhs.elems, std::divides{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator/=(scalar_type rhs) noexcept -> basic_vector_nd&
  {
    op_assign(rhs, std::divides{}, std::make_index_sequence<dimensions>());
    return *this;
  }

  auto operator==(const basic_vector_nd& rhs) const noexcept -> bool
  {
    return is_equal(rhs.elems, std::make_index_sequence<dimensions>());
  }

  auto operator!=(const basic_vector_nd& rhs) const noexcept -> bool
  {
    return !((*this) == rhs);
  }

  auto dot(const basic_vector_nd& other) const noexcept -> scalar_type
  {
    return dot(other, std::make_index_sequence<dimensions>());
  }

  auto magnitude() const noexcept -> scalar_type
  {
    return std::sqrt(dot(*this));
  }

  auto magnitude_squared() const noexcept -> scalar_type
  {
    return dot(*this);
  }

  auto to_unit() const noexcept -> basic_vector_nd
  {
    return *this / magnitude();
  }

  auto reflect(const basic_vector_nd& n) const noexcept -> basic_vector_nd
  {
    return *this - 2 * dot(n) * n;
  }

  template<typename V = void, std::enable_if_t<dimensions == 3, V>* = nullptr>
  auto cross(const basic_vector_nd& other) const noexcept -> basic_vector_nd
  {
    return boost::qvm::cross(*this, other);
  }

  friend auto operator+(const basic_vector_nd& val) noexcept -> basic_vector_nd
  {
    return val;
  }

  template<typename U,
           typename =
            std::enable_if_t<std::is_invocable_v<std::plus<>, scalar_type, U>>>
  friend auto operator+(const basic_vector_nd& lhs,
                        const basic_vector_nd<U, dimensions>& rhs) noexcept
   -> basic_vector_nd<std::invoke_result_t<std::plus<>, scalar_type, U>,
                      dimensions>
  {
    return invoke_op{}(
     std::plus{}, lhs, rhs, std::make_index_sequence<dimensions>());
  }

  friend auto operator+(const basic_vector_nd& lhs, scalar_type rhs) noexcept
   -> basic_vector_nd
  {
    return lhs + basic_vector_nd{rhs};
  }

  friend auto operator+(scalar_type lhs, const basic_vector_nd& rhs) noexcept
   -> basic_vector_nd
  {
    return basic_vector_nd{lhs} + rhs;
  }

  friend auto operator-(const basic_vector_nd& lhs) noexcept -> basic_vector_nd
  {
    return invoke_op{}(
     std::negate{}, lhs, std::make_index_sequence<dimensions>());
  }

  template<typename U,
           typename =
            std::enable_if_t<std::is_invocable_v<std::minus<>, scalar_type, U>>>
  friend auto operator-(const basic_vector_nd& lhs,
                        const basic_vector_nd<U, dimensions>& rhs) noexcept
   -> basic_vector_nd<std::invoke_result_t<std::minus<>, scalar_type, U>,
                      dimensions>
  {
    return invoke_op{}(
     std::minus{}, lhs, rhs, std::make_index_sequence<dimensions>());
  }

  friend auto operator-(const basic_vector_nd& lhs, scalar_type rhs) noexcept
   -> basic_vector_nd
  {
    return lhs - basic_vector_nd{rhs};
  }

  friend auto operator-(scalar_type lhs, const basic_vector_nd& rhs) noexcept
   -> basic_vector_nd
  {
    return basic_vector_nd{lhs} - rhs;
  }

  template<typename U,
           typename = std::enable_if_t<
            std::is_invocable_v<std::multiplies<>, scalar_type, U>>>
  friend auto operator*(const basic_vector_nd& lhs,
                        const basic_vector_nd<U, dimensions>& rhs) noexcept
   -> basic_vector_nd<std::invoke_result_t<std::multiplies<>, scalar_type, U>,
                      dimensions>
  {
    return invoke_op{}(
     std::multiplies{}, lhs, rhs, std::make_index_sequence<dimensions>());
  }

  friend auto operator*(const basic_vector_nd& lhs, scalar_type rhs) noexcept
   -> basic_vector_nd
  {
    return lhs * basic_vector_nd{rhs};
  }

  friend auto operator*(scalar_type lhs, const basic_vector_nd& rhs) noexcept
   -> basic_vector_nd
  {
    return basic_vector_nd{lhs} * rhs;
  }

  template<typename U,
           typename = std::enable_if_t<
            std::is_invocable_v<std::divides<>, scalar_type, U>>>
  friend auto operator/(const basic_vector_nd& lhs,
                        const basic_vector_nd<U, dimensions>& rhs) noexcept
   -> basic_vector_nd<std::invoke_result_t<std::divides<>, scalar_type, U>,
                      dimensions>
  {
    return invoke_op{}(
     std::divides{}, lhs, rhs, std::make_index_sequence<dimensions>());
  }

  friend auto operator/(const basic_vector_nd& lhs, scalar_type rhs) noexcept
   -> basic_vector_nd
  {
    return lhs / basic_vector_nd{rhs};
  }

  friend auto operator/(scalar_type lhs, const basic_vector_nd& rhs) noexcept
   -> basic_vector_nd
  {
    return basic_vector_nd{lhs} / rhs;
  }

private:
  struct invoke_op {
    template<typename P, typename U, std::size_t... Ns>
    auto operator()(const P op,
                    const basic_vector_nd<U, dimensions>& lhs,
                    std::index_sequence<Ns...>) const noexcept
     -> basic_vector_nd<std::invoke_result_t<P, U>, dimensions>
    {
      static_assert(sizeof...(Ns) == dimensions);
      return {op(lhs.elems[Ns])...};
    }

    template<typename P, typename U, typename V, std::size_t... Ns>
    auto operator()(const P op,
                    const basic_vector_nd<U, dimensions>& lhs,
                    const basic_vector_nd<V, dimensions>& rhs,
                    std::index_sequence<Ns...>) const noexcept
     -> basic_vector_nd<std::invoke_result_t<P, U, V>, dimensions>
    {
      static_assert(sizeof...(Ns) == dimensions);
      return {op(lhs.elems[Ns], rhs.elems[Ns])...};
    }
  };

  template<typename U, typename P, std::size_t... Ns>
  inline void op_assign(const U (&rhs)[dimensions],
                        P op,
                        std::index_sequence<Ns...>) noexcept
  {
    ((this->elems[Ns] = op(this->elems[Ns], rhs[Ns])), ...);
  }

  template<typename U, typename P, std::size_t... Ns>
  inline void op_assign(U rhs, P op, std::index_sequence<Ns...>) noexcept
  {
    ((this->elems[Ns] = op(this->elems[Ns], rhs)), ...);
  }

  template<typename U, std::size_t... Ns>
  inline void op_assign(const U (&rhs)[dimensions],
                        std::index_sequence<Ns...>) noexcept
  {
    ((this->elems[Ns] = rhs[Ns]), ...);
  }

  template<typename U, std::size_t... Ns>
  auto is_equal(const U (&rhs)[dimensions], std::index_sequence<Ns...>) const
   noexcept -> bool
  {
    return ((this->elems[Ns] == rhs[Ns]) && ... && true);
  }

  template<std::size_t... Ns>
  auto negate(std::index_sequence<Ns...>) const noexcept -> basic_vector_nd
  {
    return basic_vector_nd{(-this->elems[Ns])...};
  }

  template<std::size_t... Ns>
  auto dot(const basic_vector_nd& other, std::index_sequence<Ns...>) const
   noexcept -> scalar_type
  {
    return ((this->elems[Ns] * other.elems[Ns]) + ... + 0);
  }
};

} // namespace cppid::gm3d::detail

namespace boost::qvm {

template<typename T, std::size_t N>
struct vec_traits<cppid::gm3d::detail::basic_vector_nd<T, N>>
: public vec_traits<
   cppid::gm3d::detail::
    basic_point_vector<cppid::gm3d::detail::basic_vector_nd<T, N>, T, N>> {
};

} // namespace boost::qvm

#endif
