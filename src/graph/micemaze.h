#pragma once
#include "graph.h"
#include <queue>
#include <vector>

namespace MiceMaze
{
   using GraphType = Graphs::Graph<int>;

   struct DijkstraNodeData
   {
      Graphs::Node<int>* Node;
      uint32_t           CurrentMinCost{};

      [[nodiscard]] bool                 operator==(const DijkstraNodeData& OtherNode) const;
      [[nodiscard]] std::strong_ordering operator<=>(const DijkstraNodeData& OtherNode) const;
   };

   /**
    * Returns how many mice can reach the exit cell within the time limit
    * Requires we pass in a reverse graph (edges pointing backwards to the graph we want to find the solution to)
    */
   std::vector<DijkstraNodeData> MiceMaze(uint16_t NumCellsInMaze, uint16_t ExitCellIndex, uint16_t ExitTime,
                                          const GraphType& ReverseGraph);

}
