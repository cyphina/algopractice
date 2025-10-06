#pragma once

#include <vector>
#include "core/Grid.h"

namespace LongestCommonSubsequence
{
   enum class HockeyGameResult : uint8_t
   {
      Win,
      Loss,
   };

   struct HockeyCommonSubsequenceResult
   {
      std::vector<int> GameIndex;
      uint64_t         MaxRivalGamePoints{};
   };

   struct HockeyGameResultData
   {
      HockeyGameResult Result;
      uint8_t          PointsScored{};
   };

   /**
    * 
    */
   inline HockeyCommonSubsequenceResult HockeyCommonSubsequence(const std::vector<HockeyGameResultData>& Team1Results,
                                                                const std::vector<HockeyGameResultData>& Team2Results, int Seq1SubproblemIndex,
                                                                int Seq2SubproblemIndex, Core::Grid<HockeyGameResultData>& Memo)
   {
      if(Seq1SubproblemIndex == 0 && Seq2SubproblemIndex == 0)
      {
         return {};
      }

      HockeyCommonSubsequenceResult MaxResult;

      // 1 - Optimal solution uses final games.
      // 2 - Optional solution doesn't use final games.
      // 3 - Ignore last result of team 1.
      // 4 - Ignore last result of team 2.

      return MaxResult;
   }
}
