#pragma once

#include <memory>
#include <vector>

namespace Graph
{
   template <typename T>
   struct Edge;

   template <typename T>
   struct Node
   {
      T                    Data;
      std::vector<Edge<T>> Edges;

      void AddEdge
   };

   template <typename T>
   struct Edge
   {
      uint32_t Cost;
      Node<T>* Node;
   };

   /**
    * Keeps the nodes alive as we pass stuff along.
    * And it can provide some functions useful on graphs too.
    */
   template <typename T>
   class Graph
   {
      // We'll just use unique pointer and have to invalidate when we
      using NodeList = std::vector<std::unique_ptr<Node<T>>>;

    public:
      template <typename... Ts>
      void EmplaceNode(Ts&&... Args);

      Node<T>* InsertNode(std::unique_ptr<Node<T>>&& Node);
      void     RemoveNode(const std::unique_ptr<Node<T>>& Node);

      const NodeList& GetNodes() const { return nodes; }

    private:
      NodeList nodes;
   };

   template <typename T>
   Node<T>* Graph<T>::InsertNode(std::unique_ptr<Node<T>>&& Node)
   {
      return nodes.insert(std::move(Node).get());
   }

   template <typename T>
   void Graph<T>::RemoveNode(const std::unique_ptr<Node<T>>& Node)
   {
      nodes.erase(Node);
   }

   template <typename T>
   template <typename... Ts>
   void Graph<T>::EmplaceNode(Ts&&... Args)
   {
      nodes.emplace_back(Node(T{Args...}, {}));
   }
}
