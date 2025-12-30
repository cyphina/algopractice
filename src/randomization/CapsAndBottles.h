#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace CapsAndBottles
{
   using CapToBottleIndices = std::vector<std::pair<uint32_t, uint32_t>>;

   /**
    * Returns a vector that has indices of all the caps and the associated index of the bottle.
    */
   CapToBottleIndices MatchCapsAndBottles(const std::vector<uint32_t>& CapSizes,
                                          const std::vector<uint32_t>& BottleSizes);
}
