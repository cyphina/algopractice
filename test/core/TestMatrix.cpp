#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include "core/Matrix.h"

TEST_CASE("Matrix At", "[matrix]")
{
   auto                Range = std::views::iota(1, 17);
   std::array<int, 16> A;
   std::ranges::copy(Range, A.begin());
   const Core::Matrix<int, 4, 4> Mat1{A};

   REQUIRE(Mat1[0, 0] == 1);
   REQUIRE_THROWS_AS(Mat1.At(4, 4), std::out_of_range);
   REQUIRE(Mat1[3, 3] == 16);
}

TEST_CASE("Matrix Multiplication", "[matrix]")
{
   const Core::Matrix<int, 3, 3> Mat1{1, 2, 3, 1, 2, 3, 1, 2, 3};
   const Core::Matrix<int, 3, 3> Mat2{1, 2, 3, 1, 2, 3, 1, 2, 3};
   const auto                    Mat3{Mat1.MultiplyMatrix(Mat2)};

   REQUIRE(Mat3[0, 0] == 6);
   REQUIRE(Mat3[2, 2] == 18);
}
