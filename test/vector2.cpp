#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gm3d/Vec2.hpp>

using gm3d::Vec2;
using Vec2f = Vec2<float>;

TEST_CASE("float_vector2_test traits")
{
  REQUIRE(std::is_trivial_v<Vec2f>);
  REQUIRE(std::is_standard_layout_v<Vec2f>);
  REQUIRE(sizeof(Vec2f) == (sizeof(float) * 2));
}

TEST_CASE("float_vector2_test initialization")
{
  {
    auto vt = Vec2f{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
  }
  {
    auto vt = Vec2f{1.5, 2.2};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.2f);
  }
  {
    auto vt = Vec2f{Vec2f{1.5, 2.3}};
    REQUIRE(vt.x() == 1.5f);
    REQUIRE(vt.y() == 2.3f);
  }
  {
    auto vt = Vec2f{Vec2<int>{0}};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
  }
  {
    auto vt = Vec2f{0};
    vt = Vec2<int>{0};
    REQUIRE(vt.x() == 0.0f);
    REQUIRE(vt.y() == 0.0f);
  }
}

TEST_CASE("float_vector2_test comparison")
{
  REQUIRE((Vec2f{0} == Vec2f{0, 0}));
  REQUIRE((Vec2f{3.5} == Vec2f{3.5, 3.5}));
  REQUIRE((Vec2f{-.5} == Vec2f{-.5, -.5}));

  REQUIRE((Vec2f{-.5} != Vec2f{-.5, -.1}));
}

TEST_CASE("float_vector2_test addition")
{
  {
    auto vt = Vec2f{-10.4, 0.4};
    vt += Vec2f{0};
    REQUIRE(vt.x() == Approx(-10.4f));
    REQUIRE(vt.y() == Approx(0.4f));
  }
  {
    auto vt = Vec2f{10.4, -2.2};
    vt += 3.2;
    REQUIRE(vt.x() == Approx(13.6f));
    REQUIRE(vt.y() == Approx(1.0f));
  }
  {
    auto vt = Vec2f{0} + Vec2f{2.5, 0.3};
    REQUIRE(vt.x() == Approx(2.5f));
    REQUIRE(vt.y() == Approx(0.3f));
  }
  {
    auto vt = Vec2f{-1., 0} + 0.2;
    REQUIRE(vt.x() == Approx(-0.8f));
    REQUIRE(vt.y() == Approx(0.2f));
  }
  {
    auto vt = 0.2 + Vec2f{-1., 0};
    REQUIRE(vt.x() == Approx(-0.8f));
    REQUIRE(vt.y() == Approx(0.2f));
  }
}

TEST_CASE("float_vector2_test subtraction")
{
  {
    auto vt = Vec2f{0};
    vt -= Vec2f(-10.4, 0.4);
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
  }
  {
    auto vt = Vec2f{1.5, 2.2};
    vt -= 3.2;
    REQUIRE(vt.x() == Approx(-1.7f));
    REQUIRE(vt.y() == Approx(-1.f));
  }
  {
    auto vt = Vec2f{1.5, 2.2} - Vec2f{0};
    REQUIRE(vt.x() == Approx(1.5f));
    REQUIRE(vt.y() == Approx(2.2f));
  }
  {
    auto vt = Vec2f{2.5, -0.3} - 1;
    REQUIRE(vt.x() == Approx(1.5f));
    REQUIRE(vt.y() == Approx(-1.3f));
  }
  {
    auto vt = 1u - Vec2f{2.5, -0.3};
    REQUIRE(vt.x() == Approx(-1.5f));
    REQUIRE(vt.y() == Approx(1.3f));
  }
}

TEST_CASE("float_vector2_test multiplication")
{
  {
    auto vt = Vec2f(-10.4, 0.4);
    vt *= Vec2f{-1};
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
  }
  {
    auto vt = Vec2f(-10.4, 0.4);
    vt *= -1l;
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
  }
  {
    auto vt = Vec2f(-10.4, 0.4) * Vec2f{-1};
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
  }
  {
    auto vt = Vec2f(-10.4, 0.4) * -1.0;
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
  }
  {
    auto vt = -1 * Vec2f(-10.4, 0.4);
    REQUIRE(vt.x() == Approx(10.4f));
    REQUIRE(vt.y() == Approx(-0.4f));
  }
}

TEST_CASE("float_vector2_test division")
{
  {
    auto vt = Vec2f(-10.0, 0.5);
    vt /= Vec2f{2};
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
  }
  {
    auto vt = Vec2f(-10.0, 0.5);
    vt /= 2ull;
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
  }
  {
    auto vt = Vec2f(-10.0, 0.5) / Vec2f{2};
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
  }
  {
    auto vt = Vec2f(-10.0, 0.5) / 2;
    REQUIRE(vt.x() == Approx(-5.0f));
    REQUIRE(vt.y() == Approx(0.25f));
  }
  {
    auto vt = 2 / Vec2f(-10.0, 0.5);
    REQUIRE(vt.x() == Approx(-0.2f));
    REQUIRE(vt.y() == Approx(4.0f));
  }
}

TEST_CASE("float_vector2_test reflect")
{
  {
    auto d = Vec2f{10, -2};
    auto r = d.reflect({0, 1});
    REQUIRE(r.x() == Approx(10.f));
    REQUIRE(r.y() == Approx(2.0f));
  }
}