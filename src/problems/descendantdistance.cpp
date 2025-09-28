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
      std::println("Text Case Index {}", TestCaseIndex);

      size_t NumLinesToBuildTree{0}, DescendantDistanceOfInterest{0};
      std::cin >> NumLinesToBuildTree >> DescendantDistanceOfInterest;

      if(std::cin && NumLinesToBuildTree > 0)
      {
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

               if(!Tree.FindNode(NodeName))
               {
                  ParentNode = {Tree.AddNode(NodeType{NodeName})};
               }

               if(ParentNode)
               {
                  for(size_t j{0}; std::cin && j < NumChildren; ++j)
                  {
                     std::cin >> NodeName;
                     if(!Tree.FindNode(NodeName))
                     {
                        const auto ChildNode{Tree.AddNode(NodeType{NodeName})};
                        if(ParentNode && ChildNode)
                        {
                           ParentNode->children.emplace_back(ChildNode);
                        }
                     }
                  }
               }
            }
         }

         // Need to get descendant distance results

         for(const auto& Node : Tree.GetNodes())
         {
            std::println("{}", Node->data);
         }
      }
   }

   std::println("Finished Input Processing");
}
