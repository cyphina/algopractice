#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int solution(std::vector<int>& A)
{
   std::ranges::sort(A);
   int CurrentSmallestPositiveInteger{1};

   if(A.back() <= 0)
   {
      return 1;
   }

   for(const auto& Elem : A)
   {
      if(Elem == CurrentSmallestPositiveInteger)
      {
         ++CurrentSmallestPositiveInteger;
      }
      else if(Elem > CurrentSmallestPositiveInteger)
      {
         return CurrentSmallestPositiveInteger;
      }
   }

   return CurrentSmallestPositiveInteger;
}

int main()
{
   std::vector<int> Example1{-1, -2};
   std::vector<int> Example2{-5, -10, 0};
   std::vector<int> Example3{3, 2, 1};
   std::vector<int> Example4{1, 3, 6, 4, 1, 2};
   constexpr auto   Numbers{std::views::iota(-10000, 10000)};
   std::vector<int> LargeExample{Numbers.begin(), Numbers.end()};
   std::vector<int> Example5{-5, -21, 20, 13, 1, -88, 23, 2, 59};

   std::cout << solution(Example1) << "\n";
   std::cout << solution(Example2) << "\n";
   std::cout << solution(Example3) << "\n";
   std::cout << solution(Example4) << "\n";
   std::cout << solution(LargeExample) << "\n";
   std::cout << solution(Example5) << "\n";
}
