#include "grandmaplanner.h"
#include <queue>
#include <ranges>
#include <unordered_map>

namespace
{
   enum class ECookieStoreState : uint8_t
   {
      NotVisited = 0,
      Visited,
   };

   constexpr uint32_t SENTINEL{std::numeric_limits<uint32_t>::max()};

   struct GrandmaPlannerPriority
   {
      GrandmaPlanner::GraphType::NodeType* Node{};
      ECookieStoreState                    State{};
      uint32_t                             MinTime{SENTINEL};

      [[nodiscard]] auto operator<=>(const GrandmaPlannerPriority& OtherCookieStateMinTime) const;
   };

   auto GrandmaPlannerPriority::operator<=>(const GrandmaPlannerPriority& OtherCookieStateMinTime) const
   {
      const auto MinTimeCompare{MinTime <=> OtherCookieStateMinTime.MinTime};
      if(MinTimeCompare == std::strong_ordering::equal)
      {
         return State <=> OtherCookieStateMinTime.State;
      }
      return MinTimeCompare;
   }

   struct GrandmaPlannerMinRecord
   {
      uint32_t GetMin(ECookieStoreState State) const;

      uint32_t NotVisitedMinTime{SENTINEL};
      uint32_t VisitedMinTime{SENTINEL};
   };

   uint32_t GrandmaPlannerMinRecord::GetMin(ECookieStoreState State) const
   {
      switch(State)
      {
         case ECookieStoreState::NotVisited:
         {
            return NotVisitedMinTime;
         }
         case ECookieStoreState::Visited:
         {
            return VisitedMinTime;
         }
      }

      return SENTINEL;
   }

   using NodePriorities   = std::priority_queue<GrandmaPlannerPriority, std::vector<GrandmaPlannerPriority>,
                                                std::greater<GrandmaPlannerPriority>>;
   using NodeToMinTimeMap = std::unordered_map<GrandmaPlanner::GraphType::NodeType*, GrandmaPlannerMinRecord>;

   void Relax(GrandmaPlanner::GraphType::NodeType* CurrentNode, ECookieStoreState CurrentState,
              const std::unordered_set<uint32_t>& CookieStoreNodeIndices, NodePriorities& PQueue,
              NodeToMinTimeMap& MinTimes)
   {
      const auto CurrentNodeCost{MinTimes[CurrentNode].GetMin(CurrentState)};

      switch(CurrentState)
      {
         case ECookieStoreState::NotVisited:
         {
            for(const auto& [Node, Cost] : CurrentNode->Edges)
            {
               const auto               TargetNode{Node};
               GrandmaPlannerMinRecord& TargetNodeMinCost{MinTimes[TargetNode]};
               const auto               CostToTarget{CurrentNodeCost + Cost.value()};

               if(CookieStoreNodeIndices.contains(TargetNode->Data))
               {
                  PQueue.emplace(TargetNode, ECookieStoreState::Visited, CostToTarget);
                  TargetNodeMinCost.VisitedMinTime = CostToTarget;
               }
               else
               {
                  if(TargetNodeMinCost.NotVisitedMinTime > CostToTarget)
                  {
                     PQueue.emplace(TargetNode, ECookieStoreState::NotVisited, CostToTarget);
                     TargetNodeMinCost.NotVisitedMinTime = CostToTarget;
                  }
               }
            }

            break;
         }
         case ECookieStoreState::Visited:
         {
            for(const auto& [Node, Cost] : CurrentNode->Edges)
            {
               const auto               TargetNode{Node};
               GrandmaPlannerMinRecord& TargetNodeMinCost{MinTimes[TargetNode]};
               const auto               CostToTarget{CurrentNodeCost + Cost.value()};

               if(TargetNodeMinCost.VisitedMinTime > CostToTarget)
               {
                  PQueue.emplace(TargetNode, ECookieStoreState::Visited, CostToTarget);
                  TargetNodeMinCost.VisitedMinTime = CostToTarget;
               }
            }

            break;
         }
      }
   }
}

namespace GrandmaPlanner
{

   std::optional<GrandmaPlannerResult> GrandmaPlanner(const GraphType&                    Graph,
                                                      const std::unordered_set<uint32_t>& CookieStoreNodeIndices)
   {
      // Explore via Dijkstra
      // But setup some exploration rules in Relax

      // Track the min values since we're not going to always have the updated value in PQs so we need some record to skip the excess.
      const auto& Nodes{Graph.GetNodes()};
      const auto  NumNodes{Nodes.size()};

      NodeToMinTimeMap MinTimes;
      MinTimes.emplace(Nodes[0].get(), GrandmaPlannerMinRecord{0, SENTINEL});
      NodePriorities Priorities;

      Priorities.emplace(Nodes[0].get(), ECookieStoreState::NotVisited, 0);

      for(int i{0}; i < NumNodes * 2; ++i)
      {
         if(Priorities.empty())
         {
            return {};
         }

         GrandmaPlannerPriority MinPriority{Priorities.top()};
         Priorities.pop();

         if(MinPriority.Node == Nodes[NumNodes - 1].get() && MinPriority.State == ECookieStoreState::Visited)
         {
            break;
         }

         // Get past the outdated priority tracking.
         while(MinPriority.MinTime != MinTimes[MinPriority.Node].GetMin(MinPriority.State))
         {
            MinPriority = Priorities.top();
            Priorities.pop();
         }

         Relax(MinPriority.Node, MinPriority.State, CookieStoreNodeIndices, Priorities, MinTimes);
      }

      const auto DestinationNode{Nodes[NumNodes - 1].get()};
      if(MinTimes.contains(DestinationNode))
      {
         const auto MinTime{MinTimes[DestinationNode]};
         if(MinTime.VisitedMinTime != SENTINEL)
         {
            return GrandmaPlannerResult{.MinDist = MinTimes[DestinationNode].VisitedMinTime, .NumMinDistRoutes = 0};
         }
      }

      return {};
   }

}
