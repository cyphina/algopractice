#pragma once
#include <vector>

namespace DivideAndConquer
{
   struct SubarrayResult
   {
      int low  = 0;
      int high = 0;
      int max  = 0;
   };

   /**
    * For an empty array reurns low=high
    * Technically can return a negative max in some implementations.
    */
   SubarrayResult FindMaximumSubarray(const std::vector<int>& A);

   /**
    * Linear time approach
    */
   SubarrayResult FindMaximumSubarrayKadane(const std::vector<int>& A);

}