#include <iostream>
#include <print>
#include <vector>
#include "misc/foodlines.h"

int main()
{
   std::println("Number of Lines and Number of People");
   int NumLines{0}, NumPeople{0};
   std::cin >> NumLines >> NumPeople;
   if(NumLines > 0)
   {
      std::vector<int> NumPeopleInLines(NumLines);
      std::println("Number of People in Each Line");
      for(int i = 0; i < NumLines; ++i)
      {
         std::cin >> NumPeopleInLines[i];
      }

      const auto FoodLinesResults{FoodLines::foodLine(NumLines, NumPeople, NumPeopleInLines)};

      for(const auto& FoodLineResult : FoodLinesResults)
      {
         std::println("{} - {}", FoodLineResult.lineIndex, FoodLineResult.numPeopleInLineAtJoin);
      }
   }
}
