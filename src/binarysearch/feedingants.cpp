#include "feedingants.h"

#include <algorithm>
#include "core/DebugUtils.h"
#include "core/MathUtil.h"

namespace
{
   bool TestLiquidAmount(const FeedingAnts::NodeType& Node, uint32_t AmountOfLiquid)
   {
      if(Node.children.empty())
      {
         if(Node.data.has_value())
         {
            if(Node.data.value() > AmountOfLiquid)
            {
               return false;
            }
         }
      }
      else
      {
         bool bEnoughLiquidForChildren{true};
         for(const auto& Edge : Node.children)
         {
            // Square behavior for a superpipe. Bobi gets to decide whether nor to to use the sepcial behavior but we can pretty much always do this since
            // there's no penalty for using it since our precondition is that every ant needs at least 1 liter or liquid.
            // If we somehow get a smaller value than 1 propagating to our pipes and we square it, it would become smaller. But that would lead to the same result since
            // our amount of liquid was already too small to feed any ants.
            const auto EdgeData{Edge.Data.value()};
            const auto RegularPipeFlow{AmountOfLiquid * EdgeData.SuctionPercentage};
            const auto PipeFlow{EdgeData.bIsSuperPipe ? RegularPipeFlow * RegularPipeFlow : RegularPipeFlow};

            bEnoughLiquidForChildren = bEnoughLiquidForChildren && TestLiquidAmount(*Edge.Node, PipeFlow);

            if(!bEnoughLiquidForChildren)
            {
               return false;
            }
         }
      }

      return true;
   }
}

float FeedingAnts::FeedingAntsProblem(std::vector<TerrariumEdge>&& Pipes,
                                      std::vector<NodeDataType>&&  RequiredLiquidForAnts)
{
   TreeType Tree;

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

      const auto& Nodes{Tree.GetNodes()};
      for(const auto& Pipe : Pipes)
      {
         NodeType::EdgeType Edge;
         Edge.Data = Pipe.PipeInfo;
         Edge.Node = Nodes[Pipe.ToNodeIndex].get();
         Nodes[Pipe.FromNodeIndex]->children.emplace_back(Edge);
      }

      float Low{};
      float High{2'000'000'000};
      float Mid{(Low + High) / 2};

      while(!MathUtil::NearlyEqualAbs(Low, High))
      {
         const auto bEnoughLiquid{TestLiquidAmount(Tree, Mid)};
         if(bEnoughLiquid)
         {
            High = Mid;
         }
         else
         {
            Low = Mid;
         }

         Mid = (Low + High) / 2;
      }

      return High;
   }

   return -1.f;
}

bool FeedingAnts::TestLiquidAmount(const TreeType& Tree, uint32_t InitialAmountOfLiquid)
{
   const auto& Nodes{Tree.GetNodes()};
   return ::TestLiquidAmount(*Nodes[0].get(), InitialAmountOfLiquid);
}
