#include "binarysearch/feedingants.h"
#include "core/MathUtil.h"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("Binary Search Ant", "[binarysearch]")
{
   std::vector                            Pipes{{
       FeedingAnts::TerrariumEdge{0, 1, {.2f}},
       FeedingAnts::TerrariumEdge{0, 2, {.5f}},
       FeedingAnts::TerrariumEdge{0, 3, {.3f, true}},
       FeedingAnts::TerrariumEdge{3, 4, {.5f}},
       FeedingAnts::TerrariumEdge{3, 5, {.5f}},
   }};
   std::vector<FeedingAnts::NodeDataType> RequiredLiquidForAnts{{{}, 2, 9, {}, 7, 8}};

   const auto Result{FeedingAnts::FeedingAntsProblem(std::move(Pipes), std::move(RequiredLiquidForAnts))};

   REQUIRE(MathUtil::NearlyEqualAbs(Result.value(), 18, 1e-04));
}
