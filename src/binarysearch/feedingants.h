#pragma once

#include <cstdint>
#include <iostream>
#include <optional>
#include "tree/NaryTree.h"

namespace FeedingAnts
{
   using NodeDataType = std::optional<uint32_t>;
   using NodeType     = NaryTree::NodeWithEdge<NodeDataType>;

   struct TerrariumEdge
   {
      // We'll use indices instead of nodes cause we're making a tree just for this problem and the end user can provide the simplest id
      // to describe the problem since the terrarium isn't changing.
      uint32_t FromNodeIndex{};
      uint32_t ToNodeIndex{};
      bool     isSuperPipe{};
   };

   /**
    * Inputs should be such that the user shouldn't have to know the details of how we solve the problem.
    * But in this case the terrarium itself is a tree.
    */
   float FeedingAntsProblem(std::vector<TerrariumEdge>&& Pipes, std::vector<NodeDataType>&& RequiredLiquidForAnt);
}
