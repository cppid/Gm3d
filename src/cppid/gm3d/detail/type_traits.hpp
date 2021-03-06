#ifndef CPPID_GM3D_DETAIL_TYPE_TRAITS_HPP
#define CPPID_GM3D_DETAIL_TYPE_TRAITS_HPP

#include <cstddef>
#include <type_traits>

namespace cppid::gm3d::detail {

template<typename T, typename U>
struct is_explicit_constructible
: std::bool_constant<std::is_constructible_v<T, U> &&
                     !std::is_convertible_v<U, T>> {
};

template<typename T, typename U>
inline constexpr bool is_explicit_constructible_v =
 is_explicit_constructible<T, U>::value;

template<typename T, typename U>
struct is_implicit_constructible
: std::bool_constant<std::is_constructible_v<T, U> &&
                     std::is_convertible_v<U, T>> {
};

template<typename T, typename U>
inline constexpr bool is_implicit_constructible_v =
 is_implicit_constructible<T, U>::value;

} // namespace cppid::gm3d::detail

#endif
