#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

int MaximumSumNonAdjacentElementsImpl(std::vector<int>& A, int EndIndex, std::vector<std::optional<int>>& Memo)
{
   if(EndIndex == 0)
   {
      return 0;
   }
   else if(EndIndex == 1)
   {
      return A[0];
   }

   if(Memo[EndIndex].has_value())
   {
      return Memo[EndIndex].value();
   }

   int MaximumSum{std::max(MaximumSumNonAdjacentElementsImpl(A, EndIndex - 1, Memo),
                           MaximumSumNonAdjacentElementsImpl(A, EndIndex - 2, Memo) + A[EndIndex - 1])};
   Memo[EndIndex] = MaximumSum;

   return MaximumSum;
}

int MaximumSumNonAdjacentElements(std::vector<int>& A)
{
   std::vector<std::optional<int>> Memo(A.size() + 1);
   return MaximumSumNonAdjacentElementsImpl(A, A.size(), Memo);
}

int main()
{
   std::vector<int> EmptyExample;
   std::vector<int> SingleExample{5};
   std::vector<int> DoubleExample{6, 3};
   std::vector<int> TripleExample{3, 6, 5};

   std::vector<int> Example1{2, 6, 8, 7, 10, 3, 11, 9, 1};
   std::vector<int> Example2{20, 6, 8, 27, 10, 3, 11, 9, 1};
   const auto       Example3Items{std::views::iota(0, 100)};
   std::vector<int> Example3{Example3Items.begin(), Example3Items.end()};

   std::cout << MaximumSumNonAdjacentElements(EmptyExample) << "\n";
   std::cout << MaximumSumNonAdjacentElements(SingleExample) << "\n";
   std::cout << MaximumSumNonAdjacentElements(DoubleExample) << "\n";
   std::cout << MaximumSumNonAdjacentElements(TripleExample) << "\n";
   std::cout << MaximumSumNonAdjacentElements(Example1) << "\n";
   std::cout << MaximumSumNonAdjacentElements(Example2) << "\n";
   std::cout << MaximumSumNonAdjacentElements(Example3) << "\n";
}
