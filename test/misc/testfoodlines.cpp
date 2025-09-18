#include <catch2/catch_test_macros.hpp>
#include "misc/foodlines.h"

TEST_CASE("Test Foodlines", "[foodlines]")
{
   const auto Result = FoodLines::foodLine(3, 5, {3, 2, 5});
   REQUIRE(Result[0].lineIndex == 1);
   REQUIRE(Result[1].lineIndex == 0);
   REQUIRE(Result[2].lineIndex == 1);
   REQUIRE(Result[3].lineIndex == 0);
   REQUIRE(Result[4].lineIndex == 1);
}
