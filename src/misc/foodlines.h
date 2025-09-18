#pragma once
#include <vector>

namespace FoodLines
{
   struct LineJoinerData
   {
      int lineIndex{0};
      int numPeopleInLineAtJoin{0};
   };

   // Person always joins the least empty line.
   // Tries to output for each person, the number of people in the line at the time that person joined a line.
   std::vector<LineJoinerData> foodLine(int NumLines, int NumPeople, const std::vector<int>& InitialPeopleInLinesCount);
}
