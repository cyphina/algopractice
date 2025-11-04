#pragma once

#include <assert.h>
#include <memory>
#include <optional>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace Graphs
{
   enum class EdgeType : uint8_t
   {
      Directed,
      Undirected
   };

   template <typename T>
   struct Edge;

   template <typename T>
   struct Node
   {
      T                    Data;
      std::vector<Edge<T>> Edges;
   };

   template <typename T>
   struct Edge
   {
      Node<T>*                Node{nullptr};
      std::optional<uint32_t> Cost;
   };

   struct GraphEdgeData
   {
      uint16_t                FromIndex{};
      uint16_t                ToIndex{};
      std::optional<uint32_t> Cost;
      EdgeType                Type{EdgeType::Directed};
   };

   /**
    * Keeps the nodes alive as we pass stuff along.
    * And it can provide some functions useful on graphs too.
    */
   template <typename T>
   class Graph
   {
    public:
      using NodeType = Node<T>;
      // We'll just use unique pointer and have to invalidate dangling pointers when we remove.
      // If we stored regular nodes our pointers might be invalidated as the vector resizes.
      using NodeList = std::vector<std::unique_ptr<Node<T>>>;

      Graph() = default;
      Graph(const std::vector<T>&& NodeData, std::vector<GraphEdgeData>&& EdgeData);

      template <typename... Ts>
      Node<T>* EmplaceNode(Ts&&... Args);
      Node<T>* InsertNode(const Node<T>& NewNode);

      void AddDirectedEdge(Node<T>* A, Node<T>* B, std::optional<uint32_t> Cost = {});
      void AddUndirectedEdge(Node<T>* A, Node<T>* B, std::optional<uint32_t> Cost = {});

      void RemoveNode(const std::unique_ptr<Node<T>>& Node);

      const NodeList& GetNodes() const { return nodes; }

    private:
      NodeList nodes;
   };

   template <typename T>
   void Graph<T>::AddDirectedEdge(Node<T>* A, Node<T>* B, std::optional<uint32_t> Cost)
   {
      A->Edges.emplace_back(B, Cost);
   }

   template <typename T>
   void Graph<T>::AddUndirectedEdge(Node<T>* A, Node<T>* B, std::optional<uint32_t> Cost)
   {
      A->Edges.emplace_back(B, Cost);
      B->Edges.emplace_back(A, Cost);
   }

   template <typename T>
   Node<T>* Graph<T>::InsertNode(const Node<T>& NewNode)
   {
      nodes.push_back(std::move(std::make_unique<Node<T>>(std::move(NewNode))));
      return nodes.back().get();
   }

   template <typename T>
   void Graph<T>::RemoveNode(const std::unique_ptr<Node<T>>& Node)
   {
      nodes.erase(Node);
   }

   template <typename T>
   Graph<T>::Graph(const std::vector<T>&& NodeData, std::vector<GraphEdgeData>&& EdgeData)
   {
      for(uint32_t i{0}; i < NodeData.size(); ++i)
      {
         EmplaceNode(NodeData[i]);
      }

      const auto& Nodes{GetNodes()};

      for(const auto& [FromIndex, ToIndex, Cost, Type] : EdgeData)
      {
         switch(Type)
         {
            case EdgeType::Directed:
            {
               AddDirectedEdge(Nodes[FromIndex].get(), Nodes[ToIndex].get(), Cost);
               break;
            }
            case EdgeType::Undirected:
            {
               AddUndirectedEdge(Nodes[FromIndex].get(), Nodes[ToIndex].get(), Cost);
               break;
            }
         }
      }
   }

   template <typename T>
   template <typename... Ts>
   Node<T>* Graph<T>::EmplaceNode(Ts&&... Args)
   {
      auto& NewNode{nodes.emplace_back(std::move(std::make_unique<Node<T>>(Node<T>(T{std::forward<Ts>(Args)...}))))};
      return NewNode.get();
   }
}
