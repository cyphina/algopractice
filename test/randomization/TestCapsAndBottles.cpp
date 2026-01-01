#include "randomization/CapsAndBottles.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("CapsAndBottles", "[randomization]")
{
   std::vector<uint32_t> CapSizes{23, 85, 8, 17, 55};
   std::vector<uint32_t> BottleSizes{85, 23, 8, 55, 17};

   const auto Result{CapsAndBottles::MatchCapsAndBottles(CapSizes, BottleSizes)};

   for(uint32_t KeyIndex{}; KeyIndex < 5; ++KeyIndex)
   {
      auto it = std::ranges::find_if(Result,
                                     [KeyIndex](const auto& p)
                                     {
                                        return p.first == KeyIndex;
                                     });

      CHECK(it != Result.end());

      switch(it->first)
      {
         case 0:
         {
            CHECK(it->second == 1);
            break;
         }
         case 1:
         {
            CHECK(it->second == 0);
            break;
         }
         case 2:
         {
            CHECK(it->second == 2);
            break;
         }
         case 3:
         {
            CHECK(it->second == 4);
            break;
         }
         case 4:
         {
            CHECK(it->second == 3);
            break;
         }
         default:
         {
            FAIL();
            break;
         }
      }
   }
}
