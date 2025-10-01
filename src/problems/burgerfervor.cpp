#include <iostream>
#include <print>
#include <vector>

// 4 9 22 - 3 burgers
// 4 9 54 - Max number of burgers multiple feasible solutions. 6 9-minute or 9 4-minute and 2 9-minute.
// 4 9 15 - Can't take more than 2 burgers with 2 leftover. 3 burgers with 3 leftover but we're optimizing leftover.

struct BurgerProblemResult
{
   int BurgersEaten{-1};
   int TimeRemaining{-1};

   bool IsSet() const { return BurgersEaten != -1; }

   [[nodiscard]] auto operator<=>(const int& Rhs) const;
};

auto BurgerProblemResult::operator<=>(const int& Rhs) const
{
   return TimeRemaining <=> Rhs;
}

static int TotalCalls{};

/**
 * Our version actually handles tie breakers...
 * Make sure to pass in a vector that is actually sized to T + 1 since we fill out 0 atm...
 */
BurgerProblemResult SolveBurgerProblem(int N, int M, int T, std::vector<BurgerProblemResult>& Memo)
{
   ++TotalCalls;
   std::println("{} Total Calls", TotalCalls);

   if(T == 0)
   {
      //std::println("T - {}", T);
      return {0, 0};
   }

   if(T < 0)
   {
      //std::println("T - {}", T);
      return {-1, T};
   }

   BurgerProblemResult Result1{0, -1};
   BurgerProblemResult Result2{0, -1};

   if(M <= T)
   {
      if(!Memo[T - M].IsSet())
      {
         Result1 = SolveBurgerProblem(N, M, T - M, Memo);
      }
      else
      {
         Result1 = Memo[T - M];
      }
   }

   if(N <= T)
   {
      if(!Memo[T - N].IsSet())
      {
         Result2 = SolveBurgerProblem(N, M, T - N, Memo);
      }
      else
      {
         Result2 = Memo[T - N];
      }
   }

   BurgerProblemResult Result;

   if(Result1 < 0)
   {
      if(Result2 < 0)
      {
         // Eat no burgers everything is leftover.
         Result = {0, T};
      }
      else
      {
         Result2.BurgersEaten += 1;
         Result = Result2;
      }
   }
   else
   {
      Result1.BurgersEaten += 1;

      // Both are feasible answers
      if(Result2 >= 0)
      {
         Result2.BurgersEaten += 1;
         if(Result1.TimeRemaining == Result2.TimeRemaining)
         {
            if(Result1.BurgersEaten > Result2.BurgersEaten)
            {
               Result = Result1;
            }
            else
            {
               Result = Result2;
            }
         }
         else
         {
            // Less time to drink beer is favored
            if(Result1.TimeRemaining < Result2.TimeRemaining)
            {
               Result = Result1;
            }
            else
            {
               Result = Result2;
            }
         }
      }
      else
      {
         Result = Result1;
      }
   }

   //std::println("T {} - Time Remaining {} - - Burger 1 Result {} - Burger 2 Result {}", T, Result.TimeRemaining, Burger1Result.BurgersEaten,
   //             Burger2Result.BurgersEaten);

   std::println("Memoized {}!", T);
   Memo[T] = Result;
   return Result;
}

BurgerProblemResult SolveBurgerProblemDynamic(int M, int N, int T)
{
   std::vector<BurgerProblemResult> Dp{static_cast<size_t>(T + 1)};
   if(!Dp.empty())
   {
      Dp[0] = {.BurgersEaten = 0, .TimeRemaining = 0};
   }

   BurgerProblemResult Result1, Result2;
   for(int i = 1; i < Dp.size(); ++i)
   {
      if(i >= M)
      {
         Result1 = Dp[i - M];
      }

      if(i >= N)
      {
         Result2 = Dp[i - N];
      }

      if(Result1.IsSet() && Result2.IsSet())
      {
         if(Result1.TimeRemaining == Result2.TimeRemaining)
         {
            if(Result1.BurgersEaten > Result2.BurgersEaten)
            {
               Dp[i] = Result1;
            }
            else
            {
               Dp[i] = Result2;
            }
         }
         else
         {
            if(Result1.TimeRemaining < Result2.TimeRemaining)
            {
               Dp[i] = Result1;
            }
            else
            {
               Dp[i] = Result2;
            }
         }
      }
      else if(Result1.IsSet())
      {
         Dp[i] = Result1;
      }
      else if(Result2.IsSet())
      {
         Dp[i] = Result2;
      }
      else
      {
         Dp[i] = Dp[i - 1];
         ++Dp[i].TimeRemaining;
      }

      ++Dp[i].BurgersEaten;
   }

   return Dp[T];
}

/** Version book has but it just returns -1 if you don't have an optimal solution. */
int SolveBurgerProblemResultBook(int M, int N, int T)
{
   int First{}, Second{};
   if(T == 0)
   {
      return 0;
   }

   if(T >= M)
   {
      First = SolveBurgerProblemResultBook(M, N, T - M);
   }
   else
   {
      First = -1;
   }

   if(T >= N)
   {
      Second = SolveBurgerProblemResultBook(M, N, T - N);
   }
   else
   {
      Second = -1;
   }

   if(First == -1 && Second == -1)
   {
      return -1;
   }

   return std::max(First, Second) + 1;
}

BurgerProblemResult SolveBurgerProblemBookWithRemainingTime(int M, int N, int T)
{
   auto Result{SolveBurgerProblemResultBook(M, N, T)};
   int  BackwardsSum{0};
   while(Result == -1)
   {
      ++BackwardsSum;
      Result = SolveBurgerProblemResultBook(M, N, T - BackwardsSum);
   }
   return {Result, BackwardsSum};
}

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

         const auto Result{SolveBurgerProblemDynamic(EatTimeFirstBurger, EatTimeSecondBurger, TotalEatTime)};
         std::println("Result - {} - Time Remaining - {}", Result.BurgersEaten, Result.TimeRemaining);

         /*const auto BookResult{SolveBurgerProblemBookWithRemainingTime(EatTimeFirstBurger, EatTimeSecondBurger, TotalEatTime)};
         std::println("Book Result - {} - Time Remaining - {}", BookResult.BurgersEaten, BookResult.TimeRemaining);*/
      }

      std::println("-1 To Quit");
   }
}
