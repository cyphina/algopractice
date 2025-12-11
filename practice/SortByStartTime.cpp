#include <algorithm>
#include <format>
#include <iostream>
#include <utility>
#include <vector>

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

int main()
{
   std::vector<std::pair<int, int>> EmptyTimestamps{};
   std::vector<std::pair<int, int>> SingleTimestamp{{2, 10}};
   std::vector<std::pair<int, int>> Timestamps{{1, 3}, {2, 6}, {8, 10}, {9, 12}};

   const auto EmptyResult{ConsolidateUserTimestamps(EmptyTimestamps)};
   const auto SingleResult{ConsolidateUserTimestamps(SingleTimestamp)};
   const auto Result{ConsolidateUserTimestamps(Timestamps)};

   for(const auto Elem : EmptyResult)
   {
      std::cout << std::format("{} {}\n", Elem.first, Elem.second);
   }

   for(const auto Elem : SingleResult)
   {
      std::cout << std::format("{} {}\n", Elem.first, Elem.second);
   }

   for(const auto Elem : Result)
   {
      std::cout << std::format("{} {}\n", Elem.first, Elem.second);
   }
}
