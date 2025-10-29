#pragma once
#include "graph.h"
#include <queue>
#include <vector>

namespace MiceMaze
{
   struct DijkstraNodeData
   {
      uint16_t GraphNodeIndex{};
      uint32_t CurrentMinCost{};

      [[nodiscard]] bool                 operator==(const DijkstraNodeData& OtherNode) const;
      [[nodiscard]] std::strong_ordering operator<=>(const DijkstraNodeData& OtherNode) const;
   };

   /** Returns how many mice can reach the exit cell within the time limit */
   int MiceMaze(uint16_t NumCellsInMaze, uint16_t ExitCellIndex, uint16_t ExitTime,
                std::vector<Graph::GraphEdgeData>&& EdgeData);

}
