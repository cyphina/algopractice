#include "Knapsack.h"
#include <iostream>
#include <print>

namespace
{
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
}

namespace Knapsack
{
   BurgerProblemResult SolveBurgerMemoized(int N, int M, int T, std::vector<BurgerProblemResult>& Memo)
   {
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
            Result1 = SolveBurgerMemoized(N, M, T - M, Memo);
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
            Result2 = SolveBurgerMemoized(N, M, T - N, Memo);
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

      //std::println("Memoized {}!", T);
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
            Result1.BurgersEaten += 1;
         }

         if(i >= N)
         {
            Result2 = Dp[i - N];
            Result2.BurgersEaten += 1;
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
      }

      return Dp[T];
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
}
