#include <cstddef>
#include <iostream>
#include <string>

// Given two strings of equal size check if s2 is a rotation of s1 but not identical. Else return 0. Guarnateed strings are of length 1 to 1000.

// With this problem you just have to handle rotate left and right. Unlike snowflake you aren't checking identitical iterating left and right.
// Just watch out for parenthesis with the % and make sure to handle the loop like so or make a helper function.

bool isNonTrivialRotation(std::string s1, std::string s2)
{
   if(s1 == s2)
   {
      return false;
   }

   for(std::size_t Start{}; Start < s1.size(); ++Start)
   {
      bool MatchedAll{true};
      for(std::size_t i{}; i < s1.size(); ++i)
      {
         if(s1[(i + Start) % s1.size()] != s2[i])
         {
            MatchedAll = false;
            break;
         }
      }

      if(MatchedAll)
      {
         return true;
      }
   }

   return false;
}

int main()
{
   std::cout << isNonTrivialRotation("abcde", "bcdea") << '\n';
   std::cout << isNonTrivialRotation("abcde", "eabcd") << '\n';
   std::cout << isNonTrivialRotation("abfde", "eabcd") << '\n';
   std::cout << isNonTrivialRotation("a", "a") << '\n';
   std::cout << isNonTrivialRotation("a", "b") << '\n';
}
