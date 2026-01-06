#include <queue>
#include <unordered_set>
#include <vector>

// Given n computers labeled 0 to n-1 and a list of bidirectional communication links, find the number of connected components.
// The key is since our data is in a nice format we can setup our adjacency list quite easily.
// And we have t loop over all the nodes to handle the fact that we might have no links. Like if n is 5 and we only have {0,1} as our link, 2,3 and 4 are
// all isolated.

int countIsolatedCommunicationGroups(std::vector<std::vector<int>> links, int n)
{
   std::vector<std::vector<int>> Adj(n);
   for(const auto& Link : links)
   {
      Adj[Link[0]].emplace_back(Link[1]);
      Adj[Link[1]].emplace_back(Link[0]);
   }

   // Check all since we can have isolated computers
   int                     ConnectedComponentCount{};
   std::unordered_set<int> VisitedNodes;

   std::queue<int> ConnectedNodes;
   for(std::size_t i{0}; i < static_cast<std::size_t>(n); ++i)
   {
      if(VisitedNodes.find(i) != VisitedNodes.end())
      {
         continue;
      }

      ++ConnectedComponentCount;

      ConnectedNodes.push(i);
      while(!ConnectedNodes.empty())
      {
         const auto& ConnectedNode{ConnectedNodes.front()};
         ConnectedNodes.pop();
         VisitedNodes.emplace(ConnectedNode);

         for(const auto& NextConnection : Adj[ConnectedNode])
         {
            if(VisitedNodes.find(NextConnection) == VisitedNodes.end())
            {
               ConnectedNodes.push(NextConnection);
            }
         }
      }
   }

   return ConnectedComponentCount;
}

int main()
{
}
