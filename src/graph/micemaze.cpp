#include "micemaze.h"
#include "graph.h"
#include <numeric>
#include <ranges>
#include <unordered_map>

namespace
{
   using NodeToMinTimeMap = std::unordered_map<MiceMaze::GraphType::NodeType*, uint32_t>;
   using PriorityQueue    = std::priority_queue<MiceMaze::DijkstraNodeData, std::vector<MiceMaze::DijkstraNodeData>,
                                                std::greater<MiceMaze::DijkstraNodeData>>;

   void Relax(const MiceMaze::GraphType& Graph, NodeToMinTimeMap& MinTimeMap,
              MiceMaze::GraphType::NodeType* NodeToVisit, PriorityQueue& MinTimePriority)
   {
      const auto CurrentCellNodeCost{MinTimeMap[NodeToVisit]};

      for(const auto& Edge : NodeToVisit->Edges)
      {
         if(Edge.Cost)
         {
            const auto PathCost{CurrentCellNodeCost + Edge.Cost.value()};
            if(PathCost < MinTimeMap[Edge.Node])
            {
               MinTimeMap[Edge.Node] = PathCost;
               MinTimePriority.emplace(Edge.Node, PathCost);
            }
         }
      }
   }
}

namespace MiceMaze
{
   std::strong_ordering DijkstraNodeData::operator<=>(const DijkstraNodeData& OtherNode) const
   {
      const auto CostCompare{CurrentMinCost <=> OtherNode.CurrentMinCost};
      if(CostCompare == std::strong_ordering::equal)
      {
         return Node <=> OtherNode.Node;
      }
      return CostCompare;
   }

   bool DijkstraNodeData::operator==(const DijkstraNodeData& OtherNode) const
   {
      return Node == OtherNode.Node;
   }

   std::vector<DijkstraNodeData> MiceMaze(uint16_t NumCellsInMaze, uint16_t ExitCellIndex, uint16_t ExitTime,
                                          const GraphType& ReverseGraph)
   {
      if(ExitCellIndex >= NumCellsInMaze)
      {
         return {};
      }

      const auto& GraphNodes{ReverseGraph.GetNodes()};

      if(GraphNodes.empty())
      {
         return {};
      }

      // Since we can't like update nodes via relaxing from the priority queue the plan is to maintian the optimal distances in a map
      // Ordinarily you use a vector where
      // Index is the index of the node (nodes should be stable for the run).
      // Value is the actual optimal distance.
      // But since we use node pointers we need a map.
      NodeToMinTimeMap NodesToMinTime;
      NodesToMinTime.reserve(NumCellsInMaze);

      static constexpr uint32_t Sentinel{std::numeric_limits<uint32_t>::max()};

      const auto Indices      = std::views::repeat(Sentinel, NumCellsInMaze);
      const auto NodePointers = GraphNodes | std::views::transform(
                                                 [](const auto& Node)
                                                 {
                                                    return Node.get();
                                                 });
      const auto ZippedIndicesToNodePointers = std::views::zip(NodePointers, Indices);
#if __cpp_lib_containers_ranges
      NodesToMinTime.insert_range(ZippedIndicesToNodePointers);
#elif
      assert(false);
      return {};
#endif

      // Exit cell starts at 0;
      NodesToMinTime[GraphNodes[ExitCellIndex].get()] = 0;

      PriorityQueue Priorities;

      const auto DijkstraNodes{GraphNodes | std::views::transform(
                                                [&NodesToMinTime](const auto& Node)
                                                {
                                                   const auto NodePtr{Node.get()};
                                                   return DijkstraNodeData(NodePtr, NodesToMinTime[NodePtr]);
                                                })};

      Priorities.push_range(DijkstraNodes);

      for(int i{0}; i < NumCellsInMaze; ++i)
      {
         DijkstraNodeData MinPriority{Priorities.top()};
         Priorities.pop();

         if(MinPriority.CurrentMinCost == Sentinel)
         {
            // Rest of the graph is detached.
            break;
         }

         // Since the priority node is prefiled we can pass stale priority values
         while(MinPriority.CurrentMinCost != NodesToMinTime[MinPriority.Node])
         {
            MinPriority = Priorities.top();
            Priorities.pop();
         }

         Relax(ReverseGraph, NodesToMinTime, MinPriority.Node, Priorities);
      }

      std::vector<DijkstraNodeData> Result;
      for(const auto [Node, Cost] : NodesToMinTime)
      {
         // Prevent including exit node
         if(Cost != 0 && Cost <= ExitTime)
         {
            Result.emplace_back(Node, Cost);
         }
      }

      return Result;
   }
}
