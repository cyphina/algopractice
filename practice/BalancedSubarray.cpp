#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * Longest balanced subarray means number of 0s and 1s are equal.
 * Trick to this problem is to trya bunch of examples and track the last time we hit a prefix sum value twice so we need
 * to record when we last hit it.
 */
std::pair<int, int> FindLongestBalancedSubarray(std::vector<int>& A)
{
   std::ranges::transform(A, A.begin(),
                          [](int Elem)
                          {
                             return Elem == 1 ? Elem : -1;
                          });

   std::vector<int> PrefixSum(A.size());
   std::inclusive_scan(A.begin(), A.end(), PrefixSum.begin());

   std::unordered_map<int, int> PrefixSumValueToEarliestIndex;
   PrefixSumValueToEarliestIndex.emplace(0, 0);

   std::pair<int, int> CurrentLongestSubarrayIndices;

   for(int Index{}; const int& Elem : PrefixSum)
   {
      if(PrefixSumValueToEarliestIndex.contains(Elem))
      {
         const int EarliestIndexForValue{PrefixSumValueToEarliestIndex.at(Elem)};
         if((Index - EarliestIndexForValue) >
            CurrentLongestSubarrayIndices.second - CurrentLongestSubarrayIndices.first)
         {
            CurrentLongestSubarrayIndices = {EarliestIndexForValue, Index};
         }
      }
      else
      {
         PrefixSumValueToEarliestIndex.emplace(Elem, Index + 1);
      }
      ++Index;
   }

   return CurrentLongestSubarrayIndices;
}

int main()
{
   std::vector<int> Empty{};
   std::vector<int> Data{0, 0, 0, 1, 0, 0, 0, 1, 1, 1};
   std::vector<int> Data2{0, 1, 0, 1, 0, 1};

   // [-1, -2, -3, -2, -3, -4, -5, -4, -3, -2]
   const auto Result1{FindLongestBalancedSubarray(Empty)};
   const auto Result2{FindLongestBalancedSubarray(Data)};
   const auto Result3{FindLongestBalancedSubarray(Data2)};

   std::cout << std::format("{} {} \n", Result1.first, Result1.second);
   std::cout << std::format("{} {} \n", Result2.first, Result2.second);
   std::cout << std::format("{} {} \n", Result3.first, Result3.second);
}
