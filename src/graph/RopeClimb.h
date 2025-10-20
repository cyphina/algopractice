#pragma once
#include <cstdint>
#include <optional>
#include <unordered_set>
#include <vector>

namespace RopeClimb
{
   struct RopeSegmentCost
   {
      uint32_t              Value;
      std::vector<uint32_t> IndexHistory;

      [[nodiscard]] bool                 operator==(const RopeSegmentCost& Rhs) const;
      [[nodiscard]] std::strong_ordering operator<=>(const RopeSegmentCost& Rhs) const;
   };

   std::optional<RopeSegmentCost> RopeClimb(uint32_t JumpHeight, uint32_t TargetSegmentIndex,
                                            const std::unordered_set<uint32_t>& PowderedSegmentIndices);
}
