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

      [[nodiscard]] bool                 operator==(const TreapNode& Other) const;
      [[nodiscard]] std::strong_ordering operator<=>(const TreapNode& Other) const;
   };

   struct TreapNodeWithIndex
   {
      TreapNode*  Node;
      std::size_t Index;

      [[nodiscard]] bool operator==(const TreapNodeWithIndex& Other) const;
      [[nodiscard]] auto operator<=>(const TreapNodeWithIndex& Other) const;
   };

   // Prints (<left_subtreap><L><right_subtreap>)
   std::string GenerateTreapStringSlow(std::vector<TreapNode>& TreapNodes);

   // Prints (<left_subtreap><L><right_subtreap>)
   std::string GenerateTreapStringFast(std::vector<TreapNode>& TreapNodes);

}
