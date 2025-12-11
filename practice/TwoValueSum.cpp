
#include <algorithm>
#include <format>
#include <iostream>
#include <vector>

namespace
{
   bool DoesPairSumExist(std::vector<int>& A, int TargetSum)
   {
      if(A.size() <= 1)
      {
         return false;
      }

      if(!std::ranges::is_sorted(A))
      {
         std::ranges::sort(A);
      }

      size_t StartIndex{}, EndIndex{A.size() - 1};

      for(size_t i{0}; i < A.size(); ++i)
      {
         int TestSum{A[StartIndex] + A[EndIndex]};
         if(TestSum < TargetSum)
         {
            ++StartIndex;
         }
         else if(TestSum > TargetSum)
         {
            --EndIndex;
         }
         else
         {
            return true;
         }

         if(StartIndex == EndIndex)
         {
            return false;
         }
      }

      return false;
   }

}

int main()
{
   std::vector<int> Data{2, 3, 14, 22, 35, 39, 49};
   const auto       Result{DoesPairSumExist(Data, 25)};
   const auto       Result2{DoesPairSumExist(Data, 30)};
   const auto       Result3{DoesPairSumExist(Data, 17)};
   std::cout << std::format("Result: {}\n", Result);
   std::cout << std::format("Result2: {}\n", Result2);
   std::cout << std::format("Result3: {}\n", Result3);
}
