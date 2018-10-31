#include <cfloat>
#include <type_traits>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <gm3d/Mat3.hpp>

using gm3d::Mat3;
using gm3d::Mat4;
using Mat3f = Mat3<float>;

TEST_CASE("float_matrix3_test traits")
{
  REQUIRE(std::is_trivial_v<Mat3f>);
  REQUIRE(std::is_standard_layout_v<Mat3f>);
  REQUIRE(sizeof(Mat3f) == (sizeof(float) * 9));
}

TEST_CASE("float_matrix3_test initialization")
{
  {
    auto mat = Mat3f{1};
    REQUIRE(mat.m00() == 1.0f);
    REQUIRE(mat.m01() == 0.0f);
    REQUIRE(mat.m02() == 0.0f);

    REQUIRE(mat.m10() == 0.0f);
    REQUIRE(mat.m11() == 1.0f);
    REQUIRE(mat.m12() == 0.0f);

    REQUIRE(mat.m20() == 0.0f);
    REQUIRE(mat.m21() == 0.0f);
    REQUIRE(mat.m22() == 1.0f);
  }
  {
    auto mat =
     Mat3f{0.0f, 1.0f, 2.0f, 10.0f, 11.0f, 12.0f, 20.0f, 21.0f, 22.0f};

    REQUIRE(mat.m00() == 0.0f);
    REQUIRE(mat.m01() == 1.0f);
    REQUIRE(mat.m02() == 2.0f);

    REQUIRE(mat.m10() == 10.0f);
    REQUIRE(mat.m11() == 11.0f);
    REQUIRE(mat.m12() == 12.0f);

    REQUIRE(mat.m20() == 20.0f);
    REQUIRE(mat.m21() == 21.0f);
    REQUIRE(mat.m22() == 22.0f);
  }
  {
    auto mat = Mat3f{Mat4<int>{1}};

    REQUIRE(mat.m00() == 1.0f);
    REQUIRE(mat.m01() == 0.0f);
    REQUIRE(mat.m02() == 0.0f);

    REQUIRE(mat.m10() == 0.0f);
    REQUIRE(mat.m11() == 1.0f);
    REQUIRE(mat.m12() == 0.0f);

    REQUIRE(mat.m20() == 0.0f);
    REQUIRE(mat.m21() == 0.0f);
    REQUIRE(mat.m22() == 1.0f);
  }
}