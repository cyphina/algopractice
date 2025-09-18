#include "oneoffspellcheck.h"
#include <optional>
#include <string_view>
#include "core/DebugUtils.h"

std::optional<std::pair<int, int>> OneOffSpellCheck::IsStringOneOff(std::string_view FirstString, std::string_view SecondString)
{
   if(ensure(FirstString.size() == SecondString.size() - 1))
   {
      // Longest matching substring from the start and longest matching substring from the end. Both half open ranges.
      int PrefixRangeEnd{-1}, SuffixRangeStart{-1};

      for(int i = 0; i < FirstString.size(); ++i)
      {
         if(FirstString[i] != SecondString[i])
         {
            PrefixRangeEnd = i;
            break;
         }
      }

      // End didn't match. Can't early out have to do lookbehinds too to get a range.
      if(PrefixRangeEnd == -1)
      {
         PrefixRangeEnd = FirstString.size();
      }

      // There's no special way to express a half open range backwards. Just have to still use [start, end)
      // Just try to write this with a simple loop going backwards, insteaod of i = 0, i < 4; ++i you do i = 3; i >= 0; --i
      // Annoying but you have to do the -1 cause half open ranges only prevent off by 1 errors in the forward direction...
      for(int i = SecondString.size() - 1; i > 0; --i)
      {
         if(FirstString[i - 1] != SecondString[i])
         {
            SuffixRangeStart = i;
            break;
         }
      }

      // Beginning didn't match. Need to do lookaheads to get a range.
      if(SuffixRangeStart == -1)
      {
         SuffixRangeStart = 0;
      }

      // aaaba
      // aaba
      // Prefix Match [0,3) - Prefix range end is 2, so [0,3) is where deletable indices lie since divergence is at 2.
      // Suffix Match [1,5) - Suffix range start is 0 so [0,5) is where deletable indices lie since the divergence is at 0.

      if(SuffixRangeStart <= PrefixRangeEnd)
      {
         return std::pair{SuffixRangeStart, PrefixRangeEnd + 1};
      }
      else
      {
         return {};
      }
   }

   return {};
}
