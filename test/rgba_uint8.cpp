#include <cstdint>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <cppid/gm3d/Rgba.hpp>

using Rgba8 = cppid::gm3d::Rgba<std::uint8_t>;

TEST_CASE("rgba_uint8 traits")
{
  REQUIRE(std::is_trivial_v<Rgba8>);
  REQUIRE(std::is_standard_layout_v<Rgba8>);
  REQUIRE(sizeof(Rgba8) == (sizeof(std::uint8_t) * 4));
}

TEST_CASE("rgba_uint8 initialization")
{
  {
    auto col = Rgba8{0};
    REQUIRE(col.r() == 0);
    REQUIRE(col.g() == 0);
    REQUIRE(col.b() == 0);
    REQUIRE(col.a() == 0);
  }
  {
    auto col = Rgba8{0xFF, 0x7F};
    REQUIRE(col.r() == 0xFF);
    REQUIRE(col.g() == 0xFF);
    REQUIRE(col.b() == 0xFF);
    REQUIRE(col.a() == 0x7F);
  }
  {
    auto col = Rgba8{0xFF, 0x7F, 0x50};
    REQUIRE(col.r() == 0xFF);
    REQUIRE(col.g() == 0x7F);
    REQUIRE(col.b() == 0x50);
    REQUIRE(col.a() == 255);
  }
  {
    auto col = Rgba8{0xFF, 0x7F, 0x50, 21};
    REQUIRE(col.r() == 0xFF);
    REQUIRE(col.g() == 0x7F);
    REQUIRE(col.b() == 0x50);
    REQUIRE(col.a() == 21);
  }
}

TEST_CASE("rgba_uint8 equality comparable")
{
  auto cola = Rgba8{0xFF, 0x7F, 0x50, 0x00};
  auto colb = Rgba8{0xFF, 0x7F, 0x50, 0x00};
  auto colc = Rgba8{0xFF, 0x7F, 0x50, 0x00};
  auto cold = Rgba8{0, 0, 0, 0};

  REQUIRE(cola == cola);
  REQUIRE(cola == colb);
  REQUIRE(colb == cola);
  REQUIRE(colb == colc);
  REQUIRE(cola == colc);

  REQUIRE(cola != cold);
}