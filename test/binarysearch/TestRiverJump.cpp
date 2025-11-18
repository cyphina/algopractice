#include <vector>
#include "binarysearch/riverjump.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Test River Jump", "[binarysearch]")
{
   std::vector<uint32_t> RockPositions{2, 4, 5, 8};
   const auto            MaxHop{RiverJump::RiverJump(RockPositions, 12, 2)};
   REQUIRE(MaxHop == 4);
   std::vector<uint32_t> RockPositions2{3, 4, 7, 10, 13, 18, 20, 23, 29, 30};
   const auto            MaxHop2{RiverJump::RiverJump(RockPositions2, 35, 2)};
   // Still left with 18 to 20 even after removing some others.
   REQUIRE(MaxHop2 == 2);
}
