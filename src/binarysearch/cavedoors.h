#pragma once

#include <cstdint>
#include <vector>

namespace CaveDoors
{
   enum class SwitchState
   {
      Off,
      On
   };

   /** This step involves assuming switch i is associated with door i, and thus we just need to figure out which switches to open and close */
   void ExploreCaveStep1(uint32_t NumSwitches, const std::vector<uint32_t>& ActualSwitchPositions);
   void ExploreCaveStepBinary(uint32_t NumSwitches, const std::vector<uint32_t>& ActualSwitchPositions);
}
