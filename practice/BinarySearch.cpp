#include <vector>

int binarySearch(std::vector<int> nums, int target)
{
   if(nums.empty())
   {
      return -1;
   }

   // Anything at lo or before <= target
   std::size_t lo{0};
   // Anything at hi or after > target
   std::size_t hi{nums.size()};

   // While our invariant is true aka the number after lo cannot be >= hi since then it would be > target so we know
   // at lo is where our target would be
   while(lo + 1 < hi)
   {
      std::size_t mid{(lo + hi) / 2};
      if(nums[mid] <= target)
      {
         lo = mid;
      }
      else
      {
         hi = mid;
      }
   }

   if(nums[lo] == target)
   {
      return static_cast<int>(lo);
   }

   return -1;
}

int main()
{
}
