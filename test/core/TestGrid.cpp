#include <array>
#include <catch2/catch_test_macros.hpp>
#include "core/Grid.h"

TEST_CASE("Grid At", "[grid]")
{
   auto Grid{Core::Grid<int>({{1, 2, 3}, {1, 2, 3}})};
   REQUIRE(Grid[0, 2] == 3);
   REQUIRE_THROWS_AS(Core::Grid<int>({{1, 2}, {1, 2, 3}}), std::runtime_error);

   //std::array<std::array<int, 3>, 3> x{{{1, 2, 3}, {1, 2, 3}, {1, 2, 3}}};
   auto Grid2{Core::StaticGrid<int, 3, 3>({{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}})};
   auto Grid3{Core::StaticGrid<int, 3, 2>({{{1, 2, 3}, {4, 5, 6}}})};

   Grid2 = Grid3;

   REQUIRE(!Grid2[2, 0].has_value());
   REQUIRE(!Grid2[2, 1].has_value());
   REQUIRE(!Grid2[2, 2].has_value());
}
