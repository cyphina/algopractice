#include <catch2/catch_test_macros.hpp>
#include "DivideAndConquer/DivideAndConquer.h"

TEST_CASE("Find Maximum Subarray Recursive", "[divideAndConquer]")
{
   std::vector<int> EmptyTest;
   std::vector<int> SingleItemTest{-5};
   std::vector<int> TwoItemTest{-2, 6};
   std::vector<int> ThreeItemTest1{1, -3, 5};
   std::vector<int> ThreeItemTest2{-3, 1, 5};
   std::vector<int> ThreeItemTest3{1, 5, -3};
   std::vector<int> ThreeItemTest4{-1, 5, -3};
   std::vector<int> HandwrittenTest{3, -2, 5, 1, 2, -4, 6};
   /*std::vector<int> randomItemTest;
      std::vector<int> largeConstrainedTest;*/

   const auto EmptyResult           = DivideAndConquer::FindMaximumSubarray(EmptyTest);
   const auto SingleItemResult      = DivideAndConquer::FindMaximumSubarray(SingleItemTest);
   const auto TwoItemTestResult     = DivideAndConquer::FindMaximumSubarray(TwoItemTest);
   const auto ThreeItemTestResult   = DivideAndConquer::FindMaximumSubarray(ThreeItemTest1);
   const auto ThreeItemTestResult2  = DivideAndConquer::FindMaximumSubarray(ThreeItemTest2);
   const auto ThreeItemTestResult3  = DivideAndConquer::FindMaximumSubarray(ThreeItemTest3);
   const auto ThreeItemTestResult4  = DivideAndConquer::FindMaximumSubarray(ThreeItemTest4);
   const auto HandwrittenTestResult = DivideAndConquer::FindMaximumSubarray(HandwrittenTest);

   REQUIRE((EmptyResult.low == 0 && EmptyResult.high == 0 && EmptyResult.max == 0));
   REQUIRE((SingleItemResult.low == 0 && SingleItemResult.high == 0 && SingleItemResult.max == 0));
   REQUIRE((TwoItemTestResult.low == 1 && TwoItemTestResult.high == 1 && TwoItemTestResult.max == 6));
   REQUIRE((ThreeItemTestResult.low == 2 && ThreeItemTestResult.high == 2 && ThreeItemTestResult.max == 5));
   REQUIRE((ThreeItemTestResult2.low == 1 && ThreeItemTestResult2.high == 2 && ThreeItemTestResult2.max == 6));
   REQUIRE((ThreeItemTestResult3.low == 0 && ThreeItemTestResult3.high == 1 && ThreeItemTestResult3.max == 6));
   REQUIRE((ThreeItemTestResult4.low == 1 && ThreeItemTestResult4.high == 1 && ThreeItemTestResult4.max == 5));
   REQUIRE((HandwrittenTestResult.low == 0 && HandwrittenTestResult.high == 6 && HandwrittenTestResult.max == 11));
}

TEST_CASE("Find Maximum Subarray Kadane", "[divideAndConquer]")
{
   std::vector<int> EmptyTest;
   std::vector<int> SingleItemTest{-5};
   std::vector<int> TwoItemTest{-2, 6};
   std::vector<int> ThreeItemTest1{1, -3, 5};
   std::vector<int> ThreeItemTest2{-3, 1, 5};
   std::vector<int> ThreeItemTest3{1, 5, -3};
   std::vector<int> ThreeItemTest4{-1, 5, -3};
   std::vector<int> HandwrittenTest{3, -2, 5, 1, 2, -4, 6};
   /*std::vector<int> randomItemTest;
      std::vector<int> largeConstrainedTest;*/

   const auto EmptyResult           = DivideAndConquer::FindMaximumSubarrayKadane(EmptyTest);
   const auto SingleItemResult      = DivideAndConquer::FindMaximumSubarrayKadane(SingleItemTest);
   const auto TwoItemTestResult     = DivideAndConquer::FindMaximumSubarrayKadane(TwoItemTest);
   const auto ThreeItemTestResult   = DivideAndConquer::FindMaximumSubarrayKadane(ThreeItemTest1);
   const auto ThreeItemTestResult2  = DivideAndConquer::FindMaximumSubarrayKadane(ThreeItemTest2);
   const auto ThreeItemTestResult3  = DivideAndConquer::FindMaximumSubarrayKadane(ThreeItemTest3);
   const auto ThreeItemTestResult4  = DivideAndConquer::FindMaximumSubarrayKadane(ThreeItemTest4);
   const auto HandwrittenTestResult = DivideAndConquer::FindMaximumSubarrayKadane(HandwrittenTest);

   REQUIRE((EmptyResult.low == 0 && EmptyResult.high == 0 && EmptyResult.max == 0));
   REQUIRE((SingleItemResult.low == 0 && SingleItemResult.high == 0 && SingleItemResult.max == 0));
   REQUIRE((TwoItemTestResult.low == 1 && TwoItemTestResult.high == 1 && TwoItemTestResult.max == 6));
   REQUIRE((ThreeItemTestResult.low == 2 && ThreeItemTestResult.high == 2 && ThreeItemTestResult.max == 5));
   REQUIRE((ThreeItemTestResult2.low == 1 && ThreeItemTestResult2.high == 2 && ThreeItemTestResult2.max == 6));
   REQUIRE((ThreeItemTestResult3.low == 0 && ThreeItemTestResult3.high == 1 && ThreeItemTestResult3.max == 6));
   REQUIRE((ThreeItemTestResult4.low == 1 && ThreeItemTestResult4.high == 1 && ThreeItemTestResult4.max == 5));
   REQUIRE((HandwrittenTestResult.low == 0 && HandwrittenTestResult.high == 6 && HandwrittenTestResult.max == 11));
}