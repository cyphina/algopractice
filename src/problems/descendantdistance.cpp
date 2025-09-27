#include <compare>
#include <iostream>
#include <print>
#include "tree/NaryTree.h"

namespace
{
   using NodeType = NaryTree::Node<std::string>;
}

int main()
{
   std::println("Descendant Distance - Score is how many descendants a family member has at distance d (d edges below).");

   int NumInputs{0};
   std::cin >> NumInputs;

   if(std::cin)
   {
      int NumLinesToBuildTree{0}, DescendantDistanceOfInterest{0};
      std::cin >> NumLinesToBuildTree >> DescendantDistanceOfInterest;

      if(std::cin)
      {
         int                             NumChildren{0};
         std::string                     NodeName{0};
         NaryTree::NaryTree<std::string> Tree;

         for(size_t i{0}; std::cin && i < NumLinesToBuildTree; ++i)
         {
            // name of node, integer n, n children names
            std::cin >> NodeName >> NumChildren;
            if(std::cin)
            {
               Tree.AddNode(NodeType{NodeName});
               for(size_t j{0}; std::cin && j < NumChildren; ++j)
               {
                  std::cin >> NodeName;
                  if(!Tree.FindNode(NodeName))
                  {
                     Tree.AddNode(NodeType{NodeName});
                  }
               }
            }
         }
      }
   }
}
