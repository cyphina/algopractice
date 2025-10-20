#include <catch2/catch_test_macros.hpp>
#include <unordered_set>
#include "graph/RopeClimb.h"

TEST_CASE("Test Rope Climb", "[bfs]")
{
   const auto RopeClimbResult1{RopeClimb::RopeClimb(4, 10, {8})};
   REQUIRE(RopeClimbResult1.value().Value == 4);

   const auto RopeClimbResult2{RopeClimb::RopeClimb(4, 10, {2, 3, 8})};
   REQUIRE(RopeClimbResult2.value().Value == 5);
}
