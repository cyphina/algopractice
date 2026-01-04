#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Find the smallest missing positive integers in O(n) with O(1) space
// Only works since our input is capped to an array of size 1000 and our numbers can be from -10^9 to 10^9 which is stll in int range.
// Trick is to swap elements to their rightful place in the vector, then iterate through it.
// Another trick is that when we swap elements to their place, we also swap some elements forwards back and need to avoid skipping the ones we swap backwards.
// Thus we need to make sure this swap process does not occur indefinately b/c if we swap the same element back we'd keep going.

int findSmallestMissingPositive(std::vector<int> orderNumbers)
{
   for(std::size_t i{0}; i < orderNumbers.size(); ++i)
   {
      if(std::cmp_not_equal(orderNumbers[i], i + 1))
      {
         while(orderNumbers[i] > 0 && orderNumbers[i] < static_cast<int>(orderNumbers.size()) &&
               orderNumbers[i] != static_cast<int>(i + 1) && orderNumbers[orderNumbers[i] - 1] != orderNumbers[i])
         {
            std::swap(orderNumbers[orderNumbers[i] - 1], orderNumbers[i]);
         }
      }
   }

   int SmallestMissingPositive{1};
   for(std::size_t i{0}; i < orderNumbers.size(); ++i)
   {
      if(orderNumbers[i] != SmallestMissingPositive)
      {
         break;
      }
      ++SmallestMissingPositive;
   }

   return SmallestMissingPositive;
}

int main()
{
   std::cout << findSmallestMissingPositive({}) << "\n";
   std::cout << findSmallestMissingPositive({3, 2, 1}) << "\n";
   std::cout << findSmallestMissingPositive({-1, 322, 2, 93920, 1, 353, 2, 3, -3, -4, 5, 4}) << "\n";
}
