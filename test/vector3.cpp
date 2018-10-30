#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gm3d/Vec3.hpp>

using gm3d::Vec3;
using Vec3f = Vec3<float>;

TEST_CASE("float_vector3_test traits")
{
  REQUIRE(std::is_trivial_v<Vec3f>);
  REQUIRE(std::is_standard_layout_v<Vec3f>);
  REQUIRE(sizeof(Vec3f) == (sizeof(float) * 3));
}

TEST_CASE("float_vector3_test initialization")
{
  {
    auto vt = Vec3f{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.2f);
    REQUIRE(vt.z() == 8.9f);
  }
  {
    auto vt = Vec3f{Vec3f{1.5, 2.3, 6.4}};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.3f);
    REQUIRE(vt.z() == 6.4f);
  }
  {
    auto vt = Vec3f{Vec3<int>{0}};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
    REQUIRE(vt.z() == 0.0f);
  }
}

TEST_CASE("float_vector3_test comparison")
{
  REQUIRE((Vec3f{0} == Vec3f{0, 0, 0}));
  REQUIRE((Vec3f{3.5} == Vec3f{3.5, 3.5, 3.5}));
  REQUIRE((Vec3f{-.5} == Vec3f{-.5, -.5, -.5}));

  REQUIRE((Vec3f{-.5} != Vec3f{-.5, -.1, -.5}));
}

TEST_CASE("float_vector3_test addition")
{
  {
    auto vt = Vec3f{-10.4, 0.4, -15.4};
    vt += Vec3f{0};
    REQUIRE(vt.x() == Approx(-10.4f));
    REQUIRE(vt.y() == Approx(0.4f));
    REQUIRE(vt.z() == Approx(-15.4f));
  }
  {
    auto vt = Vec3f{10.4, -2.2, 5.5};
    vt += 3.2;
    REQUIRE(vt.x() == Approx(13.6f));
    ;
    REQUIRE(vt.y() == Approx(1.0f));
    ;
    REQUIRE(vt.z() == Approx(8.7f));
    ;
  }
  {
    auto vt = Vec3f{0} + Vec3f{2.5, 0.3, 7.4};
    REQUIRE(vt.x() == Approx(2.5f));
    REQUIRE(vt.y() == Approx(0.3f));
    REQUIRE(vt.z() == Approx(7.4f));
  }
  {
    auto vt = Vec3f{-1., 0, 1} + 0.2;
    REQUIRE(vt.x() == Approx(-0.8f));
    REQUIRE(vt.y() == Approx(0.2f));
    REQUIRE(vt.z() == Approx(1.2f));
  }
  {
    auto vt = 0.2 + Vec3f{-1., 0, 1};
    REQUIRE(vt.x() == Approx(-0.8f));
    REQUIRE(vt.y() == Approx(0.2f));
    REQUIRE(vt.z() == Approx(1.2f));
  }
}

TEST_CASE("float_vector3_test subtraction")
{
  {
    auto vt = Vec3f{0};
    vt -= Vec3f(-10.4, 0.4, -15.4);
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9};
    vt -= 3.2;
    REQUIRE(vt.x() == Approx(-1.7f));
    REQUIRE(vt.y() == Approx(-1.f));
    REQUIRE(vt.z() == Approx(5.7f));
  }
  {
    auto vt = Vec3f{1.5, 2.2, 8.9} - Vec3f{0};
    REQUIRE(vt.x() == Approx(1.5f));
    REQUIRE(vt.y() == Approx(2.2f));
    REQUIRE(vt.z() == Approx(8.9f));
  }
  {
    auto vt = Vec3f{2.5, -0.3, 7.4} - 1;
    REQUIRE(vt.x() == Approx(1.5f));
    REQUIRE(vt.y() == Approx(-1.3f));
    REQUIRE(vt.z() == Approx(6.4f));
  }
  {
    auto vt = 1u - Vec3f{2.5, -0.3, 7.4};
    REQUIRE(vt.x() == Approx(-1.5f));
    REQUIRE(vt.y() == Approx(1.3f));
    REQUIRE(vt.z() == Approx(-6.4f));
  }
}

TEST_CASE("float_vector3_test multiplication")
{
  {
    auto vt = Vec3f(-10.4, 0.4, -15.4);
    vt *= Vec3f{-1};
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = Vec3f(-10.4, 0.4, -15.4);
    vt *= -1l;
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = Vec3f(-10.4, 0.4, -15.4) * Vec3f{-1};
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = Vec3f(-10.4, 0.4, -15.4) * -1.0;
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
  {
    auto vt = -1 * Vec3f(-10.4, 0.4, -15.4);
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
    REQUIRE(vt.z() == Approx(15.4f));
  }
}

TEST_CASE("float_vector3_test division")
{
  {
    auto vt = Vec3f(-10.0, 0.5, 2);
    vt /= Vec3f{2};
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = Vec3f(-10.0, 0.5, 2);
    vt /= 2ull;
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = Vec3f(-10.0, 0.5, 2) / Vec3f{2};
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = Vec3f(-10.0, 0.5, 2) / 2;
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
  {
    auto vt = 2 / Vec3f(-10.0, 0.5, 2);
    REQUIRE(vt.x() == Approx(-0.2f));
    REQUIRE(vt.y() == Approx(4.0f));
    REQUIRE(vt.z() == Approx(1.0f));
  }
}
