#ifndef CPPID_GM3D_DETAIL_BASIC_RGBA_HPP
#define CPPID_GM3D_DETAIL_BASIC_RGBA_HPP

namespace cppid::gm3d::detail {

template<typename TRgba, typename T>
class basic_rgba {
public:
  using scalar_type = T;

  constexpr basic_rgba() noexcept = default;

  explicit constexpr basic_rgba(scalar_type s) noexcept
  : basic_rgba{s, s, s, s}
  {
  }

  constexpr basic_rgba(scalar_type s, scalar_type a) noexcept
  : basic_rgba{s, s, s, a}
  {
  }

  constexpr basic_rgba(scalar_type r,
                       scalar_type g,
                       scalar_type b,
                       scalar_type a) noexcept
  : r_{r}
  , g_{g}
  , b_{b}
  , a_{a}
  {
  }

  constexpr void r(scalar_type val) noexcept
  {
    r_ = val;
  }

  constexpr void g(scalar_type val) noexcept
  {
    g_ = val;
  }

  constexpr void b(scalar_type val) noexcept
  {
    b_ = val;
  }

  constexpr void a(scalar_type val) noexcept
  {
    a_ = val;
  }

  constexpr auto r() const noexcept -> scalar_type
  {
    return r_;
  }

  constexpr auto g() const noexcept -> scalar_type
  {
    return g_;
  }

  constexpr auto b() const noexcept -> scalar_type
  {
    return b_;
  }

  constexpr auto a() const noexcept -> scalar_type
  {
    return a_;
  }

  friend constexpr auto operator==(const basic_rgba& lhs,
                                   const basic_rgba& rhs) noexcept -> bool
  {
    return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() &&
           lhs.a() == rhs.a();
  }

  friend constexpr auto operator!=(const basic_rgba& lhs,
                                   const basic_rgba& rhs) noexcept -> bool
  {
    return !(lhs == rhs);
  }

private:
  scalar_type r_, g_, b_, a_;
};

} // namespace cppid::gm3d::detail

#endif
