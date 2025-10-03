#include <catch2/catch_test_macros.hpp>
#include "memoization/Knapsack.h"

TEST_CASE("Test Knapsack", "[knapsack]")
{
   // 4 9 22 - 3 burgers
   // 4 9 54 - Max number of burgers multiple feasible solutions. 6 9-minute or 9 4-minute and 2 9-minute.
   // 4 9 15 - Can't take more than 2 burgers with 2 leftover. 3 burgers with 3 leftover but we're optimizing leftover.

   constexpr auto                             T1{22};
   std::vector<Knapsack::BurgerProblemResult> Memo;
   Memo.resize(T1 + 1);
   const auto Test1Result{Knapsack::SolveBurgerMemoized(4, 9, T1, Memo)};
   const auto Test1Result2{Knapsack::SolveBurgerProblemBookWithRemainingTime(4, 9, T1)};
   const auto Test1Result3{Knapsack::SolveBurgerProblemDynamic(4, 9, T1)};

   constexpr auto                             T2{54};
   std::vector<Knapsack::BurgerProblemResult> Memo2;
   Memo2.resize(T2 + 1);
   const auto Test2Result{Knapsack::SolveBurgerMemoized(4, 9, T2, Memo2)};
   const auto Test2Result2{Knapsack::SolveBurgerProblemBookWithRemainingTime(4, 9, T2)};
   const auto Test2Result3{Knapsack::SolveBurgerProblemDynamic(4, 9, T2)};

   constexpr auto                             T3{15};
   std::vector<Knapsack::BurgerProblemResult> Memo3;
   Memo3.resize(T3 + 1);
   const auto Test3Result{Knapsack::SolveBurgerMemoized(4, 9, T3, Memo3)};
   const auto Test3Result2{Knapsack::SolveBurgerProblemBookWithRemainingTime(4, 9, T3)};
   const auto Test3Result3{Knapsack::SolveBurgerProblemDynamic(4, 9, T3)};

   REQUIRE((Test1Result == Test1Result2 && Test1Result2 == Test1Result3));
   REQUIRE((Test2Result == Test2Result2 && Test2Result2 == Test2Result3));
   REQUIRE((Test3Result == Test3Result2 && Test3Result2 == Test3Result3));
}
