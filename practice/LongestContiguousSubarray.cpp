#include <iostream>
#include <utility>
#include <vector>

size_t SizeLengthLongestContiguousSubarraySumUnderK(std::vector<int> A, int K)
{
   if(A.empty())
   {
      return 0;
   }

   size_t LeftIndex{}, RightIndex{};
   size_t MaxLength{};
   size_t CurrentSum{};

   for(; RightIndex < A.size(); ++RightIndex)
   {
      CurrentSum += static_cast<size_t>(A[RightIndex]);
      while(std::cmp_greater(CurrentSum, K))
      {
         CurrentSum -= A[LeftIndex];
         ++LeftIndex;
      }

      // Prune than update since we're finding the longest only if our condition is valid.
      MaxLength = std::max(MaxLength, RightIndex - LeftIndex + 1);
   }

   return MaxLength;
}

int main()
{
   std::vector<int> Empty{};
   std::vector<int> Single{5};
   std::vector<int> Data{2, 4, 1, 3, 8, 5, 1, 2, 3};
   std::vector<int> Data2{20, 40, 10, 30, 80, 50, 10, 20, 20};
   std::vector<int> Data3{2, 1, 1, 1, 1};

   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Empty, 9) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Single, 4) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Single, 10) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Data, 9) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Data, 20) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Data, 0) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Data2, 5) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Data2, 50) << "\n";
   std::cout << SizeLengthLongestContiguousSubarraySumUnderK(Data3, 3) << "\n";
}
