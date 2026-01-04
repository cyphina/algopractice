#include <iostream>
#include <utility>
#include <vector>

// Given an integer array nums and integers k and M,
// count the number of contiguous subarrays whose sum equals k and whose maximum element is at most M.
// Note our length can fit in an integer - capped at 10^9
// But the sum k is capped at 10^16 and M is capped at 10^9.

// Trick is to handle the constraints separately.
// Segment out the vector, then try to find the subarrays that have sums equal to k using prefix sums to lookup ranges faster.
// But instead of just iterating through every start end index combo to test out subarrays you use the trick in the balanced subarray problem
// genrealized to summing up to `k`. That is:
// If two positions have running totals that differ by k, then everything between them adds up to k.

// This variant passed
//long countSubarraysWithSumAndMaxAtMost(std::vector<int> nums, long k, long M)
//{
//   std::vector<std::size_t> PartitionIndices;
//
//   std::size_t StartOffset{};
//   std::size_t EndOffset{};
//   std::size_t SubarrayEqualKCount{};
//
//   bool                                             bInValidRange{false};
//   std::vector<std::pair<std::size_t, std::size_t>> ValidRanges;
//
//   for(std::size_t i{0}; i < nums.size(); ++i)
//   {
//      if(!bInValidRange)
//      {
//         if(nums[i] <= M)
//         {
//            StartOffset   = i;
//            bInValidRange = true;
//         }
//      }
//      else
//      {
//         if(nums[i] > M)
//         {
//            EndOffset = i;
//            ValidRanges.emplace_back(StartOffset, EndOffset);
//            bInValidRange = false;
//         }
//      }
//   }
//
//   if(bInValidRange)
//   {
//      EndOffset = nums.size();
//      ValidRanges.emplace_back(StartOffset, EndOffset);
//   }
//
//   std::vector<std::vector<long>> PrefixSums(ValidRanges.size());
//
//   std::size_t ValidRangeIndex{};
//   for(const auto& ValidRange : ValidRanges)
//   {
//      auto& PrefixSum{PrefixSums[ValidRangeIndex]};
//      PrefixSum.resize(ValidRange.second - ValidRange.first);
//
//      long Sum{0};
//      for(std::size_t Start{ValidRange.first}; Start < ValidRange.second; ++Start)
//      {
//         Sum += nums[Start];
//         PrefixSum[Start - ValidRange.first] = Sum;
//      }
//
//      ++ValidRangeIndex;
//   }
//
//   for(const auto& PrefixSum : PrefixSums)
//   {
//      for(std::size_t StartIndex{0}; StartIndex < PrefixSum.size(); ++StartIndex)
//      {
//         for(std::size_t EndIndex{StartIndex}; EndIndex < PrefixSum.size(); ++EndIndex)
//         {
//            if(StartIndex == 0)
//            {
//               if(PrefixSum[EndIndex] == k)
//               {
//                  ++SubarrayEqualKCount;
//               }
//            }
//            else
//            {
//               if(PrefixSum[EndIndex] - PrefixSum[StartIndex - 1] == k)
//               {
//                  ++SubarrayEqualKCount;
//               }
//            }
//         }
//      }
//   }
//
//   return SubarrayEqualKCount;
//}

long countSubarraysWithSumAndMaxAtMost(std::vector<int> nums, long k, long M)
{
   std::vector<std::size_t> PartitionIndices;

   std::size_t StartOffset{};
   std::size_t EndOffset{};
   std::size_t SubarrayEqualKCount{};

   bool                                             bInValidRange{false};
   std::vector<std::pair<std::size_t, std::size_t>> ValidRanges;

   for(std::size_t i{0}; i < nums.size(); ++i)
   {
      if(!bInValidRange)
      {
         if(nums[i] <= M)
         {
            StartOffset   = i;
            bInValidRange = true;
         }
      }
      else
      {
         if(nums[i] > M)
         {
            EndOffset = i;
            ValidRanges.emplace_back(StartOffset, EndOffset);
            bInValidRange = false;
         }
      }
   }

   if(bInValidRange)
   {
      EndOffset = nums.size();
      ValidRanges.emplace_back(StartOffset, EndOffset);
   }

   std::vector<std::vector<long>> PrefixSums(ValidRanges.size());

   std::size_t ValidRangeIndex{};
   for(const auto& ValidRange : ValidRanges)
   {
      auto& PrefixSum{PrefixSums[ValidRangeIndex]};
      PrefixSum.resize(ValidRange.second - ValidRange.first);

      long Sum{0};
      for(std::size_t Start{ValidRange.first}; Start < ValidRange.second; ++Start)
      {
         Sum += nums[Start];
         PrefixSum[Start - ValidRange.first] = Sum;
      }

      ++ValidRangeIndex;
   }

   for(const auto& PrefixSum : PrefixSums)
   {
      for(std::size_t StartIndex{0}; StartIndex < PrefixSum.size(); ++StartIndex)
      {
         for(std::size_t EndIndex{StartIndex}; EndIndex < PrefixSum.size(); ++EndIndex)
         {
            if(StartIndex == 0)
            {
               if(PrefixSum[EndIndex] == k)
               {
                  ++SubarrayEqualKCount;
               }
            }
            else
            {
               if(PrefixSum[EndIndex] - PrefixSum[StartIndex - 1] == k)
               {
                  ++SubarrayEqualKCount;
               }
            }
         }
      }
   }

   return SubarrayEqualKCount;
}

int main()
{
   std::cout << countSubarraysWithSumAndMaxAtMost({7, 9, 3, 2, 10, 6, 3, 6}, 5, 5) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({}, 5, 5) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({2}, 5, 5) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({5}, 5, 5) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({5, 2}, 2, 4) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({5, 5}, 5, 5) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({2, -1, 2, 1, -2, 3}, 3, 2) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({2, -1, 2, 3, 1, -2, 2, 1, 1, 3}, 3, 2) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({2, -1, 2}, 2, 2) << std::endl;
   std::cout << countSubarraysWithSumAndMaxAtMost({1, -1, 1, -1}, 0, 2) << std::endl;

   return 0;
}
