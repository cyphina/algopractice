#include <algorithm>
#include <iostream>
#include <vector>

/**
 * Triangle is a[i] + a[j] > a[k], a[i] + a[k] > a[j], and a[j] + a[k] > a[i].
 * When sorted this boils down to is a[k] < a[i] + a[j] since a[k] is the largest value.
 * Since we know a[k]>a[j]>a[i] we know that a[i]+a[k] > a[j] and a[j]+a[k] > a[i].
 * Also since we're just trying to find the existance of a triangle we can so a single pass iteration.
 * Else we would have to test combinations since you could jump around with k and another triangle but it's guaranteed the unjumped versions
 * which we're searching through exist if the jump versions exists which will help us test existence.
 */
bool HasTriangle(std::vector<uint32_t>& A)
{
   if(A.size() < 3)
   {
      return false;
   }

   std::ranges::sort(A);

   size_t LeftIndex{0};
   size_t RightIndex{2};

   for(; RightIndex < A.size(); ++RightIndex, ++LeftIndex)
   {
      if(A[LeftIndex] + A[LeftIndex + 1] > A[RightIndex])
      {
         return true;
      }
   }

   return false;
}

int main()
{
   std::vector<uint32_t> Empty{};
   std::vector<uint32_t> Single{1};
   std::vector<uint32_t> Data{1, 2, 5, 8, 10, 12};
   std::vector<uint32_t> Data2{10, 20, 40, 80, 160};
   std::vector<uint32_t> Data3(6);
   std::ranges::transform(Data, Data3.begin(),
                          [](const auto& Elem)
                          {
                             return Elem * Elem;
                          });

   std::cout << HasTriangle(Empty) << "\n";
   std::cout << HasTriangle(Single) << "\n";
   std::cout << HasTriangle(Data) << "\n";
   std::cout << HasTriangle(Data2) << "\n";
   std::cout << HasTriangle(Data3) << "\n";
}
