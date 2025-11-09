#pragma once

#include <cstdint>
#include <iostream>
#include <optional>
#include "tree/NaryTree.h"

namespace FeedingAnts
{
   struct EdgeData
   {
      float SuctionPercentage{};
      bool  bIsSuperPipe{};
   };

   using NodeDataType = std::optional<uint32_t>;
   using NodeType     = NaryTree::NodeWithEdge<NodeDataType, EdgeData>;
   using TreeType     = NaryTree::NaryTree<FeedingAnts::NodeDataType, FeedingAnts::NodeType>;

   struct TerrariumEdge
   {
      // We'll use indices instead of nodes cause we're making a tree just for this problem and the end user can provide the simplest id
      // to describe the problem since the terrarium isn't changing.
      uint32_t FromNodeIndex{};
      uint32_t ToNodeIndex{};
      EdgeData PipeInfo;
   };

   bool TestLiquidAmount(const TreeType& Tree, uint32_t InitialAmountOfLiquid);

   /**
    * Inputs should be such that the user shouldn't have to know the details of how we solve the problem.
    * But in this case the terrarium itself is a tree.
    *
    * Figures out the minimum amount of liquid required to feed all the ants in the leaf nodes given there's a pipe system to
    * describe how water propagates throughout the tree.
    *
    * Each ant requires at least 1 liter of water.
    */
   float FeedingAntsProblem(std::vector<TerrariumEdge>&& Pipes, std::vector<NodeDataType>&& RequiredLiquidForAnt);
}
