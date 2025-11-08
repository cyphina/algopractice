#include "feedingants.h"

#include <algorithm>
#include "core/DebugUtils.h"

float FeedingAnts::FeedingAntsProblem(std::vector<TerrariumEdge>&& Pipes,
                                      std::vector<NodeDataType>&&  RequiredLiquidForAnts)
{
   NaryTree::NaryTree<NodeDataType, NodeType> Tree;

   if(RequiredLiquidForAnts.empty())
   {
      return 0;
   }

   if(ensure(Pipes.size() == RequiredLiquidForAnts.size() - 1))
   {
      for(const auto& RequiredLiquid : RequiredLiquidForAnts)
      {
         if(RequiredLiquid.has_value())
         {
            Tree.AddNode(RequiredLiquid);
         }
      }
   }

   return -1.f;
}
