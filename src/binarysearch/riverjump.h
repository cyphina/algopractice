#pragma once
#include <cstdint>
#include <vector>

namespace RiverJump
{
   /**
    * Tries to figure out the maximum gap we can achieve between any two rocks that are positioned in some arrangement of spot 0 to n.
    *
    * Rocks 0 and MaxRockPosition do not need to be provided. The RockPositions must be sorted.
    *
    * We have some rocks between them and we can remove up to NumRemovals to try and maximize the gap
    * between any two rocks.
    *
    * Returns the min gap between any two rocks after removing NumRemoval rocks from the list in a way to maximize this min gap.
    */
   uint32_t RiverJump(const std::vector<uint32_t>& RockPositions, uint32_t MaxRockPosition, uint32_t NumRemovals);
}
