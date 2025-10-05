#include <catch2/catch_test_macros.hpp>
#include "memoization/AtLeastKnapsack.h"

TEST_CASE("Test At Least Knapsack", "[knapsack]")
{
   AtLeastKnapsack::PricingSchemes PricingSchemes{{4, 3}, {2, 2}};
   const auto                      Result{AtLeastKnapsack::MoneyGrubbersSolveForAtLeastValue(PricingSchemes, 3)};

   REQUIRE(Result.OptimalPrice == 3);
   REQUIRE(Result.StrategyIndices.size() == 1);
   REQUIRE(Result.StrategyIndices[0] == 4);

   const auto Result2{AtLeastKnapsack::MoneyGrubbersSolveForAtLeastValue(PricingSchemes, 5)};
   REQUIRE(Result2.OptimalPrice == 5);
   REQUIRE(Result2.StrategyIndices.size() == 2);
   REQUIRE(std::ranges::find(Result2.StrategyIndices, 4) != std::end(Result2.StrategyIndices));
   REQUIRE(std::ranges::find(Result2.StrategyIndices, 2) != std::end(Result2.StrategyIndices));

   AtLeastKnapsack::PricingSchemes PricingSchemes2{{1, 1.75}, {3, 4}, {2, 2.5}};
   const auto                      Result3{AtLeastKnapsack::MoneyGrubbersSolveForAtLeastValue(PricingSchemes2, 1)};
   REQUIRE(Result3.OptimalPrice == 1.75);
   const auto Result4{AtLeastKnapsack::MoneyGrubbersSolveForAtLeastValue(PricingSchemes2, 4)};
   REQUIRE(Result4.OptimalPrice == 5);
}
