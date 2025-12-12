#include <iostream>
#include <optional>
#include <string>
#include <vector>

//Return the length of their longest common subsequence.
//
//A subsequence means characters appear in the same order,
//but not necessarily contiguously.

// seaweed
// daedee
// see
// sea

int longestCommonSubsequenceImpl(const std::string& s1, const std::string& s2, const size_t s1End, const size_t s2End,
                                 std::vector<std::vector<std::optional<int>>>& Memo)
{
   if(s1End == 0 || s2End == 0)
   {
      return 0;
   }

   if(const auto CachedValue{Memo[s1End][s2End]})
   {
      return CachedValue.value();
   }

   const auto LongestCommonSeq1 = longestCommonSubsequenceImpl(s1, s2, s1End, s2End - 1, Memo);
   const auto LongestCommonSeq2 = longestCommonSubsequenceImpl(s1, s2, s1End - 1, s2End, Memo);

   int LCSLength;
   if(s1[s1End - 1] == s2[s2End - 1])
   {
      LCSLength = 1 + longestCommonSubsequenceImpl(s1, s2, s1End - 1, s2End - 1, Memo);
   }
   else
   {
      LCSLength = std::max(LongestCommonSeq1, LongestCommonSeq2);
   }

   Memo[s1End][s2End] = LCSLength;

   return LCSLength;
}

int longestCommonSubsequence(const std::string& s1, const std::string& s2)
{
   std::vector Memo(s1.size() + 1, std::vector<std::optional<int>>(s2.size() + 1));
   return longestCommonSubsequenceImpl(s1, s2, s1.size(), s2.size(), Memo);
}

int main()
{
   std::cout << longestCommonSubsequence("seaweed", "seed") << "\n";
   std::cout << longestCommonSubsequence("sad", "asd") << "\n";
   std::cout << longestCommonSubsequence("a", "a") << "\n";
}
