#include <vector>

namespace
{
   constexpr int SENTINEL = 100001;
}

// Inorder
void GetTreeValues(std::size_t NodeIndex, const std::vector<int>& Tree, std::vector<int>& Values)
{
   if(NodeIndex < Tree.size() && Tree[NodeIndex] != SENTINEL)
   {
      const auto LeftIndex{2 * NodeIndex + 1};
      const auto RightIndex{2 * NodeIndex + 2};

      GetTreeValues(LeftIndex, Tree, Values);

      Values.push_back(Tree[NodeIndex]);

      GetTreeValues(RightIndex, Tree, Values);
   }
}

// Preorder Type Processing
bool TestTreeStructure(std::size_t NodeIndex, const std::vector<int>& Tree1, const std::vector<int>& Tree2)
{
   bool Does1NotExist{NodeIndex >= Tree1.size() || Tree1[NodeIndex] == SENTINEL};
   bool Does2NotExist{NodeIndex >= Tree2.size() || Tree2[NodeIndex] == SENTINEL};

   if(Does1NotExist && Does2NotExist)
   {
      return true;
   }
   else if(Does1NotExist || Does2NotExist)
   {
      return false;
   }
   else
   {
      const auto LeftIndex{2 * NodeIndex + 1};
      const auto RightIndex{2 * NodeIndex + 2};

      return TestTreeStructure(LeftIndex, Tree1, Tree2) && TestTreeStructure(RightIndex, Tree1, Tree2);
   }
}

bool verifySameMultisetDifferentStructure(std::vector<int> root1, std::vector<int> root2)
{
   if(root1.empty() && root2.empty())
   {
      return false;
   }

   std::vector<int> Values1;
   std::vector<int> Values2;

   GetTreeValues(0, root1, Values1);
   GetTreeValues(0, root2, Values2);

   const auto MatchingStructure{TestTreeStructure(0, root1, root2)};

   return Values1 == Values2 && !MatchingStructure;
}

int main()
{
}
