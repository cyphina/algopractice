#include <cstdint>
#include <iostream>
#include <vector>

int SizeMinContiguousSubarraySumGreaterK(std::vector<uint32_t>& A, int K)
{
   static size_t SENTINEL{std::numeric_limits<size_t>::max()};

   size_t LeftIndex{}, RightIndex{};
   size_t CurrentSum{};
   size_t MinLength{SENTINEL};

   for(; RightIndex < A.size(); ++RightIndex)
   {
      CurrentSum += A[RightIndex];

      while(std::cmp_greater_equal(CurrentSum, K))
      {
         // Prune while updating since as we shrink we can get a new min.
         MinLength = std::min(MinLength, RightIndex - LeftIndex + 1);
         CurrentSum -= A[LeftIndex];
         ++LeftIndex;
      }
   }

   if(MinLength == SENTINEL)
   {
      return -1;
   }

   return MinLength;
}

int main()
{
   std::vector<uint32_t> Empty{};
   std::vector           Single{5u};
   std::vector           Data{2u, 3u, 1u, 2u, 4u, 3u};
   std::vector           Data2{5u, 8u, 11u, 3u, 6u, 1u, 2u, 9u};

   std::cout << SizeMinContiguousSubarraySumGreaterK(Empty, 7) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Single, 3) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Single, 6) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Data, 3) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Data, 7) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Data, 14) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Data, 20) << "\n";
   std::cout << SizeMinContiguousSubarraySumGreaterK(Data2, 14) << "\n";
}
