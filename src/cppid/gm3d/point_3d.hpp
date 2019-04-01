#ifndef CPPID_GM3D_POINT_3D_HPP
#define CPPID_GM3D_POINT_3D_HPP

#include "detail/basic_point_nd.hpp"

namespace cppid::gm3d {

template<typename T>
using point_3d = detail::basic_point_nd<T, 3>;

} // namespace cppid::gm3d

#endif
