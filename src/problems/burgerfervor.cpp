#include <iostream>
#include <print>

// 4 9 22 - 3 burgers
// 4 9 54 - Max number of burgers multiple feasible solutions. 6 9-minute or 9 4-minute and 2 9-minute.
// 4 9 15 - Can't take more than 2 burgers with 2 leftover. 3 burgers with 3 leftover but we're optimizing leftover.

struct BurgerProblemResult
{
   int BurgersEaten;
   int TimeRemaining;

   [[nodiscard]] auto operator<=>(const int& Rhs) const;
};

auto BurgerProblemResult::operator<=>(const int& Rhs) const
{
   return TimeRemaining <=> Rhs;
}

BurgerProblemResult SolveBurgerProblem(int N, int M, int T)
{
   if(T == 0)
   {
      std::println("T - {}", T);
      return {0, 0};
   }

   if(T < 0)
   {
      std::println("T - {}", T);
      return {-1, T};
   }

   auto Burger1Result{SolveBurgerProblem(N, M, T - N)};
   auto Burger2Result{SolveBurgerProblem(N, M, T - M)};

   BurgerProblemResult Result;

   if(Burger1Result < 0)
   {
      if(Burger2Result < 0)
      {
         // Eat no burgers everything is leftover.
         Result = {0, T};
      }
      else
      {
         Burger2Result.BurgersEaten += 1;
         Result = Burger2Result;
      }
   }
   else
   {
      Burger1Result.BurgersEaten += 1;

      // Both are feasible answers
      if(Burger2Result >= 0)
      {
         Burger2Result.BurgersEaten += 1;
         if(Burger1Result.TimeRemaining == Burger2Result.TimeRemaining)
         {
            if(Burger1Result.BurgersEaten > Burger2Result.BurgersEaten)
            {
               Result = Burger1Result;
            }
            else
            {
               Result = Burger2Result;
            }
         }
         else
         {
            // Less time to drink beer is favored
            if(Burger1Result.TimeRemaining < Burger2Result.TimeRemaining)
            {
               Result = Burger1Result;
            }
            else
            {
               Result = Burger2Result;
            }
         }
      }
      else
      {
         Result = Burger1Result;
      }
   }

   std::println("T {} - Time Remaining {} - - Burger 1 Result {} - Burger 2 Result {}", T, Result.TimeRemaining, Burger1Result.BurgersEaten,
                Burger2Result.BurgersEaten);
   return Result;
}

int main()
{
   std::println("Burger Problem. Input Num Minutes to Eat First Burger n, Num Minutes to Eat Second Burger m, then How Much Time we Have to Eat t");
   int EatTimeFirstBurger{}, EatTimeSecondBurger{}, TotalEatTime{};

   std::println("-1 To Quit");
   while(std::cin >> EatTimeFirstBurger && EatTimeFirstBurger != -1)
   {
      std::cin >> EatTimeSecondBurger >> TotalEatTime;
      if(std::cin)
      {
         const auto Result{SolveBurgerProblem(EatTimeFirstBurger, EatTimeSecondBurger, TotalEatTime)};
         std::println("Result - {} - Time Remaining - {}", Result.BurgersEaten, Result.TimeRemaining);
      }

      std::println("-1 To Quit");
   }
}
