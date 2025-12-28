#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace Yokan
{
   enum class YokanQueryResult
   {
      NO,
      YES,
   };

   struct FlavorIndices
   {
      FlavorIndices(std::size_t InitialSize);

      std::vector<std::vector<std::size_t>> Data;
   };

   struct YokanResult
   {
      std::pair<int, int> ValidFlavorIndices{-1, -1};
      YokanQueryResult    queryResult{YokanQueryResult::NO};
   };

   /** Given a piece of Yokan described by piece flavors, tries to query a slab at LeftSlabIndex to RightSlabIndex to see if two friends can get at least 1/3 pieces of the same flavors out of the slab. */
   FlavorIndices BuildFlavorIndices(uint32_t MaxPieceFlavor, const std::vector<uint32_t>& PieceFlavors);

   std::optional<YokanResult> YokanQuery(std::vector<uint32_t>& PieceFlavors, const FlavorIndices& FlavorIndexLookup,
                                         std::size_t LeftSlabInclusiveIndex, std::size_t RightSlabExclusiveIndex);
}
