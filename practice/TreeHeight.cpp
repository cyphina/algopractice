#include <iostream>
#include <vector>

// This problem has a decent amount of constraints thus we should be careful to read them all. The values fit in integer ranges,
// and we can have an empty array as input.

using namespace std;

int visitNode(int NodeIndex, const vector<int>& LeftChild, const vector<int>& RightChild)
{
   // Since root is at 0, this means we've reached past the leaves.
   // Bottoms up so the child will give back 0 since we'll +1 at the parent.
   if(NodeIndex == -1)
   {
      return 0;
   }

   const auto LeftHeight{1 + visitNode(LeftChild[NodeIndex], LeftChild, RightChild)};
   const auto RightHeight{1 + visitNode(RightChild[NodeIndex], LeftChild, RightChild)};

   return std::max(LeftHeight, RightHeight);
}

int getBinarySearchTreeHeight(vector<int> values, vector<int> leftChild, vector<int> rightChild)
{
   if(values.empty())
   {
      return 0;
   }

   return visitNode(0, leftChild, rightChild);
}

int main()
{
   std::cout << getBinarySearchTreeHeight({}, {}, {}) << "\n";

   std::cout << getBinarySearchTreeHeight({4, 2, 6, 1, 3, 5, 7}, {1, 3, 5, -1, -1, -1, -1}, {2, 4, 6, -1, -1, -1, -1})
             << "\n";
}
