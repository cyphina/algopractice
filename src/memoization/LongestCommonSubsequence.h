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
      std::vector<std::pair<int, int>> GameIndices;
      uint64_t                         MaxRivalGamePoints{};

      [[nodiscard]] bool                 operator==(const HockeyCommonSubsequenceResult& Rhs) const = default;
      [[nodiscard]] std::strong_ordering operator<=>(const HockeyCommonSubsequenceResult& Rhs) const;
   };

   struct HockeyGameResultData
   {
      HockeyGameResult Result;
      uint8_t          PointsScored{};
   };

   /**
    * Variation of LCS with some rules about when a hockey game.
    */
   HockeyCommonSubsequenceResult HockeyCommonSubsequence(const std::vector<HockeyGameResultData>& Team1Results,
                                                         const std::vector<HockeyGameResultData>& Team2Results);
}
