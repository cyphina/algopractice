#pragma once

#include <cstdint>

namespace CaveDoors
{
   /** This step involves assuming switch i is associated with door i, and thus we just need to figure out which switches to open and close */
   void ExploreCaveStep1(uint32_t NumSwitches);
}
