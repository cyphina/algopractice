#include "cavedoors.h"

#include <optional>
#include <utility>
#include <vector>
#include "core/DebugUtils.h"

namespace
{
   // Try a configuration of switches and returns the index of the first closed door.
   // When doing the problem we don't know the right switch positoins and swich to door mapping but
   // we can provide one in to test.
   int TryCombination(const std::vector<uint32_t>& TestSwitchPositions,
                      const std::vector<uint32_t>& ActualSwitchPositions)
   {
      if(ensure(TestSwitchPositions.size() == ActualSwitchPositions.size()))
      {
         for(size_t i{0}; i < TestSwitchPositions.size(); ++i)
         {
            if(TestSwitchPositions[i] != ActualSwitchPositions[i])
            {
               return static_cast<int>(i);
            }
         }
      }
      return -1;
   }

   // Submission
   void Answer(const std::vector<uint32_t>& SwitchPositions, const std::vector<uint32_t>& SwitchToDoor,
               const std::vector<uint32_t>& ActualSwitchPositions, const std::vector<uint32_t>& ActualSwitchToDoor)
   {
   }
}

void CaveDoors::ExploreCaveStep1(uint32_t NumSwitches, const std::vector<uint32_t>& ActualSwitchPositions)
{
   std::vector<uint32_t> SwitchPositions;
   std::vector<uint32_t> SwitchToDoor;

   SwitchPositions.resize(NumSwitches);
   SwitchToDoor.resize(NumSwitches);

   for(size_t i{0}; i < SwitchToDoor.size(); ++i)
   {
      SwitchToDoor[i] = static_cast<uint32_t>(i);
   }

   auto Result{TryCombination(SwitchPositions, ActualSwitchPositions)};

   while(Result != -1)
   {
      SwitchToDoor[Result] = 1 - SwitchToDoor[Result];
      Result               = TryCombination(SwitchPositions, ActualSwitchPositions);
   }

   // We're going to
}

void CaveDoors::ExploreCaveStepBinary(uint32_t NumSwitches, const std::vector<uint32_t>& ActualSwitchPositions)
{
   std::vector<uint32_t>                SwitchPositions;
   std::vector<std::optional<uint32_t>> SwitchToDoor;

   SwitchPositions.resize(NumSwitches);
   SwitchToDoor.resize(NumSwitches);

   // Try to associate each switch with a door
   for(size_t SwitchIndex{0}; SwitchIndex < NumSwitches; ++SwitchIndex)
   {
      for(size_t i{0}; i < NumSwitches; ++i)
      {
         if(!SwitchToDoor[i].has_value())
         {
            SwitchPositions[i] = 0;
         }
      }

      // Make sure to set it in such a way that it starts off as closed
      if(std::cmp_not_equal(TryCombination(SwitchPositions, ActualSwitchPositions), SwitchIndex))
      {
         for(size_t i{0}; i < NumSwitches; ++i)
         {
            if(!SwitchToDoor[i].has_value())
            {
               SwitchPositions[i] = 1;
            }
         }
      }

      size_t Low{};
      size_t High{NumSwitches};

      while(Low + 1 <= High)
      {
         size_t Mid{(Low + High) / 2};
         for(size_t i{0}; i < Mid; ++i)
         {
            if(!SwitchToDoor[i].has_value())
            {
               SwitchPositions[i] = 1 - SwitchPositions[i];
            }
         }

         if(std::cmp_not_equal(TryCombination(SwitchPositions, ActualSwitchPositions), SwitchIndex))
         {
            Low = Mid;
         }
         else
         {
            High = Mid;
         }

         // W ehave to reset the switch positions to force the door at SwitchIndex closed
         // I thought we could just store the previous combination attempt result but that can change even if we don't hit the switch.
         for(size_t i{0}; i < Mid; ++i)
         {
            if(!SwitchToDoor[i].has_value())
            {
               SwitchPositions[i] = 1 - SwitchPositions[i];
            }
         }
      }

      SwitchPositions[SwitchIndex] = Low;
   }
}
