#pragma once
#include <vector>

namespace Knapsack
{
   // 4 9 22 - 3 burgers
   // 4 9 54 - Max number of burgers multiple feasible solutions. 6 9-minute or 9 4-minute and 2 9-minute.
   // 4 9 15 - Can't take more than 2 burgers with 2 leftover. 3 burgers with 3 leftover but we're optimizing leftover.

   struct BurgerProblemResult
   {
      int BurgersEaten{-1};
      int TimeRemaining{-1};

      bool IsSet() const { return BurgersEaten != -1; }

      // User generated operator== from the non defaulted <=> means we have to default an `operator<=>`.
      [[nodiscard]] auto operator<=>(const BurgerProblemResult& Rhs) const = default;
      [[nodiscard]] auto operator<=>(const int& Rhs) const;
   };

   inline auto BurgerProblemResult::operator<=>(const int& Rhs) const
   {
      return TimeRemaining <=> Rhs;
   }

   /**
    * Our version actually handles tie breakers...
    * Make sure to pass in a vector that is actually sized to T + 1 since we fill out 0 atm...
    */
   BurgerProblemResult SolveBurgerMemoized(int N, int M, int T, std::vector<BurgerProblemResult>& Memo);

   BurgerProblemResult SolveBurgerProblemDynamic(int M, int N, int T);

   BurgerProblemResult SolveBurgerProblemBookWithRemainingTime(int M, int N, int T);
}
