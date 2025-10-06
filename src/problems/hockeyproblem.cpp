#include <print>
#include <vector>
#include "memoization/LongestCommonSubsequence.h"

int main()
{
   using namespace LongestCommonSubsequence;

   std::vector<HockeyGameResultData> Team1GameResults{{.Result = HockeyGameResult::Win, .PointsScored = 3},
                                                      {HockeyGameResult::Loss, 4},
                                                      {HockeyGameResult::Win, 1},
                                                      {HockeyGameResult::Win, 8}};
   std::vector<HockeyGameResultData> Team2GameResults{{.Result = HockeyGameResult::Win, .PointsScored = 5},
                                                      {HockeyGameResult::Loss, 1},
                                                      {HockeyGameResult::Loss, 2},
                                                      {HockeyGameResult::Loss, 3}};
   const auto                        Result{HockeyCommonSubsequence(Team1GameResults, Team2GameResults)};

   std::println("Hockey Result - {} - {}", Result.MaxRivalGamePoints, Result.GameIndices);
}
