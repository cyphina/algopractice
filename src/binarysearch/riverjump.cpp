#include "riverjump.h"

#include "core/DebugUtils.h"

namespace
{
   /**
    * Keeps removing rocks to make sure no gaps under `MinGapToCheck` size exist.
    * If it removes more than `NumRemovalsAllowed` then it's not feasible aka we can't achieve `MinGapToCheck` min distance between rocks
    * with `NumRemovalsAllowed`.
    *
    * Throws `std::exception{}` if inputs are incorrect.
    */
   bool MinJumpFeasibilityCheck(const std::vector<uint32_t>& RockPositions, uint32_t MaxRockPosition,
                                uint32_t MinGapToCheck, uint32_t NumRemovalsAllowed)
   {
      PRE_RETURN(!RockPositions.empty(), false);

      uint32_t NumRocksRemoved{};

      uint32_t PrevRockPosition{};

      if(RockPositions[0] < MinGapToCheck)
      {
         ++NumRocksRemoved;
      }
      else
      {
         PrevRockPosition = RockPositions[0];
      }

      for(int i = 1; i < RockPositions.size(); ++i)
      {
         // The vector should be sorted but you never know so be defensive.
         assert(PrevRockPosition < RockPositions[i]);

         if(RockPositions[i] - PrevRockPosition < MinGapToCheck)
         {
            ++NumRocksRemoved;
         }
         else
         {
            PrevRockPosition = RockPositions[i];
         }
      }

      if(MaxRockPosition - RockPositions.back() < MinGapToCheck)
      {
         ++NumRocksRemoved;
      }

      if(NumRocksRemoved > NumRemovalsAllowed)
      {
         return false;
      }

      return true;
   }

}
namespace RiverJump
{
   uint32_t RiverJump(const std::vector<uint32_t>& RockPositions, uint32_t MaxRockPosition, uint32_t NumRemovalsAllowed)
   {
      if(RockPositions.empty())
      {
         return MaxRockPosition;
      }

      // Low and below is feasible. Hi and above is always unfeasible.
      uint32_t Low{0};
      // Start not knowing what's unfeasible.
      uint32_t High{MaxRockPosition + 1};
      uint32_t Mid{(Low + High) / 2};

      // While we maintain the feasible/infeasible split
      while(Low + 1 < High)
      {
         if(MinJumpFeasibilityCheck(RockPositions, MaxRockPosition, Mid, NumRemovalsAllowed))
         {
            Low = Mid;
         }
         else
         {
            High = Mid;
         }

         Mid = (Low + High) / 2;
      }

      return Low;
   }
}
