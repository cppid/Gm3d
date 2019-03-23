#ifndef CPPID_GM3D_VECTOR_3D_HPP
#define CPPID_GM3D_VECTOR_3D_HPP

#include "detail/basic_vector_nd.hpp"

namespace cppid::gm3d {

template<typename T>
using vector_3d = detail::basic_vector_nd<T, 3>;

} // namespace cppid::gm3d

#endif
