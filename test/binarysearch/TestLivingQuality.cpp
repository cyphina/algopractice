#include "binarysearch/livingquality.h"
#include "core/Grid.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Test Living Quality", "[binarysearch]")
{
   const Core::Grid<uint32_t> Grid{{{48, 16, 15, 45, 40, 28, 8},
                                    {20, 11, 36, 19, 24, 6, 33},
                                    {22, 39, 30, 7, 9, 1, 18},
                                    {14, 35, 2, 13, 31, 12, 46},
                                    {32, 37, 21, 3, 41, 23, 29},
                                    {42, 49, 38, 10, 17, 47, 5},
                                    {43, 4, 34, 25, 26, 27, 44}}};

   SECTION("Test Median Rectangle Calculation")
   {
      const auto RectMedian{LivingQuality::CalculateMinimumMedianRectangle(Grid, 5, 3, {0, 0})};
      const auto RectMedian2{LivingQuality::CalculateMinimumMedianRectangle(Grid, 2, 2, {0, 0})};

      CHECK(RectMedian == 22);
      CHECK(RectMedian2 == 18);
   }

   SECTION("Test Brute Force")
   {
      const auto MinimumMedianRectangle{LivingQuality::FindMinimumMedianRectangleInCityBrute(Grid, 5, 3)};
      CHECK(MinimumMedianRectangle == 13);
   }
}
