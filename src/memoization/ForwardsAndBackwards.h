
#pragma once
#include "core/Grid.h"

namespace ForwardsAndBackwards
{
   struct JumpResult
   {
      int              BestCost{-1};
      std::vector<int> JumpIndices;

      bool IsValid() const { return BestCost > -1; }

      [[nodiscard]] auto operator==(const JumpResult& Rhs) const { return BestCost == Rhs.BestCost; }
      [[nodiscard]] auto operator<=>(const JumpResult& Rhs) const { return BestCost <=> Rhs.BestCost; }
   };

   using JumpMemo = Core::Grid<JumpResult>;

   JumpResult SolveJumpProblem(const std::vector<int>& SquareCosts, int TargetSquareIndex);
   JumpResult SolveJumpProblemForwards(const std::vector<int>& SquareCosts, int TargetSquareIndex);
}
