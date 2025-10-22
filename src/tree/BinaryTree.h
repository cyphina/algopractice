#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace BinaryTree
{
   template <typename T>
   struct Node
   {
      T     data;
      Node* left;
      Node* right;
   };

   /**
    * A container for nodes to keep them alive while we do stuff
    * Sometimes code that provides nodes need to like do stuff with them across multiple functions so this is mainly for keeping the nodes alive
    * and other code can still reference individual nodes as needed.
    * It also provides a nicer interface to make nodes.
    */
   template <typename T>
   class BinaryTree
   {
      using NodeList = std::vector<std::unique_ptr<Node<T>>>;

    public:
      template <typename... Ts>
      void EmplaceNode(Ts&&... Args);

      void            AddNode(std::unique_ptr<Node<T>>&& Node);
      const NodeList& GetNodes() const { return nodes; }

    private:
      NodeList nodes;
   };

   template <typename T>
   template <typename... Ts>
   void BinaryTree<T>::EmplaceNode(Ts&&... Args)
   {
      auto NewNode{std::make_unique<Node<T>>(T{std::forward<Ts>(Args)...}, nullptr, nullptr)};
      nodes.push_back(std::move(NewNode));
   }

   template <typename T>
   void BinaryTree<T>::AddNode(std::unique_ptr<Node<T>>&& Node)
   {
      nodes.emplace_back(std::move(Node));
   }
}
