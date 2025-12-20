#pragma once

#include <vector>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

namespace DivideAndConquer
{
   /**
    * To remember how this works you need to map this to the idea of a feasibility partitioning binary search problem where the feasibility condition is A[i] <= V.
    */
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

      // At each step we have an invariant.
      // Finding the optimal value involves a costly scan through the array without binary search.
      // Optimality is hard to find but feasibility (check whether A[i] <= V) is
      // easy to check (it's technically std::lower_bound aka find first element not less than V).
      // By nature of the array being sorted we have feasible and infeasible solutions partitioned.

      // lo is part of the feasible. hi should always be part of the unfeasible.
      // Don't even think about indices just keep this rule in mind, and remember the condition is when the boundaries touch.
      while(lo + 1 < hi)
      {
         int mid = (lo + hi) / 2; // integral division will already floor.
         // For each of these we already checked mid in the else case so we can adjust the index by 1.
         // Also if we don't do this we can get restuck just setting it to mid for cases where mid is the same value.
         // We see this mostly in small subarrays where mid either equals low or hi, and then we set low or hi to mid which keeps it the same..

         // feasible so now lo is it (notice weuse less than or equal to cause this means we're part of the feasible)
         if(A[mid] <= V)
         {
            lo = mid;
         }
         // no feasible so hi is it
         else if(A[mid] > V)
         {
            hi = mid;
         }
      }

      if(A[lo] == V)
      {
         return lo;
      }

      return -1;
   }
}
