#include <catch2/catch_test_macros.hpp>
#include "memoization/ForwardsAndBackwards.h"

TEST_CASE("Test Forwards", "[ForwardsAndBackwards]")
{
}

TEST_CASE("Test Backwards", "[ForwardsAndBackwards]")
{
   std::vector<int> Costs{{3, 5, 1, 9, 7, 2, 3}};
   const auto       Result{ForwardsAndBackwards::SolveJumpProblem(Costs, 6)};
   REQUIRE(Result.BestCost == 15);
   const auto ResultForwards{ForwardsAndBackwards::SolveJumpProblemForwards(Costs, 6)};
   REQUIRE(Result.BestCost == 15);
}
