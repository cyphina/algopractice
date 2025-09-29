#include <algorithm>
#include <compare>
#include <iostream>
#include <print>
#include "tree/NaryTree.h"

namespace
{
   using NodeType = std::string;
   using Node     = NaryTree::Node<NodeType>;
   // Ultimately we'll store a unique pointer to things in case we have to reallocate the underlying data for the set.
   using NodePtr = std::unique_ptr<NaryTree::Node<NodeType>>;
}

int main()
{
   std::println("Descendant Distance - Score is how many descendants a family member has at distance d (d edges below).");
   std::println("Print num inputs.");

   size_t NumInputs{0};
   std::cin >> NumInputs;

   std::println("{} Test Cases!", NumInputs);

   for(size_t TestCaseIndex{0}; std::cin && TestCaseIndex < NumInputs; ++TestCaseIndex)
   {
      size_t NumLinesToBuildTree{0}, DescendantDistanceOfInterest{0};
      std::cin >> NumLinesToBuildTree >> DescendantDistanceOfInterest;

      if(std::cin && NumLinesToBuildTree > 0)
      {
         std::println("Text Case Index {}, Descendant Distance {}", TestCaseIndex, DescendantDistanceOfInterest);
         std::println("{} lines to build tree", NumLinesToBuildTree);

         size_t                          NumChildren{0};
         std::string                     NodeName{0};
         NaryTree::NaryTree<std::string> Tree;
         Node*                           ParentNode{nullptr};

         for(size_t i{0}; std::cin && i < NumLinesToBuildTree; ++i)
         {
            // name of node, integer n, n children names
            std::cin >> NodeName >> NumChildren;
            if(std::cin)
            {
               std::println("{} parent, {} children", NodeName, NumChildren);

               ParentNode = Tree.FindNode(NodeName);
               if(!ParentNode)
               {
                  ParentNode = {Tree.AddNode(NodeType{NodeName})};
               }

               if(ParentNode)
               {
                  for(size_t j{0}; std::cin && j < NumChildren; ++j)
                  {
                     std::cin >> NodeName;
                     auto ExistingChildNode{Tree.FindNode(NodeName)};

                     if(!ExistingChildNode)
                     {
                        const auto ChildNode{Tree.AddNode(NodeType{NodeName})};
                        if(ParentNode && ChildNode)
                        {
                           ParentNode->children.emplace_back(ChildNode);
                        }
                     }
                     else
                     {
                        ParentNode->children.emplace_back(ExistingChildNode);
                     }
                  }
               }
            }
         }

         // Need to get descendant distance results

         using DescendantDistanceType = std::pair<Node*, int>;
         std::vector<DescendantDistanceType> DescendantDistances;
         DescendantDistances.reserve(Tree.GetNodes().size());

         for(const auto& Node : Tree.GetNodes())
         {
            const auto DescendantDistance{Tree.DescendantDistance(*Node.get(), DescendantDistanceOfInterest)};
            DescendantDistances.emplace_back(Node.get(), DescendantDistance);
         }

         std::ranges::sort(DescendantDistances,
                           [](const DescendantDistanceType& DescendantDistanceA, const DescendantDistanceType& DescendantDistanceB)
                           {
                              return DescendantDistanceA.second > DescendantDistanceB.second;
                           });

         int ThirdHighestScore{0};
         if(DescendantDistances.size() > 2)
         {
            ThirdHighestScore = DescendantDistances[2].second;
         }

         for(const DescendantDistanceType& DescendantDistance : DescendantDistances)
         {
            if(DescendantDistance.second >= ThirdHighestScore)
            {
               std::println("{} - {}", DescendantDistance.first->data, DescendantDistance.second);
            }
            else
            {
               break;
            }
         }
      }
   }

   std::println("Finished Input Processing");
}
