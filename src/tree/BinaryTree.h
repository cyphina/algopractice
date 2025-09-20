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

   /** A container for nodes to keep them alive while we do stuff */
   template <typename T>
   class BinaryTree
   {
      using NodeList = std::vector<std::unique_ptr<Node<T>>>;

    public:
      void            AddNode(std::unique_ptr<Node<T>>&& Node);
      const NodeList& GetNodes() const { return nodes; }

    private:
      NodeList nodes;
   };

   template <typename T>
   void BinaryTree<T>::AddNode(std::unique_ptr<Node<T>>&& Node)
   {
      nodes.emplace_back(std::move(Node));
   }
}
