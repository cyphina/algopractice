#include "booktranslation.h"

#include <unordered_map>

namespace BookTranslation
{
   std::optional<NodeCost> BookTranslation::FindMinimalCostTranslation(GraphType&       LanguageGraph,
                                                                       std::string_view StartingLanguage,
                                                                       std::string_view TargetLanguage)
   {
      const auto& Nodes{LanguageGraph.GetNodes()};

      const auto StartingNode{std::ranges::find_if(Nodes,
                                                   [&StartingLanguage](const auto& Node)
                                                   {
                                                      return Node->Data == StartingLanguage;
                                                   })};

      const auto TargetNode{std::ranges::find_if(Nodes,
                                                 [&TargetLanguage](const auto& Node)
                                                 {
                                                    return Node->Data == TargetLanguage;
                                                 })};

      if(StartingNode == Nodes.end() || TargetNode == Nodes.end())
      {
         return {};
      }

      std::queue<const NodeType*>                   Queue;
      std::unordered_map<const NodeType*, NodeCost> ExploredNodeCosts;

      ExploredNodeCosts.insert({StartingNode->get(), {}});
      Queue.push(StartingNode->get());

      while(!Queue.empty())
      {
         const auto CurrentNode{Queue.front()};
         Queue.pop();

         const auto CurrentNodeCost{ExploredNodeCosts.find(CurrentNode)->second};

         for(const auto& Edge : CurrentNode->Edges)
         {
            const auto PreviousCost{ExploredNodeCosts.find(Edge.Node)};
            NodeCost   CostToEdgeNode{CurrentNodeCost.EdgeCost + Edge.Cost.value(),
                                    static_cast<uint16_t>(CurrentNodeCost.EdgeCountCost + 1)};

            if(PreviousCost == ExploredNodeCosts.end())
            {
               ExploredNodeCosts.insert({Edge.Node, CostToEdgeNode});
               Queue.emplace(Edge.Node);
            }
            else
            {
               if(PreviousCost->second > CostToEdgeNode)
               {
                  ExploredNodeCosts[Edge.Node] = CostToEdgeNode;
                  Queue.emplace(Edge.Node);
               }
            }
         }
      }

      return ExploredNodeCosts[TargetNode->get()];
   }
}
