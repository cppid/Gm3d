#ifndef GM3D_RGBA_HPP
#define GM3D_RGBA_HPP

#include <cstdint>
#include <type_traits>

#include "detail/BasicRgba.hpp"

namespace gm3d {

template<typename>
class Rgba;

template<>
class Rgba<std::uint8_t>
: public detail::BasicRgba<Rgba<std::uint8_t>, std::uint8_t> {
public:
  using Scalar = detail::BasicRgba<Rgba<std::uint8_t>, std::uint8_t>::Scalar;

  using detail::BasicRgba<Rgba<std::uint8_t>, std::uint8_t>::BasicRgba;

  Rgba() noexcept = default;

  Rgba(Scalar r, Scalar g, Scalar b) noexcept
  : Rgba{r, g, b, 0xFF}
  {
  }
};

template<>
class Rgba<float> : public detail::BasicRgba<Rgba<float>, float> {
public:
  using Scalar = detail::BasicRgba<Rgba<float>, float>::Scalar;

  using detail::BasicRgba<Rgba<float>, float>::BasicRgba;

  Rgba() noexcept = default;

  template<typename T,
           typename = std::enable_if_t<std::is_same_v<T, std::uint8_t>>>
  explicit Rgba(Rgba<T>&& col)
  : Rgba{col.r(), col.g(), col.b(), col.a()}
  {
  }

  template<typename T,
           typename = std::enable_if_t<std::is_same_v<T, std::uint8_t>>>
  Rgba(T r, T g, T b, T a) noexcept
  : Rgba{r / Scalar{255} * a / Scalar{255},
         g / Scalar{255} * a / Scalar{255},
         b / Scalar{255} * a / Scalar{255},
         a / Scalar{255}}
  {
  }

  Rgba(Scalar r, Scalar g, Scalar b) noexcept
  : Rgba{r, g, b, 1}
  {
  }
};

} // namespace gm3d

#endif
