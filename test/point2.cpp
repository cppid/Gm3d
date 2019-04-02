#include <cfloat>
#include <type_traits>

#include <boost/qvm/all.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cppid/gm3d/point_2d.hpp>

using cppid::gm3d::point_2d;
using point2f = point_2d<float>;

TEST_CASE("float_point2_test traits")
{
  REQUIRE(std::is_trivial_v<point2f>);
  REQUIRE(std::is_standard_layout_v<point2f>);
  REQUIRE(sizeof(point2f) == (sizeof(float) * 2));

  REQUIRE((
   std::is_same_v<float, typename boost::qvm::vec_traits<point2f>::scalar_type>));
  REQUIRE(boost::qvm::vec_traits<point2f>::dim == 2);
}

TEST_CASE("float_point2_test initialization")
{
  {
    auto vt = point2f{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
  }
  {
    auto vt = point2f{1.5, 2.2};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.2f);
  }
  {
    auto vt = point2f{point2f{1.5, 2.3}};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.3f);
  }
  {
    auto vt = point2f{point_2d<int>{0}};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
  }
  {
    auto vt = point2f{0};
    vt = point_2d<int>{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
  }
  {
    auto vd = point_2d<double>{0};
    point2f vt = vd;
    CHECK(vt.x() == 0.0f);
    CHECK(vt.y() == 0.0f);
  }
}

TEST_CASE("float_point2_test comparison")
{
  REQUIRE((point2f{0} == point2f{0, 0}));
  REQUIRE((point2f{3.5} == point2f{3.5, 3.5}));
  REQUIRE((point2f{-.5} == point2f{-.5, -.5}));

  REQUIRE((point2f{-.5} != point2f{-.5, -.1}));
}
