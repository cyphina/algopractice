#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

// <int,int> - To Node Index to Priority
int ShortestPath(const std::vector<std::vector<std::pair<int, int>>>& adj, int source, int target)
{
   if(adj.empty() || source > adj.size() || target > adj.size())
   {
      return -1;
   }

   struct NodePriority
   {
      int NodeIndex{};
      int Priority{};

      [[nodiscard]] bool operator==(const NodePriority&) const = default;
      [[nodiscard]] auto operator<=>(const NodePriority& Other) const { return Priority <=> Other.Priority; }
   };

   constexpr int    SENTINEL{std::numeric_limits<int>::max()};
   std::vector<int> CurrentMinCosts(adj.size(), SENTINEL);
   CurrentMinCosts[source] = 0;

   std::priority_queue<NodePriority, std::vector<NodePriority>, std::greater<>> Priorities;
   Priorities.emplace(source, 0);

   for(size_t i{0}; i < adj.size(); ++i)
   {
      if(Priorities.empty())
      {
         break;
      }

      auto MinNodePriority{Priorities.top()};
      Priorities.pop();

      // In theory there shouldn't be a situation where priority can be empty so just keep doing this.
      while(MinNodePriority.Priority != CurrentMinCosts[MinNodePriority.NodeIndex])
      {
         MinNodePriority = Priorities.top();
         Priorities.pop();
      }

      if(MinNodePriority.NodeIndex == target)
      {
         break;
      }

      const auto& Connections{adj[MinNodePriority.NodeIndex]};
      const auto  MinNodePriorityCost{MinNodePriority.Priority};

      for(const auto& [ToNodeIndex, Priority] : Connections)
      {
         const auto NewPriority{MinNodePriorityCost + Priority};
         if(NewPriority < CurrentMinCosts[ToNodeIndex])
         {
            CurrentMinCosts[ToNodeIndex] = NewPriority;
            Priorities.emplace(ToNodeIndex, NewPriority);
         }
      }
   }

   if(CurrentMinCosts[target] != SENTINEL)
   {
      return CurrentMinCosts[target];
   }

   return -1;
}

int main()
{
   std::vector<std::vector<std::pair<int, int>>> Graph1;
   Graph1.emplace_back(std::vector<std::pair<int, int>>{{0, 1}, {1, 2}, {2, 4}});
   Graph1.emplace_back(std::vector<std::pair<int, int>>{{0, 3}, {3, 3}});
   Graph1.emplace_back(std::vector<std::pair<int, int>>{{0, 1}, {3, 3}});
   Graph1.emplace_back(std::vector<std::pair<int, int>>{{1, 4}, {2, 3}});

   std::cout << ShortestPath(Graph1, 0, 3) << "\n";
   std::cout << ShortestPath(Graph1, 3, 0) << "\n";

   std::vector<std::vector<std::pair<int, int>>> EmptyGraph;
   std::cout << ShortestPath(EmptyGraph, 0, 0) << "\n";
   std::cout << ShortestPath(EmptyGraph, 0, 1) << "\n";
   std::cout << ShortestPath(EmptyGraph, 1, 0) << "\n";

   std::vector<std::vector<std::pair<int, int>>> SingleGraph;
   SingleGraph.emplace_back(std::vector<std::pair<int, int>>{{0, 5}});

   std::cout << ShortestPath(SingleGraph, 0, 0) << "\n";

   std::vector<std::vector<std::pair<int, int>>> ZeroWeightEdge;
   ZeroWeightEdge.emplace_back(std::vector<std::pair<int, int>>{{0, 5}, {1, 0}});
   ZeroWeightEdge.emplace_back(std::vector<std::pair<int, int>>{{0, 2}});

   std::cout << ShortestPath(ZeroWeightEdge, 0, 1) << "\n";
   std::cout << ShortestPath(ZeroWeightEdge, 1, 0) << "\n";

   std::vector<std::vector<std::pair<int, int>>> DisjointGraph;
   DisjointGraph.emplace_back(std::vector<std::pair<int, int>>{{1, 3}});
   DisjointGraph.emplace_back(std::vector<std::pair<int, int>>{{1, 0}});

   std::cout << ShortestPath(DisjointGraph, 0, 1) << "\n";
   std::cout << ShortestPath(DisjointGraph, 1, 0) << "\n";
}
