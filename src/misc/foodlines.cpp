#include "foodlines.h"

#include <assert.h>

namespace
{
   void shortestLineIndex(int NumPeople, std::vector<int>& NumPeopleInLines, std::vector<FoodLines::LineJoinerData>& NumberOfPeopleInLineAtJoinPoint)
   {
      for(int i = 0; i < NumPeople; ++i)
      {
         int SmallestLineIndex{0};

         for(int LineIndex = 1; LineIndex < NumPeopleInLines.size(); ++LineIndex)
         {
            if(NumPeopleInLines[LineIndex] < NumPeopleInLines[SmallestLineIndex])
            {
               SmallestLineIndex = LineIndex;
            }
         }

         NumberOfPeopleInLineAtJoinPoint.push_back({SmallestLineIndex, NumPeopleInLines[SmallestLineIndex]});
         ++NumPeopleInLines[SmallestLineIndex];
      }
   }
}

std::vector<FoodLines::LineJoinerData> FoodLines::foodLine(int NumLines, int NumPeople, const std::vector<int>& InitialPeopleInLinesCount)
{
   assert(InitialPeopleInLinesCount.size() <= NumLines);

   if(NumPeople == 0 || NumLines == 0)
   {
      return {};
   }

   std::vector<int> NumPeopleInLines(NumLines);

   for(int i{0}; i < NumLines; ++i)
   {
      if(i < InitialPeopleInLinesCount.size())
      {
         NumPeopleInLines[i] = InitialPeopleInLinesCount[i];
      }
   }

   std::vector<FoodLines::LineJoinerData> NumberOfPeopleInLineAtJoinPoint;

   shortestLineIndex(NumPeople, NumPeopleInLines, NumberOfPeopleInLineAtJoinPoint);

   return NumberOfPeopleInLineAtJoinPoint;
}
