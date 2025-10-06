#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "memoization/LongestCommonSubsequence.h"

TEST_CASE("Test Longest Common Subsequence", "[lcs]")
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
   REQUIRE(Result.MaxRivalGamePoints == 20);

   std::vector<HockeyGameResultData> Team1GameResults2{
       {.Result = HockeyGameResult::Win, .PointsScored = 8}, {HockeyGameResult::Win, 5}, {HockeyGameResult::Win, 7}};
   std::vector<HockeyGameResultData> Team2GameResults2{
       {.Result = HockeyGameResult::Win, .PointsScored = 5}, {HockeyGameResult::Win, 3}, {HockeyGameResult::Win, 4}};
   const auto Result2{HockeyCommonSubsequence(Team1GameResults2, Team2GameResults2)};
   REQUIRE(Result2.MaxRivalGamePoints == 0);

   std::vector<HockeyGameResultData> Team1GameResults3{
       {.Result = HockeyGameResult::Win, .PointsScored = 8}, {HockeyGameResult::Win, 15}, {HockeyGameResult::Win, 11}};
   std::vector<HockeyGameResultData> Team2GameResults3{
       {.Result = HockeyGameResult::Loss, .PointsScored = 5}, {HockeyGameResult::Loss, 7}, {HockeyGameResult::Loss, 8}};
   const auto Result3{HockeyCommonSubsequence(Team1GameResults3, Team2GameResults3)};
   REQUIRE(Result3.MaxRivalGamePoints == 54);
}
