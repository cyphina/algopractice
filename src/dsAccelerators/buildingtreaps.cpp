#include "buildingtreaps.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include "core/SegmentTree.h"

namespace
{
   using SegmentTreeElemType = std::vector<BuildingTreaps::TreapNode>::iterator;
   struct SegmentTreeMerge
   {
      static SegmentTreeElemType operator()(const SegmentTreeElemType& NodeA, const SegmentTreeElemType& NodeB)
      {
         if(NodeA->Priority >= NodeB->Priority)
         {
            return NodeA;
         }
         return NodeB;
      };
   };

   using SegmentTreeType = SegmentTree::SegmentTree<SegmentTreeElemType, SegmentTreeMerge>;

   size_t FindHighestPriorityNodeIndexSlow(std::vector<BuildingTreaps::TreapNode>& TreapNodes, std::size_t L,
                                           std::size_t R)
   {
      const auto MaxElementIt{
          std::max_element(TreapNodes.begin() + L, TreapNodes.begin() + R,
                           [](const BuildingTreaps::TreapNode& First, const BuildingTreaps::TreapNode& Second)
                           {
                              return First.Priority < Second.Priority;
                           })};
      return std::distance(TreapNodes.begin(), MaxElementIt);
   }

   auto FindHighestPriorityNodeFast(std::vector<BuildingTreaps::TreapNode>& TreapNodes, const SegmentTreeType& Tree,
                                    std::size_t L, std::size_t R)
   {
      const auto Result{Tree.Query(L, R)};
      return Result.value();
   }

   void GenerateTreapStringRecursive(std::vector<BuildingTreaps::TreapNode>& TreapNodes, std::size_t L, std::size_t R,
                                     std::ostringstream& OStream)
   {
      if(L == R)
      {
         return;
      }

      const auto HighestPriorityNodeIndex{FindHighestPriorityNodeIndexSlow(TreapNodes, L, R)};

      OStream << "(";
      GenerateTreapStringRecursive(TreapNodes, L, HighestPriorityNodeIndex, OStream);
      OStream << TreapNodes[HighestPriorityNodeIndex].Label << "/" << TreapNodes[HighestPriorityNodeIndex].Priority;
      GenerateTreapStringRecursive(TreapNodes, HighestPriorityNodeIndex + 1, R, OStream);
      OStream << ")";
   }

   void GenerateTreapStringRecursive(std::vector<BuildingTreaps::TreapNode>& TreapNodes, const SegmentTreeType& SegTree,
                                     std::size_t L, std::size_t R, std::ostringstream& OStream)
   {
      if(L == R)
      {
         return;
      }

      const auto HighestPriorityNode{FindHighestPriorityNodeFast(TreapNodes, SegTree, L, R)};
      const auto HighestPriorityNodeIndex{std::distance(TreapNodes.begin(), HighestPriorityNode)};

      OStream << "(";
      GenerateTreapStringRecursive(TreapNodes, SegTree, L, HighestPriorityNodeIndex, OStream);
      OStream << TreapNodes[HighestPriorityNodeIndex].Label << "/" << TreapNodes[HighestPriorityNodeIndex].Priority;
      GenerateTreapStringRecursive(TreapNodes, SegTree, HighestPriorityNodeIndex + 1, R, OStream);
      OStream << ")";
   }
}

namespace BuildingTreaps
{
   bool TreapNode::operator==(const TreapNode& Other) const
   {
      return Label == Other.Label;
   }

   std::strong_ordering TreapNode::operator<=>(const TreapNode& Other) const
   {
      const auto Result{Label <=> Other.Label};
      return Result;
   }

   std::string GenerateTreapStringSlow(std::vector<TreapNode>& TreapNodes)
   {
      std::ranges::sort(TreapNodes);
      std::ostringstream OutStream;

      GenerateTreapStringRecursive(TreapNodes, 0, TreapNodes.size(), OutStream);

      return OutStream.str();
   }

   std::string GenerateTreapStringFast(std::vector<TreapNode>& TreapNodes)
   {
      std::ranges::sort(TreapNodes);
      std::vector<SegmentTreeElemType> SegmentTreeData;
      SegmentTreeData.reserve(TreapNodes.size());

      std::size_t Index{};
      // Guaranteed order for sequential execution
      // std::vector<SegmentTreeElemType> SegmentTreeData(TreapNodes.size());
      /*std::ranges::transform(TreapNodes, SegmentTreeData.begin(),
                             [&Index, &TreapNodes](const auto& TreapNode)
                             {
                                return TreapNodes.begin() + Index++;
                             });*/

      // Could also use {priority,index} and merge those properly.
      for(auto it = TreapNodes.begin(); it != TreapNodes.end(); ++it)
      {
         SegmentTreeData.push_back(it);
      }

      SegmentTreeType SegTree{SegmentTreeData};

      std::ostringstream OutStream;

      GenerateTreapStringRecursive(TreapNodes, SegTree, 0, TreapNodes.size(), OutStream);

      return OutStream.str();
   }
}
