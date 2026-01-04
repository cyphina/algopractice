#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

// For this problem you have lowercase letters and you need to find the maximum length of a substring with all distinct letters.
// The twist is for this problem * means you should split the string processing between those between *. And then you return the max amongst
// processing all strings individually.

// The string size varies from 0 to 100000.
// For input of `*` just return 0

// The trick is to use a sliding window and optimally try to track when you hit the characters last in a map to prevent having to
// search over the string over and over. Like most sliding window problems you have to recognize increasing the right side adds pressure
// and removing elements on the left undoes it.

int maxDistinctSubstringLengthInSessions(std::string sessionString)
{
   std::size_t                           LongestSubstringUniqueCharsLength{};
   std::size_t                           CurrentSlidingWindowLength{};
   std::unordered_map<char, std::size_t> CharToLastSeenIndex;

   for(std::size_t CharIndex{0}; CharIndex < sessionString.size(); ++CharIndex)
   {
      const auto& CurrentChar{sessionString[CharIndex]};

      if(CurrentChar == '*')
      {
         CurrentSlidingWindowLength = 0;
         CharToLastSeenIndex.clear();
         continue;
      }

      if(const auto CurrentCharLastSeenIndex{CharToLastSeenIndex.find(sessionString[CharIndex])};
         CurrentCharLastSeenIndex == CharToLastSeenIndex.end())
      {
         ++CurrentSlidingWindowLength;
         LongestSubstringUniqueCharsLength = std::max(CurrentSlidingWindowLength, LongestSubstringUniqueCharsLength);
      }
      else
      {
         if(CharIndex - (CurrentSlidingWindowLength) <= CurrentCharLastSeenIndex->second)
         {
            CurrentSlidingWindowLength = CharIndex - CurrentCharLastSeenIndex->second;
         }
         else
         {
            ++CurrentSlidingWindowLength;
            LongestSubstringUniqueCharsLength = std::max(CurrentSlidingWindowLength, LongestSubstringUniqueCharsLength);
         }
      }

      CharToLastSeenIndex.insert_or_assign(sessionString[CharIndex], CharIndex);
   }

   return static_cast<int>(LongestSubstringUniqueCharsLength);
}

int main()
{
   std::cout << maxDistinctSubstringLengthInSessions("a") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("*") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("abcabcabc") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("abcda") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("abcdb") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("abcdaddxabcdefgh") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("abcdadadabcxdefgh") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("dddd") << "\n";
   std::cout << maxDistinctSubstringLengthInSessions("dddd*abcd*xyzlmnop") << "\n";
}
