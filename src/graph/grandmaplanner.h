#pragma once

#include <cstdint>
#include <unordered_set>
#include "graph/graph.h"

namespace GrandmaPlanner
{
   // The int is just to mark each node
   using GraphType = Graphs::Graph<int>;

   struct GrandmaPlannerResult
   {
      uint32_t MinDist;
      uint32_t NumMinDistRoutes;
   };

   /**
    * Given a complete graph of towns and a list of indices that mark town nodes as having cookie stores, give us the min distance to get to
    * town `n` aka Grandma's House while passing to at least one cookie store.
    *
    * Assumes Node 0 is the Start.
    *
    * Problem is supposed to require us to build a system that can augment our existing graph to represent a 0-1 cookie state.
    *
    * Then we'll run Dijkstra's on the augmented graph.
    */
   std::optional<GrandmaPlannerResult> GrandmaPlanner(const GraphType&                    Graph,
                                                      const std::unordered_set<uint32_t>& CookieStoreNodeIndices);
}
