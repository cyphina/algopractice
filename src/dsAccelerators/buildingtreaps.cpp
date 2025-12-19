#include "buildingtreaps.h"
#include <algorithm>
#include <sstream>

namespace
{
   size_t FindHighestPriorityNodeIndex(std::vector<BuildingTreaps::TreapNode>& TreapNodes, std::size_t L, std::size_t R)
   {
      const auto MaxElementIt{
          std::max_element(TreapNodes.begin() + L, TreapNodes.begin() + R,
                           [](const BuildingTreaps::TreapNode& First, const BuildingTreaps::TreapNode& Second)
                           {
                              return First.Priority < Second.Priority;
                           })};
      return std::distance(TreapNodes.begin(), MaxElementIt);
   }

   void GenerateTreapStringRecursive(std::vector<BuildingTreaps::TreapNode>& TreapNodes, std::size_t L, std::size_t R,
                                     std::ostringstream& OStream)
   {
      if(L == R)
      {
         return;
      }

      const auto HighestPriorityNodeIndex{FindHighestPriorityNodeIndex(TreapNodes, L, R)};

      OStream << "(";
      GenerateTreapStringRecursive(TreapNodes, L, HighestPriorityNodeIndex, OStream);
      OStream << TreapNodes[HighestPriorityNodeIndex].Label << "/" << TreapNodes[HighestPriorityNodeIndex].Priority;
      GenerateTreapStringRecursive(TreapNodes, HighestPriorityNodeIndex + 1, R, OStream);
      OStream << ")";
   }
}

namespace BuildingTreaps
{
   bool TreapNode::operator==(const TreapNode& Other) const
   {
      return Label == Other.Label;
   }

   auto TreapNode::operator<=>(const TreapNode& Other) const
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
}
