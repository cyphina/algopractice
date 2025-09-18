#include <print>
#include <stack>
#include <variant>
#include "tree/BinaryTree.h"

namespace
{
   using NodeType = BinaryTree::Node<std::variant<std::monostate, int>>;
}

void InorderTraversalStack(const NodeType& RootNode)
{
   std::stack<const NodeType*> S;
   const NodeType*             CurrentNode{&RootNode};

   while(!S.empty() || CurrentNode)
   {
      while(CurrentNode)
      {
         S.push(CurrentNode);
         CurrentNode = CurrentNode->left;
      }

      CurrentNode = S.top();
      S.pop();

      std::visit(
          [](auto&& arg)
          {
             using T = std::decay_t<decltype(arg)>;
             if constexpr(std::is_same_v<T, int>)
             {
                std::println("Node: {}", arg);
             }
             else
             {
             }
          },
          CurrentNode->data);

      CurrentNode = CurrentNode->right;
   }
}

int main()
{
   BinaryTree::BinaryTree<std::variant<std::monostate, int>> Tree;

   //NodeType House{4};
   //NodeType House2{9};
   //NodeType House3{15};
   //NodeType RouteB{{}, &House, &House2};
   //NodeType RouteC{{}, &RouteB, &House3};

   NodeType A{1};
   NodeType B{2};
   NodeType C{3};
   NodeType D{4};
   NodeType E{5};
   NodeType F{6};
   NodeType G{7};
   NodeType H{8};
   NodeType I{9};

   A.left  = &B;
   A.right = &C;

   B.left  = &D;
   B.right = &E;

   E.left  = &H;
   E.right = &I;

   C.left  = &F;
   C.right = &G;

   InorderTraversalStack(A);
}
