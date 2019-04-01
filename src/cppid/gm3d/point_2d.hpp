#ifndef CPPID_GM3D_POINT_2D_HPP
#define CPPID_GM3D_POINT_2D_HPP

#include "detail/basic_point_nd.hpp"

namespace cppid::gm3d {

template<typename T>
using point_2d = detail::basic_point_nd<T, 2>;

} // namespace cppid::gm3d

#endif
