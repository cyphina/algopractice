#include <algorithm>
#include <ranges>
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Test Some Range Functionality", "[ranges]")
{
   std::vector<int> Vec{std::from_range, std::views::iota(0, 100)};
   // Lower bound should give the index we can insert something sorted, aka first index after the element is found
   // where the element is < Value. Aka index of first element where < Value is not true so it would point to element with value 20.
   const auto LowerBound{std::ranges::lower_bound(Vec, 20)};
   REQUIRE(LowerBound == Vec.begin() + 20);
}
