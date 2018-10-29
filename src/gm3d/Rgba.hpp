#ifndef GM3D_RGBA_HPP
#define GM3D_RGBA_HPP

#include <cstdint>

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

} // namespace gm3d

#endif
