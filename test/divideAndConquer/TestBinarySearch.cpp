#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include "divideAndConquer/BinarySearch.h"

TEST_CASE("Binary Search", "[divideAndConquer]")
{
   std::vector<int> Empty      = {};
   std::vector<int> Single     = {5};
   std::vector<int> TwoArray   = {4, 6};
   std::vector<int> ThreeArray = {4, 10, 18};

   auto             View = std::views::iota(1, 100);
   std::vector<int> HundredArray;
   std::ranges::copy(View, std::back_inserter(HundredArray));

   REQUIRE(DivideAndConquer::BinarySearch(Empty, 5) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(Single, 5) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(Single, 3) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(TwoArray, 3) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(TwoArray, 4) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(TwoArray, 6) == 1);
   REQUIRE(DivideAndConquer::BinarySearch(TwoArray, 5) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 4) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 10) == 1);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 18) == 2);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 0) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 5) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 12) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(ThreeArray, 20) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(HundredArray, 1) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(HundredArray, 101) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(HundredArray, 26) == 25);
   REQUIRE(DivideAndConquer::BinarySearch(HundredArray, 97) == 96);
}
