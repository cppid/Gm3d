#ifndef GM3D_RGBA_HPP
#define GM3D_RGBA_HPP

#include <cstdint>
#include <type_traits>

namespace gm3d {

template<typename>
class Rgba;

template<>
class Rgba<std::uint8_t> {
  std::uint8_t r_, g_, b_, a_;

public:
  Rgba() noexcept = default;

  explicit Rgba(std::uint8_t s) noexcept
  : Rgba{s, s, s, s}
  {
  }

  Rgba(std::uint8_t s, std::uint8_t a) noexcept
  : Rgba{s, s, s, a}
  {
  }

  Rgba(std::uint8_t r,
       std::uint8_t g,
       std::uint8_t b,
       std::uint8_t a = 0xFF) noexcept
  : r_{r}
  , g_{g}
  , b_{b}
  , a_{a}
  {
  }

  void
  r(std::uint8_t val) noexcept
  {
    r_ = val;
  }

  void
  g(std::uint8_t val) noexcept
  {
    g_ = val;
  }

  void
  b(std::uint8_t val) noexcept
  {
    b_ = val;
  }

  void
  a(std::uint8_t val) noexcept
  {
    a_ = val;
  }

  std::uint8_t
  r() const noexcept
  {
    return r_;
  }

  std::uint8_t
  g() const noexcept
  {
    return g_;
  }

  std::uint8_t
  b() const noexcept
  {
    return b_;
  }

  std::uint8_t
  a() const noexcept
  {
    return a_;
  }

  friend bool
  operator==(const Rgba& lhs, const Rgba& rhs) noexcept
  {
    return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() &&
           lhs.a() == rhs.a();
  }

  friend bool
  operator!=(const Rgba& lhs, const Rgba& rhs) noexcept
  {
    return !(lhs == rhs);
  }
};

} // namespace gm3d

#endif
