#include <iostream>
#include <locale>
#include <print>
#include <sstream>
#include <stack>
#include <string>
#include <variant>
#include "tree/BinaryTree.h"

namespace
{
   using NodeValueType = std::variant<std::monostate, int>;
   using NodeType      = BinaryTree::Node<NodeValueType>;

}

struct NodePrinter
{
   void operator()(int value) const { std::print("Node: {}", value); }

   void operator()(const auto& other) const { std::print("Node: [non-int type]"); }
};

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

      std::visit(NodePrinter{}, CurrentNode->data);
      std::cout << "\n";

      CurrentNode = CurrentNode->right;
   }
}

int ChildOnlyTraversal(const NodeType* Node)
{
   if(Node)
   {
      if(!Node->left && !Node->right)
      {
         return 1;
      }
      return 1 + ChildOnlyTraversal(Node->left) + ChildOnlyTraversal(Node->right);
   }
   return 0;
}

int LeafOnlyTraversal(const NodeType* Node)
{
   if(Node)
   {
      if(!Node->left && !Node->right)
      {
         return 1;
      }
      else
      {
         return LeafOnlyTraversal(Node->left) + LeafOnlyTraversal(Node->right);
      }
   }
   return 0;
}

int CalculateHeight(const NodeType* Node)
{
   if(Node)
   {
      if(!Node->left && !Node->right)
      {
         return 0;
      }
      return 1 + std::max(CalculateHeight(Node->left), CalculateHeight(Node->right));
   }
   return 0;
}

int CalculateReturnToRootFullWalk(const NodeType* Node)
{
   if(Node)
   {
      const auto NumVisits{(Node->left ? 2 : 0) + (Node->right ? 2 : 0)};
      return NumVisits + CalculateReturnToRootFullWalk(Node->left) + CalculateReturnToRootFullWalk(Node->right);
   }
   return 0;
}

void PrintTree(const BinaryTree::BinaryTree<NodeValueType>& Tree)
{
   for(const auto& Node : Tree.GetNodes())
   {
      std::visit(NodePrinter{}, Node->data);
      if(Node->left)
      {
         std::print(" ");
         std::visit(NodePrinter{}, Node->left->data);
      }

      if(Node->right)
      {
         std::print(" ");
         std::visit(NodePrinter{}, Node->right->data);
      }
      std::cout << "\n";
   }
}

BinaryTree::BinaryTree<NodeValueType> ReadTree()
{
   std::println("Read Tree - Example Format ((4 9) 15)");

   BinaryTree::BinaryTree<NodeValueType> Tree;
   std::string                           DigitBuffer;
   std::string                           TreeDescription;
   char                                  Next{};
   NodeType*                             CurrentNode;
   std::stack<NodeType*>                 NodeStack;

   Next = std::cin.get();

   if(Next != '(' && std::cin)
   {
      std::print("Tree should start with (");
   }
   else
   {
      std::unique_ptr<NodeType> NewNode{std::make_unique<NodeType>()};
      CurrentNode = NewNode.get();
      Tree.AddNode(std::move(NewNode));
   }

   while(CurrentNode)
   {
      std::cin.get(Next);

      if(!std::cin)
      {
         std::println("Error getting next character");
      }

      if(Next == '(')
      {
         NodeStack.push(CurrentNode);
         std::unique_ptr<NodeType> NewNode{std::make_unique<NodeType>()};

         if(!CurrentNode->left)
         {
            CurrentNode->left = NewNode.get();
         }
         else
         {
            CurrentNode->right = NewNode.get();
         }

         CurrentNode = NewNode.get();
         Tree.AddNode(std::move(NewNode));
      }
      else if(std::isdigit(Next))
      {
         DigitBuffer = Next;
         while(isdigit(static_cast<char>(std::cin.peek())))
         {
            if(!std::cin)
            {
               std::println("Error reading over digits");
            }

            DigitBuffer += std::cin.get();
         }

         const auto                Value{std::stoi(DigitBuffer)};
         std::unique_ptr<NodeType> NewNode{std::make_unique<NodeType>(Value)};

         if(!CurrentNode->left)
         {
            CurrentNode->left = NewNode.get();
         }
         else
         {
            CurrentNode->right = NewNode.get();
         }
         Tree.AddNode(std::move(NewNode));
      }
      else if(Next == ')')
      {
         if(!NodeStack.empty())
         {
            CurrentNode = NodeStack.top();
            NodeStack.pop();
         }
         else
         {
            CurrentNode = nullptr;
         }
      }
   }

   return Tree;
}

/**
 * Recursive Descent Parse
 */
NodeType* ReadTreeRecursiveImpl(std::istream& in, BinaryTree::BinaryTree<NodeValueType>& Tree)
{
   char                      Next;
   std::unique_ptr<NodeType> NewNode{nullptr};
   NodeType*                 NewNodePtr{nullptr};

   std::string Remaining;

   while(in.get(Next))
   {
      if(isdigit(Next))
      {
         std::string Number{Next};
         while(isdigit(static_cast<char>(in.peek())))
         {
            in.get(Next);
            Number += Next;
         }

         int Value{std::stoi(Number)};
         NewNode    = std::make_unique<NodeType>(Value);
         NewNodePtr = NewNode.get();

         Tree.AddNode(std::move(NewNode));
         return NewNodePtr;
      }
      else if(Next == '(')
      {
         NewNode    = std::make_unique<NodeType>();
         NewNodePtr = NewNode.get();
         // We'll let the tokenizing occuring in each subtree advance the stream.
         const auto LeftNode{ReadTreeRecursiveImpl(in, Tree)};
         const auto RightNode{ReadTreeRecursiveImpl(in, Tree)};

         NewNode->left  = LeftNode;
         NewNode->right = RightNode;
         Tree.AddNode(std::move(NewNode));
      }
      else if(Next == ')')
      {
         return NewNodePtr;
      }
   }

   return nullptr;
}

BinaryTree::BinaryTree<NodeValueType> ReadTreeRecursive()
{
   std::println("Read Tree - Example Format ((4 9) 15)");

   std::string Line;
   std::getline(std::cin, Line);
   BinaryTree::BinaryTree<NodeValueType> Tree;

   if(std::cin)
   {
      std::istringstream S{Line};
      ReadTreeRecursiveImpl(S, Tree);
   }

   return Tree;
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

   const auto Height{CalculateHeight(&A)};
   const auto FullWalkReturnToRoot{CalculateReturnToRootFullWalk(&A)};
   std::println("Num Nodes {}", ChildOnlyTraversal(&A));
   std::println("Num Leaves {}", LeafOnlyTraversal(&A));
   std::println("Height {}", Height);
   std::println("Return to Root Walk Max Distance {}", FullWalkReturnToRoot);
   std::println("Return to Root Walk Distance {}", FullWalkReturnToRoot - Height);

   const auto Tree2 = ReadTreeRecursive();
   PrintTree(Tree2);
   std::println("Num Nodes {}", ChildOnlyTraversal(Tree2.GetNodes()[0].get()));
}
