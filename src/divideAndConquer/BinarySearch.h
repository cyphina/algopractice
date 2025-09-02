#pragma once

#include <vector>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

namespace DivideAndConquer
{
   template <typename T>
      requires Arithmetic<T>
   int BinarySearch(const std::vector<T>& A, T V)
   {
      if(A.empty())
      {
         return -1;
      }

      int lo = 0;
      int hi = A.size();

      // Last == in <= is narrowed down to the final target. We need it or the only way we'd work is if our narrowing of lo and high had somehow led us to a mid with a matching value.
      // The < is the real stopping condition. We get there after processing the final target.
      while(lo < hi)
      {
         int mid = (lo + hi) / 2; // integral division will already floor.
         // For each of these we already checked mid in the else case so we can adjust the index by 1.
         // Also if we don't do this we can get restuck just setting it to mid for cases where mid is the same value.
         // We see this mostly in small subarrays where mid either equals low or hi, and then we set low or hi to mid which keeps it the same...

         if(V > A[mid])
         {
            lo = mid + 1;
         }
         else if(V < A[mid])
         {
            hi = mid;
         }
         else
         {
            return mid;
         }
      }

      return -1;
   }
}