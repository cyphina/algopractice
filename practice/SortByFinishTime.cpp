#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using MeetingTime = std::pair<uint32_t, uint32_t>;

int CountMaxNonOverlappingMeetingTimes(std::vector<std::pair<uint32_t, uint32_t>>& MeetingTimes)
{
   std::ranges::sort(MeetingTimes,
                     [](const MeetingTime& A, const MeetingTime& B)
                     {
                        return A.second < B.second;
                     });

   int CumulativeEndTime{};
   int Count{};

   for(const auto& Elem : MeetingTimes)
   {
      if(std::cmp_greater_equal(Elem.first, CumulativeEndTime))
      {
         //std::cout << Elem.first << " " << Elem.second << "\n";
         CumulativeEndTime = Elem.second;
         ++Count;
      }
   }

   return Count;
}

int main()
{
   std::vector<MeetingTime> EmptyMeetingTimes{};
   std::vector<MeetingTime> MeetingTimes{{6, 10}, {2, 5}, {1, 4}, {8, 12}, {12, 16}, {2, 14}, {8, 11},
                                         {3, 9},  {5, 9}, {1, 2}, {5, 7},  {2, 4},   {3, 5},  {0, 6}};
   std::cout << CountMaxNonOverlappingMeetingTimes(MeetingTimes) << "\n";
   std::cout << CountMaxNonOverlappingMeetingTimes(EmptyMeetingTimes) << "\n";
}
