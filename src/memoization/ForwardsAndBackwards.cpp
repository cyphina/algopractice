#include "ForwardsAndBackwards.h"
#include <ranges>

namespace
{
   ForwardsAndBackwards::JumpResult SolveJumpProblemBackwardsImpl(const std::vector<int>& SquareCosts,
                                                                  int TargetSquareIndex, int JumpStrength,
                                                                  ForwardsAndBackwards::JumpMemo& Memo)
   {
      if(JumpStrength == 0)
      {
         // Invalid Result
         return {};
      }

      if(const auto MemoizedResult{Memo[TargetSquareIndex, JumpStrength]})
      {
         return MemoizedResult.value();
      }

      // Keep going back till we hit a jump strength of 1 (aka how we started)
      if(TargetSquareIndex == 1 && JumpStrength == 1)
      {
         return {SquareCosts[1], {1}};
      }

      // Case 1 - Jump Right
      ForwardsAndBackwards::JumpResult Result1;
      // If our jump strength is 1 then we couldn't even have jumped right since our jump strength would have been 0
      if(TargetSquareIndex - JumpStrength >= 0 && JumpStrength > 1)
      {
         Result1 = SolveJumpProblemBackwardsImpl(SquareCosts, TargetSquareIndex - JumpStrength, JumpStrength - 1, Memo);
      }
      else
      {
         Result1 = {};
      };

      // Case 2 - Jump Left
      ForwardsAndBackwards::JumpResult Result2;
      if(TargetSquareIndex + JumpStrength < SquareCosts.size())
      {
         Result2 = SolveJumpProblemBackwardsImpl(SquareCosts, TargetSquareIndex + JumpStrength, JumpStrength, Memo);
      }
      else
      {
         Result2 = {};
      }

      if(!Result1.IsValid() && !Result2.IsValid())
      {
         Memo[TargetSquareIndex, JumpStrength] = Result1;
         return Result1;
      }
      else if(!Result1.IsValid())
      {
         Result2.JumpIndices.emplace_back(TargetSquareIndex);
         Result2.BestCost += SquareCosts[TargetSquareIndex];
         Memo[TargetSquareIndex, JumpStrength] = Result2;
         return Result2;
      }
      else if(!Result2.IsValid())
      {
         Result1.JumpIndices.emplace_back(TargetSquareIndex);
         Result1.BestCost += SquareCosts[TargetSquareIndex];

         Memo[TargetSquareIndex, JumpStrength] = Result1;
         return Result1;
      }
      else
      {
         auto BestResult{std::min(Result1, Result2)};
         BestResult.JumpIndices.emplace_back(TargetSquareIndex);
         BestResult.BestCost += SquareCosts[TargetSquareIndex];
         Memo[TargetSquareIndex, JumpStrength] = BestResult;
         return BestResult;
      }
   }

   ForwardsAndBackwards::JumpResult SolveJumpProblemForwardsImpl(const std::vector<int>& SquareCosts,
                                                                 int TargetSquareIndex, int SquareIndex,
                                                                 int JumpStrength, ForwardsAndBackwards::JumpMemo& Memo)
   {
      if(const auto MemoizedSolution{Memo[SquareIndex, JumpStrength]})
      {
         return MemoizedSolution.value();
      }

      if(SquareIndex == TargetSquareIndex)
      {
         return {0, {TargetSquareIndex}};
      }

      ForwardsAndBackwards::JumpResult Result1;
      if(SquareIndex + JumpStrength + 1 < SquareCosts.size())
      {
         Result1 = SolveJumpProblemForwardsImpl(SquareCosts, TargetSquareIndex, SquareIndex + JumpStrength + 1,
                                                JumpStrength + 1, Memo);
      }
      else
      {
         Result1 = {};
      }

      ForwardsAndBackwards::JumpResult Result2;
      if(SquareIndex - JumpStrength >= 0)
      {
         Result2 = SolveJumpProblemForwardsImpl(SquareCosts, TargetSquareIndex, SquareIndex - JumpStrength,
                                                JumpStrength, Memo);
      }
      else
      {
         Result2 = {};
      }

      if(!Result1.IsValid() && !Result2.IsValid())
      {
         Memo[SquareIndex, JumpStrength] = Result1;
         return Result1;
      }
      else if(!Result1.IsValid())
      {
         Result2.BestCost += SquareCosts[SquareIndex];
         Result2.JumpIndices.emplace_back(SquareIndex);
         Memo[SquareIndex, JumpStrength] = Result2;
         return Result2;
      }
      else if(!Result2.IsValid())
      {
         Result1.BestCost += SquareCosts[SquareIndex];
         Result1.JumpIndices.emplace_back(SquareIndex);
         Memo[SquareIndex, JumpStrength] = Result1;
         return Result1;
      }
      else
      {
         auto BestResult{std::min(Result1, Result2)};
         BestResult.BestCost += SquareCosts[SquareIndex];
         BestResult.JumpIndices.emplace_back(SquareIndex);
         Memo[SquareIndex, JumpStrength] = BestResult;
         return BestResult;
      }
   }
}

namespace ForwardsAndBackwards
{
   JumpResult SolveJumpProblem(const std::vector<int>& SquareCosts, int TargetSquareIndex)
   {
      if(TargetSquareIndex == 0)
      {
         return {0, {}};
      }

      if(SquareCosts.empty())
      {
         return {0, {}};
      }

      JumpMemo                Memo{SquareCosts.size(), SquareCosts.size()};
      std::vector<JumpResult> Results;
      Results.reserve(SquareCosts.size());

      for(int i = 1; i < SquareCosts.size(); ++i)
      {
         const auto Result{SolveJumpProblemBackwardsImpl(SquareCosts, TargetSquareIndex, i, Memo)};
         if(Result.IsValid())
         {
            Results.emplace_back(Result);
         }
      }

      auto MaxResult{std::ranges::min(Results)};
      return MaxResult;
   }

   JumpResult SolveJumpProblemForwards(const std::vector<int>& SquareCosts, int TargetSquareIndex)
   {
      JumpMemo Memo{SquareCosts.size(), SquareCosts.size()};
      return SolveJumpProblemForwardsImpl(SquareCosts, TargetSquareIndex, 1, 1, Memo);
   }
}
