#pragma once

#include <vector>

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
      uint64_t         MaxRivalGamePoints;
   };

   struct HockeyGameResultData
   {
      HockeyGameResult Result;
      uint8_t          PointsScored;
   };

   /**
    * 
    * @return 
    */
   HockeyCommonSubsequenceResult HockeyCommonSubsequence(const std::vector<HockeyGameResultData>& Team1Results,
                                                         const std::vector<HockeyGameResultData>& Team2Results, int Seq1SubproblemIndex,
                                                         int Seq2SubproblemIndex)
   {
      if(Seq1SubproblemIndex == 0 && Seq2SubproblemIndex == 0)
      {
         return
      }
   }
}
