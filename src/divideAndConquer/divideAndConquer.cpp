#include "DivideAndConquer.h"

namespace DivideAndConquer
{
   SubarrayResult Crossing(const std::vector<int>& A, int Low, int Mid, int High)
   {
      int LeftSideMax      = std::numeric_limits<int>::min();
      int LeftSideMaxIndex = Mid - 1;
      int LeftSideSum      = 0;

      for(int i = Mid - 1; i >= Low; --i)
      {
         LeftSideSum += A[i];
         if(LeftSideSum > LeftSideMax)
         {
            LeftSideMax      = LeftSideSum;
            LeftSideMaxIndex = i;
         }
      }

      int RightSideMax      = std::numeric_limits<int>::min();
      int RightSideMaxIndex = Mid - 1;
      int RightSideSum      = 0;

      for(int i = Mid; i < High; ++i)
      {
         RightSideSum += A[i];
         if(RightSideSum > RightSideMax)
         {
            RightSideMax      = RightSideSum;
            RightSideMaxIndex = i;
         }
      }

      return {LeftSideMaxIndex, RightSideMaxIndex, LeftSideMax + RightSideMax};
   }

   SubarrayResult FindMaximumSubarray(const std::vector<int>& A, int Low, int High)
   {
      if(Low >= High - 1)
      {
         if(A[Low] < 0)
         {
            return {};
         }
         else
         {
            return {Low, High - 1, A[Low]};
         }
      }

      const int Mid = (Low + High) / 2;

      const auto LowResult      = FindMaximumSubarray(A, Low, Mid);
      const auto HighResult     = FindMaximumSubarray(A, Mid, High);
      const auto CrossingResult = Crossing(A, Low, Mid, High);

      // Left biased results
      if(LowResult.max >= CrossingResult.max)
      {
         if(LowResult.max >= HighResult.max)
         {
            return LowResult;
         }
         else
         {
            return HighResult;
         }
      }
      else if(CrossingResult.max >= HighResult.max)
      {
         return CrossingResult;
      }
      else
      {
         return HighResult;
      }
   }

   SubarrayResult FindMaximumSubarray(const std::vector<int>& A)
   {
      if(A.empty())
      {
         return {};
      }

      return FindMaximumSubarray(A, 0, A.size());
   }

   SubarrayResult FindMaximumSubarrayKadane(const std::vector<int>& A)
   {
      if(A.size() == 0)
      {
         return {};
      }

      int            currentSum = 0;
      SubarrayResult bestResult;
      SubarrayResult curentResult;

      for(int i = 0; i < A.size(); ++i)
      {
         if(currentSum < 0)
         {
            currentSum   = 0;
            curentResult = {.low = i, .high = i, .max = 0};
         }

         currentSum += A[i];

         if(currentSum > bestResult.max)
         {
            bestResult.low = curentResult.low;
            bestResult.high = i;
            bestResult.max = currentSum;
         }
      }

      return bestResult;
   }
}
