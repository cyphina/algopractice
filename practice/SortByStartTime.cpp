#include <algorithm>
#include <format>
#include <iostream>
#include <utility>
#include <vector>

// Aka the Merge and Sort Intervals Problem
// Key is to sort by start time and then start collecting intervals

std::vector<std::pair<int, int>> ConsolidateUserTimestamps(std::vector<std::pair<int, int>>& Timestamps)
{
   std::ranges::sort(Timestamps,
                     [](const auto& A, const auto& B)
                     {
                        return A.first < B.first;
                     });

   if(Timestamps.empty())
   {
      return {};
   }

   std::vector<std::pair<int, int>> ConsolidatedTimestamps;
   ConsolidatedTimestamps.emplace_back(Timestamps[0]);

   for(size_t i{1}; i < Timestamps.size(); ++i)
   {
      auto&       LastTimestamp{ConsolidatedTimestamps.back()};
      const auto& CurrentTimestamp{Timestamps[i]};
      if(LastTimestamp.second >= CurrentTimestamp.first)
      {
         LastTimestamp.second = CurrentTimestamp.second;
      }
      else
      {
         ConsolidatedTimestamps.emplace_back(CurrentTimestamp);
      }
   }

   return ConsolidatedTimestamps;
}

// How I did in Hackerrank
std::vector<std::vector<int>> mergeHighDefinitionIntervals(std::vector<std::vector<int>> intervals)
{
   if(intervals.empty())
   {
      return {};
   }

   std::sort(intervals.begin(), intervals.end(),
             [](const std::vector<int>& PairA, const std::vector<int>& PairB)
             {
                return PairA[0] < PairB[0];
             });

   std::vector<std::vector<int>> Result;
   std::vector<int>              CurrentInterval{intervals[0]};

   for(std::size_t i{1}; i < intervals.size(); ++i)
   {
      if(intervals[i][0] <= CurrentInterval[1])
      {
         CurrentInterval[1] = std::max(intervals[i][1], CurrentInterval[1]);
      }
      else
      {
         Result.emplace_back(CurrentInterval);
         CurrentInterval = intervals[i];
      }
   }

   Result.emplace_back(CurrentInterval);

   return Result;
}

int main()
{
   std::vector<std::pair<int, int>> EmptyTimestamps{};
   std::vector<std::pair<int, int>> SingleTimestamp{{2, 10}};
   std::vector<std::pair<int, int>> Timestamps{{1, 3}, {2, 6}, {8, 10}, {9, 12}, {20, 24}};

   const auto EmptyResult{ConsolidateUserTimestamps(EmptyTimestamps)};
   const auto SingleResult{ConsolidateUserTimestamps(SingleTimestamp)};
   const auto Result{ConsolidateUserTimestamps(Timestamps)};

   for(const auto Elem : EmptyResult)
   {
      std::cout << std::format("{} {}\n", Elem.first, Elem.second);
   }

   std::cout << "\n";

   for(const auto Elem : SingleResult)
   {
      std::cout << std::format("{} {}\n", Elem.first, Elem.second);
   }

   std::cout << "\n";

   for(const auto Elem : Result)
   {
      std::cout << std::format("{} {}\n", Elem.first, Elem.second);
   }
}
