#ifndef GM3D_DETAIL_BASIC_RGBA_HPP
#define GM3D_DETAIL_BASIC_RGBA_HPP

namespace gm3d::detail {

template<typename TRgba, typename T>
class BasicRgba {
public:
  using Scalar = T;

  BasicRgba() noexcept = default;

  explicit BasicRgba(Scalar s) noexcept
  : BasicRgba{s, s, s, s}
  {
  }

  BasicRgba(Scalar s, Scalar a) noexcept
  : BasicRgba{s, s, s, a}
  {
  }

  BasicRgba(Scalar r, Scalar g, Scalar b, Scalar a) noexcept
  : r_{r}
  , g_{g}
  , b_{b}
  , a_{a}
  {
  }

  void
  r(Scalar val) noexcept
  {
    r_ = val;
  }

  void
  g(Scalar val) noexcept
  {
    g_ = val;
  }

  void
  b(Scalar val) noexcept
  {
    b_ = val;
  }

  void
  a(Scalar val) noexcept
  {
    a_ = val;
  }

  Scalar
  r() const noexcept
  {
    return r_;
  }

  Scalar
  g() const noexcept
  {
    return g_;
  }

  Scalar
  b() const noexcept
  {
    return b_;
  }

  Scalar
  a() const noexcept
  {
    return a_;
  }

  friend bool
  operator==(const BasicRgba& lhs, const BasicRgba& rhs) noexcept
  {
    return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() &&
           lhs.a() == rhs.a();
  }

  friend bool
  operator!=(const BasicRgba& lhs, const BasicRgba& rhs) noexcept
  {
    return !(lhs == rhs);
  }

private:
  Scalar r_, g_, b_, a_;
};

} // namespace gm3d::detail

#endif
