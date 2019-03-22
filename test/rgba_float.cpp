#include <cstdint>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cppid/gm3d/Rgba.hpp>

using u8 = std::uint8_t;
using Rgba8 = cppid::gm3d::Rgba<u8>;
using Rgbaf = cppid::gm3d::Rgba<float>;

TEST_CASE("rgba_uint8 traits")
{
  REQUIRE(std::is_trivial_v<Rgbaf>);
  REQUIRE(std::is_standard_layout_v<Rgbaf>);
  REQUIRE(sizeof(Rgbaf) == (sizeof(float) * 4));
}

TEST_CASE("rgba_uint8 initialization")
{
  {
    auto col = Rgbaf{0};
    REQUIRE(col.r() == 0.0f);
    REQUIRE(col.g() == 0.0f);
    REQUIRE(col.b() == 0.0f);
    REQUIRE(col.a() == 0.0f);
  }
  {
    auto col = Rgbaf{0.4, 0.4};
    REQUIRE(col.r() == Approx(0.4f));
    REQUIRE(col.g() == Approx(0.4f));
    REQUIRE(col.b() == Approx(0.4f));
    REQUIRE(col.a() == Approx(0.4f));
  }
  {
    auto col = Rgbaf{0.6, 0.4, 1.8};
    REQUIRE(col.r() == Approx(0.6f));
    REQUIRE(col.g() == Approx(0.4f));
    REQUIRE(col.b() == Approx(1.8f));
    REQUIRE(col.a() == Approx(1.0f));
  }
  {
    auto col = Rgbaf{0.6, 0.4, 1.8, 1.0};
    REQUIRE(col.r() == Approx(0.6f));
    REQUIRE(col.g() == Approx(0.4f));
    REQUIRE(col.b() == Approx(1.8f));
    REQUIRE(col.a() == Approx(1.0f));
  }
  {
    auto col = Rgbaf{u8{45}, u8{201}, u8{99}, u8{255}};
    REQUIRE(col.r() == Approx(0.176471));
    REQUIRE(col.g() == Approx(0.788235));
    REQUIRE(col.b() == Approx(0.388235));
    REQUIRE(col.a() == Approx(1.0));
  }
  {
    auto col = Rgbaf{Rgba8{45, 201, 99, 255}};
    REQUIRE(col.r() == Approx(0.176471));
    REQUIRE(col.g() == Approx(0.788235));
    REQUIRE(col.b() == Approx(0.388235));
    REQUIRE(col.a() == Approx(1.0));
  }
  {
    auto cu8 = Rgba8{45, 201, 99, 255};
    auto col = Rgbaf{cu8};
    REQUIRE(col.r() == Approx(0.176471));
    REQUIRE(col.g() == Approx(0.788235));
    REQUIRE(col.b() == Approx(0.388235));
    REQUIRE(col.a() == Approx(1.0));
  }
}

TEST_CASE("rgba_uint8 equality comparable")
{
  auto cola = Rgbaf{0.6, 0.4, 1.8, 1.0};
  auto colb = Rgbaf{0.6, 0.4, 1.8, 1.0};
  auto colc = Rgbaf{0.6, 0.4, 1.8, 1.0};
  auto cold = Rgbaf{0, 0, 0, 0};

  REQUIRE(cola == cola);
  REQUIRE(cola == colb);
  REQUIRE(colb == cola);
  REQUIRE(colb == colc);
  REQUIRE(cola == colc);

  REQUIRE(cola != cold);
}