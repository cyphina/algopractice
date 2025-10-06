#include "LongestCommonSubsequence.h"
#include <array>

namespace
{
   using namespace LongestCommonSubsequence;

   HockeyCommonSubsequenceResult GetOrTrySetMemoizedValue(Core::Grid<HockeyCommonSubsequenceResult>& Memo,
                                                          const std::vector<::HockeyGameResultData>& Team1Results,
                                                          const std::vector<::HockeyGameResultData>& Team2Results,
                                                          int Index1, int Index2);

   HockeyCommonSubsequenceResult HockeyCommonSubsequenceImpl(const std::vector<::HockeyGameResultData>& Team1Results,
                                                             const std::vector<::HockeyGameResultData>& Team2Results,
                                                             int Seq1SubproblemIndex, int Seq2SubproblemIndex,
                                                             Core::Grid<HockeyCommonSubsequenceResult>& Memo)
   {
      if(Seq1SubproblemIndex < 0 || Seq2SubproblemIndex < 0)
      {
         return {};
      }

      HockeyCommonSubsequenceResult MaxResult;

      // 1 - Optimal solution uses final games.
      // 2 - Optional solution doesn't use final games.
      // 3 - Ignore last result of team 1.
      // 4 - Ignore last result of team 2.

      const auto& FinalResult1{Team1Results[Seq1SubproblemIndex]};
      const auto& FinalResult2{Team2Results[Seq2SubproblemIndex]};

      HockeyCommonSubsequenceResult Case1Result;

      if((FinalResult1.Result != FinalResult2.Result))
      {
         if(FinalResult1.Result == HockeyGameResult::Win)
         {
            if(FinalResult1.PointsScored > FinalResult2.PointsScored)
            {
               const auto PointsScored{FinalResult1.PointsScored + FinalResult2.PointsScored};
               if(Seq1SubproblemIndex > 0 && Seq2SubproblemIndex > 0)
               {
                  Case1Result = GetOrTrySetMemoizedValue(Memo, Team1Results, Team2Results, Seq1SubproblemIndex - 1,
                                                         Seq2SubproblemIndex - 1);
               }
               Case1Result.MaxRivalGamePoints += PointsScored;
               Case1Result.GameIndices.emplace_back(Seq1SubproblemIndex, Seq2SubproblemIndex);
            }
         }
         else
         {
            if(FinalResult1.PointsScored < FinalResult2.PointsScored)
            {
               const auto PointsScored{FinalResult1.PointsScored + FinalResult2.PointsScored};
               if(Seq1SubproblemIndex > 0 && Seq2SubproblemIndex > 0)
               {
                  Case1Result = GetOrTrySetMemoizedValue(Memo, Team1Results, Team2Results, Seq1SubproblemIndex - 1,
                                                         Seq2SubproblemIndex - 1);
               }
               Case1Result.MaxRivalGamePoints += PointsScored;
               Case1Result.GameIndices.emplace_back(Seq1SubproblemIndex, Seq2SubproblemIndex);
            }
         }
      }

      HockeyCommonSubsequenceResult Case2Result;
      if(Seq1SubproblemIndex > 0 && Seq2SubproblemIndex > 0)
      {
         Case2Result = GetOrTrySetMemoizedValue(Memo, Team1Results, Team2Results, Seq1SubproblemIndex - 1,
                                                Seq2SubproblemIndex - 1);
      }

      HockeyCommonSubsequenceResult Case3Result;
      if(Seq1SubproblemIndex > 0)
      {
         Case3Result =
             GetOrTrySetMemoizedValue(Memo, Team1Results, Team2Results, Seq1SubproblemIndex - 1, Seq2SubproblemIndex);
      }

      HockeyCommonSubsequenceResult Case4Result;
      if(Seq2SubproblemIndex > 0)
      {
         Case4Result =
             GetOrTrySetMemoizedValue(Memo, Team1Results, Team2Results, Seq1SubproblemIndex, Seq2SubproblemIndex - 1);
      }

      std::array Results{Case1Result, Case2Result, Case3Result, Case4Result};

      return std::ranges::max(Results);
   }

   HockeyCommonSubsequenceResult GetOrTrySetMemoizedValue(Core::Grid<HockeyCommonSubsequenceResult>& Memo,
                                                          const std::vector<::HockeyGameResultData>& Team1Results,
                                                          const std::vector<::HockeyGameResultData>& Team2Results,
                                                          int Index1, int Index2)
   {
      auto& MemoizedValue{Memo[Index1, Index2]};
      if(MemoizedValue.has_value())
      {
         return MemoizedValue.value();
      }
      else
      {
         MemoizedValue = HockeyCommonSubsequenceImpl(Team1Results, Team2Results, Index1, Index2, Memo);
         return MemoizedValue.value();
      }
   }

}

namespace LongestCommonSubsequence
{
   std::strong_ordering HockeyCommonSubsequenceResult::operator<=>(const HockeyCommonSubsequenceResult& Rhs) const
   {
      return MaxRivalGamePoints <=> Rhs.MaxRivalGamePoints;
   }

   HockeyCommonSubsequenceResult HockeyCommonSubsequence(const std::vector<HockeyGameResultData>& Team1Results,
                                                         const std::vector<HockeyGameResultData>& Team2Results)
   {
      Core::Grid<HockeyCommonSubsequenceResult> Memo{Team1Results.size(), Team2Results.size()};

      return HockeyCommonSubsequenceImpl(Team1Results, Team2Results, Team1Results.size() - 1, Team2Results.size() - 1,
                                         Memo);
   }
}
