#include <iostream>
#include <optional>
#include <vector>

// Given n (0-based indexing), return the n-th Fibonacci number where F(0) = 1, F(1) = 2, and F(n) = F(n-1) + F(n-2).
// Trick is to use caching and make sure to use large enough data types cause we expect to handle up to N=92.

long long Fibonacci(int N, std::vector<std::optional<long long>>& Cache)
{
   if(N == 0)
   {
      return 1;
   }
   else if(N == 1)
   {
      return 2;
   }
   else
   {
      if(Cache[N].has_value())
      {
         return Cache[N].value();
      }
      else
      {
         const auto Result{Fibonacci(N - 1, Cache) + Fibonacci(N - 2, Cache)};
         Cache[N] = Result;
         return Result;
      }
   }
}

long long getAutoSaveInterval(int n)
{
   std::vector<std::optional<long long>> Cache(n + 1);

   return Fibonacci(n, Cache);
}

int main()
{
   std::cout << getAutoSaveInterval(0) << "\n";
   std::cout << getAutoSaveInterval(1) << "\n";
   std::cout << getAutoSaveInterval(2) << "\n";
   std::cout << getAutoSaveInterval(4) << "\n";
   std::cout << getAutoSaveInterval(20) << "\n";
   std::cout << getAutoSaveInterval(50) << "\n";
   std::cout << getAutoSaveInterval(92) << "\n";
}
