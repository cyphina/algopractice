#pragma once

#include "Graph.h"
#include <cstdint>
#include <optional>

namespace BookTranslation
{
   using GraphType = Graphs::Graph<std::string>;
   using NodeType  = Graphs::Node<std::string>;

   struct NodeCost
   {
      uint32_t EdgeCost{};
      uint16_t EdgeCountCost{};

      [[nodiscard]] bool                 operator==(const NodeCost& OtherNode) const = default;
      [[nodiscard]] std::strong_ordering operator<=>(const NodeCost& OtherNode) const
      {
         if(const auto Res{EdgeCountCost <=> OtherNode.EdgeCountCost}; Res != std::strong_ordering::equal)
         {
            return Res;
         }
         return EdgeCost <=> OtherNode.EdgeCost;
      }
   };

   std::optional<NodeCost> FindMinimalCostTranslation(GraphType& LanguageGraph, std::string_view StartingLanguage,
                                                      std::string_view TargetLanguage);
}
