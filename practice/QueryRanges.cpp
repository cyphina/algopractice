#include "DebugUtils.h"
#include <numeric>
#include <utility>
#include <vector>

using RangeIndices = std::pair<int, int>;

std::vector<int> QueryRanges(std::vector<int> A, std::vector<std::pair<int, int>> Queries)
{
   if(A.empty())
   {
      return {};
   }

   std::vector<int> PrefixSums(A.size());
   std::vector<int> Results;
   Results.reserve(Queries.size());

   std::inclusive_scan(A.begin(), A.end(), PrefixSums.begin());

   for(const auto& Query : Queries)
   {
      if(Query.first > 0)
      {
         Results.emplace_back(PrefixSums[Query.second] - PrefixSums[Query.first - 1]);
      }
      else
      {
         Results.emplace_back(PrefixSums[Query.second]);
      }
   }

   return Results;
}

int main()
{
   std::vector<RangeIndices> Empty{};

   std::vector<int> EmptyData{};
   std::vector<int> SingleData{5};

   const std::vector<int>    Data{4, 8, 5, 7, 3, 1, 13, 7};
   std::vector<RangeIndices> Query{{0, 0}, {0, 3}, {2, 4}, {3, 5}, {1, 6}};

   const auto Results{QueryRanges(Data, Query)};
   DebugUtils::PrintRange(Results);

   const auto ResultsEmpty{QueryRanges(EmptyData, {})};
   DebugUtils::PrintRange(ResultsEmpty);

   const auto ResultsSingle{QueryRanges(SingleData, std::vector<RangeIndices>{{0, 0}})};
   DebugUtils::PrintRange(ResultsSingle);
}
