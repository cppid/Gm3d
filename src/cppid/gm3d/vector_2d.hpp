#ifndef CPPID_GM3D_VECTOR_2D_HPP
#define CPPID_GM3D_VECTOR_2D_HPP

#include "detail/basic_vector_nd.hpp"

namespace cppid::gm3d {

template<typename T>
using vector_2d = detail::basic_vector_nd<T, 2>;

} // namespace cppid::gm3d

#endif
