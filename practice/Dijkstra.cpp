#include <iostream>
#include <queue>

// <int,int> - To Node Index to Priority
int ShortestPath(int n, const std::vector<std::vector<std::pair<int, int>>>& adj, int source, int target)
{
   struct NodePriority
   {
      int NodeIndex{};
      int Priority{};

      [[nodiscard]] bool operator==(const NodePriority&) const = default;
      [[nodiscard]] auto operator<=>(const NodePriority& Other) const { return Priority <=> Other.Priority; }
   };

   std::vector<int> CurrentMinTimes(adj.size(), -1);

   std::priority_queue<NodePriority, std::vector<std::pair<int, int>>, std::greater<>> Priorities;
   Priorities.emplace(source, 0);

   int MinPriorityNodeIndex{source};

   for(size_t i{0}; i < adj.size(); ++i)
   {
      for()
   }
}
