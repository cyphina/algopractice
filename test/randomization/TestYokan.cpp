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

   const auto Result2{Yokan::YokanQuery(YokanPieceFlavors, FlavorIndices, 8, 12)};
   CHECK(Result2.has_value());
   CHECK(Result2->queryResult == Yokan::YokanQueryResult::NO);

   const auto Result3{Yokan::YokanQuery(YokanPieceFlavors, FlavorIndices, 5, 6)};
   CHECK(Result3.has_value());
   CHECK(Result3->queryResult == Yokan::YokanQueryResult::YES);
   CHECK(Result3->ValidFlavorIndices.first == 0);
   CHECK(Result3->ValidFlavorIndices.second == 0);
}
