#pragma once
#include <vector>

namespace Sorting
{
   void BubbleSort(std::vector<int>& A)
   {
      if(A.size() <= 1)
      {
         return;
      }

      for(size_t i = 0; i < A.size(); ++i)
      {
         // Half open so A.size() - 1
         bool didSwap = false;

         for(size_t j = A.size() - 1; j >= 1; --j)
         {
            if(A[j] < A[j - 1])
            {
               const int temp = A[j - 1];
               A[j - 1]       = A[j];
               A[j]           = temp;
               didSwap        = true;
            }
         }

         if(!didSwap)
         {
            return;
         }
      }
   }
}