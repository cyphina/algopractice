#include "micemaze.h"
#include "graph.h"
#include <numeric>

namespace MiceMaze
{
   std::strong_ordering DijkstraNodeData::operator<=>(const DijkstraNodeData& OtherNode) const
   {
      const auto CostCompare{CurrentMinCost <=> OtherNode.CurrentMinCost};
      if(CostCompare == std::strong_ordering::equal)
      {
         return GraphNodeIndex <=> OtherNode.GraphNodeIndex;
      }
      return CostCompare;
   }

   bool DijkstraNodeData::operator==(const DijkstraNodeData& OtherNode) const
   {
      return GraphNodeIndex == OtherNode.GraphNodeIndex;
   }

   int MiceMaze(uint16_t NumCellsInMaze, uint16_t ExitCellIndex, uint16_t ExitTime,
                std::vector<Graph::GraphEdgeData>&& EdgeData)
   {
      std::vector<int> NodeData;
      std::ranges::iota(NodeData, NumCellsInMaze);
      Graph::Graph Graph{std::move(NodeData), std::move(EdgeData)};

      std::priority_queue<DijkstraNodeData> RelaxData;
      return {};
   }
}
