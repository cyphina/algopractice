#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include "divideAndConquer/BinarySearch.h"

TEST_CASE("Binary Search", "[divideAndConquer]")
{
   std::vector<int> empty      = {};
   std::vector<int> single     = {5};
   std::vector<int> twoArray   = {4, 6};
   std::vector<int> threeArray = {4, 10, 18};

   auto             view = std::views::iota(1, 100);
   std::vector<int> hundredArray;
   std::ranges::copy(view, std::back_inserter(hundredArray));

   REQUIRE(DivideAndConquer::BinarySearch(empty, 5) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(single, 5) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(single, 3) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(twoArray, 3) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(twoArray, 4) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(twoArray, 6) == 1);
   REQUIRE(DivideAndConquer::BinarySearch(twoArray, 5) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 4) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 10) == 1);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 18) == 2);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 0) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 5) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 12) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(threeArray, 20) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(hundredArray, 1) == 0);
   REQUIRE(DivideAndConquer::BinarySearch(hundredArray, 101) == -1);
   REQUIRE(DivideAndConquer::BinarySearch(hundredArray, 26) == 25);
   REQUIRE(DivideAndConquer::BinarySearch(hundredArray, 97) == 96);
}