#include "DebugUtils.h"
#include <algorithm>
#include <string>
#include <vector>

// This was my first attempt of coming up with a solution.
// Doesn't work since we in theory would get a number of brackets equal to the Catalan numbers.
// For n=4 and beyond we start to miss stuff
// since you can have things like <<>><<>> which can't be built from previous elements just using this rule.

//std::vector<std::string> generateAngleBracketSequenceImpl(int n)
//{
//   if(n == 1)
//   {
//      return {"<>"};
//   }
//
//   std::vector<std::string> Result;
//   std::vector<std::string> PrevResults{generateAngleBracketSequenceImpl(n - 1)};
//   for(const auto& PrevResult : PrevResults)
//   {
//      Result.emplace_back("<" + PrevResult + ">");
//      Result.emplace_back("<>" + PrevResult);
//      Result.emplace_back(PrevResult + "<>");
//   }
//
//   return Result;
//}

// The trick is pretty weird. We think of recursion as solving subproblems but here it's to explore a state space.
// The base case is we've reached a valid end state instead of the smallest subproblem.
// You also need to use this string and as you explore build up your result and as you backtrack you take away from it a bit.

void generateAngleBracketSequenceImpl(int LeftBracketCount, int RightBracketCount, std::string& CurrentString,
                                      std::vector<std::string>& Results, int n)
{
   if(LeftBracketCount == n && RightBracketCount == n)
   {
      Results.push_back(CurrentString);
      return;
   }

   if(LeftBracketCount < n)
   {
      CurrentString.push_back('<');
      generateAngleBracketSequenceImpl(LeftBracketCount + 1, RightBracketCount, CurrentString, Results, n);
      CurrentString.pop_back();
   }

   if(RightBracketCount < LeftBracketCount)
   {
      CurrentString.push_back('>');
      generateAngleBracketSequenceImpl(LeftBracketCount, RightBracketCount + 1, CurrentString, Results, n);
      CurrentString.pop_back();
   }
}

std::vector<std::string> generateAngleBracketSequences(int n)
{
   std::string              CurrentString;
   std::vector<std::string> Results;
   generateAngleBracketSequenceImpl(0, 0, CurrentString, Results, n);

   return Results;
}

int main()
{
   const auto Results{generateAngleBracketSequences(5)};

   DebugUtils::PrintRange(Results);
}
