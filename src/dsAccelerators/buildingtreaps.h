#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace BuildingTreaps
{
   struct TreapNode
   {
      std::string Label;
      uint32_t    Priority{};

      [[nodiscard]] bool operator==(const TreapNode& Other) const;
      [[nodiscard]] auto operator<=>(const TreapNode& Other) const;
   };

   // Prints (<left_subtreap><L><right_subtreap>)
   std::string GenerateTreapStringSlow(std::vector<TreapNode>& TreapNodes);

}
