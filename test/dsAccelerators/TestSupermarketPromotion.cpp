#include "dsAccelerators/supermarketPromotion.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("supermarketPromotion, [heap]")
{
   std::vector<uint32_t> Day1Prices{16, 6, 63, 16, 82, 25, 2, 43, 5, 17, 10, 56, 85, 38, 15, 32, 91};
   std::vector<uint32_t> Day2Prices{57};
   const auto            PrizeSum{
       SupermarketPromotion::SupermarketProblem(std::vector<std::vector<uint32_t>>{Day1Prices, Day2Prices})};
   CHECK(PrizeSum == 169);
}
