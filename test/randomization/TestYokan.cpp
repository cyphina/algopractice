#include "randomization/Yokan.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("YokanProblem", "[randomization]")
{
   SECTION("Empty Case")
   {
      std::vector<uint32_t>      YokanPieceFlavors;
      const Yokan::FlavorIndices FlavorIndices{0};

      const auto Result{Yokan::YokanQuery(YokanPieceFlavors, FlavorIndices, 2, 11)};

      CHECK(!Result.has_value());
   }

   std::vector<uint32_t> YokanPieceFlavors{1, 3, 4, 2, 1, 1, 2, 4, 1, 2, 2, 4, 1, 1};
   const auto            FlavorIndices{Yokan::BuildFlavorIndices(4, YokanPieceFlavors)};
   const auto            Result{Yokan::YokanQuery(YokanPieceFlavors, FlavorIndices, 2, 11)};

   CHECK(Result.has_value());
   CHECK(Result->queryResult == Yokan::YokanQueryResult::YES);
   CHECK((Result->ValidFlavorIndices.first == 0 || Result->ValidFlavorIndices.first == 1));
   CHECK((Result->ValidFlavorIndices.second == 0 || Result->ValidFlavorIndices.second == 1));
}
