#include <cfloat>
#include <type_traits>

#include <boost/qvm/all.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cppid/gm3d/point_3d.hpp>

using cppid::gm3d::point_3d;
using point3f = point_3d<float>;

TEST_CASE("float_point3_test traits")
{
  REQUIRE(std::is_trivial_v<point3f>);
  REQUIRE(std::is_standard_layout_v<point3f>);
  REQUIRE(sizeof(point3f) == (sizeof(float) * 3));

  REQUIRE((
   std::is_same_v<float, typename boost::qvm::vec_traits<point3f>::scalar_type>));
  REQUIRE(boost::qvm::vec_traits<point3f>::dim == 3);
}

TEST_CASE("float_point3_test initialization")
{
  {
    auto vt = point3f{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vt = point3f{1.5, 2.2, 8.9};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.2f);
    REQUIRE(vt.z() == 8.9f);
  }
  {
    auto vt = point3f{point3f{1.5, 2.3, 6.4}};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.3f);
    REQUIRE(vt.z() == 6.4f);
  }
  {
    auto vt = point3f{point_3d<int>{0}};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vt = point3f{0};
    vt = point_3d<int>{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vd = point_3d<double>{0};
    point3f vt = vd;
    CHECK(vt.x() == 0.0f);
    CHECK(vt.y() == 0.0f);
    CHECK(vt.z() == 0.0f);
  }
}

TEST_CASE("float_point3_test comparison")
{
  REQUIRE((point3f{0} == point3f{0, 0, 0}));
  REQUIRE((point3f{3.5} == point3f{3.5, 3.5, 3.5}));
  REQUIRE((point3f{-.5} == point3f{-.5, -.5, -.5}));

  REQUIRE((point3f{-.5} != point3f{-.5, -.1, -.5}));
}
