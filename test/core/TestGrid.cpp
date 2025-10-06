#include <catch2/catch_test_macros.hpp>
#include "core/Grid.h"

TEST_CASE("Grid At", "[grid]")
{
   auto Grid{Core::Grid<int>({{1, 2, 3}, {1, 2, 3}})};
   REQUIRE(Grid[0, 2] == 3);
   REQUIRE_THROWS_AS(Core::Grid<int>({{1, 2}, {1, 2, 3}}), std::runtime_error);
}
