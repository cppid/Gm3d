#ifndef CPPID_GM3D_RGBA_HPP
#define CPPID_GM3D_RGBA_HPP

#include <cstdint>
#include <type_traits>

#include "detail/basic_rgba.hpp"

namespace cppid::gm3d {

template<typename>
class rgba;

template<>
class rgba<std::uint8_t>
: public detail::basic_rgba<rgba<std::uint8_t>, std::uint8_t> {
public:
  using scalar_type =
   detail::basic_rgba<rgba<std::uint8_t>, std::uint8_t>::scalar_type;

  using detail::basic_rgba<rgba<std::uint8_t>, std::uint8_t>::basic_rgba;

  constexpr rgba(scalar_type r, scalar_type g, scalar_type b) noexcept
  : rgba{r, g, b, 0xFF}
  {
  }
};

template<>
class rgba<float> : public detail::basic_rgba<rgba<float>, float> {
public:
  using scalar_type = detail::basic_rgba<rgba<float>, float>::scalar_type;

  using detail::basic_rgba<rgba<float>, float>::basic_rgba;

  template<typename T,
           typename = std::enable_if_t<std::is_same_v<T, std::uint8_t>>>
  explicit constexpr rgba(const rgba<T>& col)
  : rgba{col.r(), col.g(), col.b(), col.a()}
  {
  }

  template<typename T,
           typename = std::enable_if_t<std::is_same_v<T, std::uint8_t>>>
  constexpr rgba(T r, T g, T b, T a) noexcept
  : rgba{r / scalar_type{255} * a / scalar_type{255},
         g / scalar_type{255} * a / scalar_type{255},
         b / scalar_type{255} * a / scalar_type{255},
         a / scalar_type{255}}
  {
  }

  constexpr rgba(scalar_type r, scalar_type g, scalar_type b) noexcept
  : rgba{r, g, b, 1}
  {
  }
};

} // namespace cppid::gm3d

#endif
