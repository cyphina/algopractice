#include <iostream>
#include <print>
#include <vector>
#include "memoization/knapsack.h"

int main()
{
   std::println("Burger Problem. Input Num Minutes to Eat First Burger n, Num Minutes to Eat Second Burger m, then How Much Time we Have to Eat t");
   size_t EatTimeFirstBurger{}, EatTimeSecondBurger{}, TotalEatTime{};

   std::println("-1 To Quit");
   while(std::cin >> EatTimeFirstBurger && EatTimeFirstBurger != -1)
   {
      std::cin >> EatTimeSecondBurger >> TotalEatTime;
      if(std::cin)
      {
         // +1 since we have to store from [0, T]. That's what the algo checks...
         //std::vector<BurgerProblemResult> Memo{TotalEatTime + 1};
         //const auto Result{SolveBurgerProblem(EatTimeFirstBurger, EatTimeSecondBurger, TotalEatTime, Memo)};

         const auto Result{Knapsack::SolveBurgerProblemDynamic(EatTimeFirstBurger, EatTimeSecondBurger, TotalEatTime)};
         std::println("Result - {} - Time Remaining - {}", Result.BurgersEaten, Result.TimeRemaining);

         /*const auto BookResult{SolveBurgerProblemBookWithRemainingTime(EatTimeFirstBurger, EatTimeSecondBurger, TotalEatTime)};
         std::println("Book Result - {} - Time Remaining - {}", BookResult.BurgersEaten, BookResult.TimeRemaining);*/
      }

      std::println("-1 To Quit");
   }
}
