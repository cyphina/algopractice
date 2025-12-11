#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

size_t CountUniquePairs(std::vector<int>& A, int K)
{
   if(A.size() < 2)
   {
      return 0;
   }

   std::ranges::sort(A);

   size_t LeftIndex{0};
   size_t RightIndex{A.size() - 1};

   size_t UniquePairCount{};
   int    Right{A[RightIndex]};

   // Can't early out with std::cmp_less(A[LeftIndex], K) since that screws up our negative values like we could add negatives and get something less even if left is larger than K.
   for(; LeftIndex < RightIndex; ++LeftIndex)
   {
      const int Left{A[LeftIndex]};

      while(Left + Right > K && LeftIndex != RightIndex)
      {
         --RightIndex;
         Right = A[RightIndex];
      }

      UniquePairCount += RightIndex - LeftIndex;
   }

   return UniquePairCount;
}

int main()
{
   std::vector<int> Data{2, 3, 14, 22, 35, 39, 49};
   std::vector<int> Empty{};
   std::vector<int> Single{5};
   std::vector<int> NegData(Data.size());

   std::ranges::transform(Data, NegData.begin(),
                          [](int Elem)
                          {
                             return -Elem;
                          });

   std::cout << CountUniquePairs(Data, 25) << "\n";
   std::cout << CountUniquePairs(Data, 50) << "\n";
   std::cout << CountUniquePairs(Data, 100) << "\n";
   std::cout << CountUniquePairs(Data, 0) << "\n";
   std::cout << CountUniquePairs(NegData, -25) << "\n";
   std::cout << CountUniquePairs(Empty, 25) << "\n";
   std::cout << CountUniquePairs(Single, 4) << "\n";
}
