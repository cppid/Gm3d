#ifndef CPPID_GM3D_DETAIL_BASIC_POINT_ND_HPP
#define CPPID_GM3D_DETAIL_BASIC_POINT_ND_HPP

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
struct basic_point_nd : public basic_point_vector<basic_point_nd<T, N>, T, N> {
  using typename basic_point_vector<basic_point_nd<T, N>, T, N>::scalar_type;

  using basic_point_vector<basic_point_nd<T, N>, T, N>::dimensions;

  using basic_point_vector<basic_point_nd<T, N>, T, N>::basic_point_vector;

  constexpr basic_point_nd() noexcept = default;

  template<typename U,
           std::enable_if_t<
            detail::is_explicit_constructible_v<scalar_type, U>>* = nullptr>
  explicit constexpr basic_point_nd(basic_point_nd<U, dimensions> v) noexcept
  : basic_point_nd{v, std::make_index_sequence<dimensions>()}
  {
  }

  template<typename U,
           std::size_t... Ns,
           std::enable_if_t<
            (sizeof...(Ns) == dimensions) &&
            detail::is_explicit_constructible_v<scalar_type, U>>* = nullptr>
  constexpr basic_point_nd(basic_point_nd<U, dimensions> v,
                           std::index_sequence<Ns...>) noexcept
  : basic_point_nd{v.elems[Ns]...}
  {
  }

  template<typename U,
           std::enable_if_t<
            detail::is_implicit_constructible_v<scalar_type, U>>* = nullptr>
  constexpr basic_point_nd(basic_point_nd<U, dimensions> v) noexcept
  : basic_point_nd{v, std::make_index_sequence<dimensions>()}
  {
  }

  template<typename U,
           std::size_t... Ns,
           std::enable_if_t<
            (sizeof...(Ns) == dimensions) &&
            detail::is_implicit_constructible_v<scalar_type, U>>* = nullptr>
  constexpr basic_point_nd(basic_point_nd<U, dimensions> v,
                           std::index_sequence<Ns...>) noexcept
  : basic_point_nd{scalar_type(v.elems[Ns])...}
  {
  }

  template<typename U,
           typename = std::enable_if_t<std::is_convertible_v<U, scalar_type>>>
  constexpr auto operator=(const basic_point_nd<U, dimensions> rhs) noexcept
   -> basic_point_nd&
  {
    op_assign(rhs.elems, std::make_index_sequence<dimensions>());
    return *this;
  }

  constexpr auto operator==(const basic_point_nd& rhs) const noexcept -> bool
  {
    return is_equal(rhs.elems, std::make_index_sequence<dimensions>());
  }

  constexpr auto operator!=(const basic_point_nd& rhs) const noexcept -> bool
  {
    return !(*this == rhs);
  }

  friend constexpr auto operator+(const basic_point_nd& val) noexcept
   -> basic_point_nd
  {
    return val;
  }

  friend constexpr auto operator-(const basic_point_nd& lhs) noexcept
   -> basic_point_nd
  {
    return invoke_op{}(
     std::negate{}, lhs, std::make_index_sequence<dimensions>());
  }

private:
  struct invoke_op {
    template<typename P, typename U, std::size_t... Ns>
    constexpr auto operator()(const P op,
                              const basic_point_nd<U, dimensions>& lhs,
                              std::index_sequence<Ns...>) const noexcept
     -> basic_point_nd<std::invoke_result_t<P, U>, dimensions>
    {
      static_assert(sizeof...(Ns) == dimensions);
      return {op(lhs.elems[Ns])...};
    }

    template<typename P, typename U, typename V, std::size_t... Ns>
    constexpr auto operator()(const P op,
                              const basic_point_nd<U, dimensions>& lhs,
                              const basic_point_nd<V, dimensions>& rhs,
                              std::index_sequence<Ns...>) const noexcept
     -> basic_point_nd<std::invoke_result_t<P, U, V>, dimensions>
    {
      static_assert(sizeof...(Ns) == dimensions);
      return {op(lhs.elems[Ns], rhs.elems[Ns])...};
    }
  };

  template<typename U, typename P, std::size_t... Ns>
  inline constexpr void op_assign(const U (&rhs)[dimensions],
                                  P op,
                                  std::index_sequence<Ns...>) noexcept
  {
    ((this->elems[Ns] = op(this->elems[Ns], rhs[Ns])), ...);
  }

  template<typename U, typename P, std::size_t... Ns>
  inline constexpr void
  op_assign(U rhs, P op, std::index_sequence<Ns...>) noexcept
  {
    ((this->elems[Ns] = op(this->elems[Ns], rhs)), ...);
  }

  template<typename U, std::size_t... Ns>
  inline constexpr void op_assign(const U (&rhs)[dimensions],
                                  std::index_sequence<Ns...>) noexcept
  {
    ((this->elems[Ns] = rhs[Ns]), ...);
  }

  template<typename U, std::size_t... Ns>
  constexpr auto is_equal(const U (&rhs)[dimensions],
                          std::index_sequence<Ns...>) const noexcept -> bool
  {
    return ((this->elems[Ns] == rhs[Ns]) && ... && true);
  }

  template<std::size_t... Ns>
  constexpr auto negate(std::index_sequence<Ns...>) const noexcept
   -> basic_point_nd
  {
    return basic_point_nd{(-this->elems[Ns])...};
  }
};

} // namespace cppid::gm3d::detail

namespace boost::qvm {

template<typename T, std::size_t N>
struct vec_traits<cppid::gm3d::detail::basic_point_nd<T, N>>
: public vec_traits<
   cppid::gm3d::detail::
    basic_point_vector<cppid::gm3d::detail::basic_point_nd<T, N>, T, N>> {
};

} // namespace boost::qvm

#endif
