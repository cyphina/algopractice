#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_set>

namespace NaryTree
{
   template <typename T>
   struct Node
   {
      T                  data;
      std::vector<Node*> children;

      size_t      GetNumChildren() const { return children.size(); }
      const Node* GetChildAt(uint32_t Index) const { return children[Index]; }

      [[nodiscard]] auto operator<=>(const Node& rhs) const;
      [[nodiscard]] bool operator==(const Node& rhs) const;
      [[nodiscard]] bool operator==(const T& rhs) const;
   };

   template <typename T, typename EdgeDataT>
   struct NodeWithEdge;

   template <typename NodeDataType, typename EdgeDataT>
   struct Edge
   {
      NodeWithEdge<NodeDataType, EdgeDataT>* Node{nullptr};
      std::optional<EdgeDataT>               Data;
   };

   template <typename T, typename EdgeDataT>
   struct NodeWithEdge
   {
      using EdgeType = Edge<T, EdgeDataT>;

      NodeWithEdge(const T& Data);

      T                     data;
      std::vector<EdgeType> children;

      size_t        GetNumChildren() const { return children.size(); }
      NodeWithEdge* GetChildAt(uint32_t Index) { return children[Index].Node; }

      [[nodiscard]] auto operator<=>(const NodeWithEdge& Rhs) const;
      [[nodiscard]] bool operator==(const NodeWithEdge& Rhs) const;
      [[nodiscard]] bool operator==(const T& Rhs) const;
   };

   template <typename T, typename NodeT>
   struct NodeHash
   {
      // Transparent operators are heterogeneous and let us omit the template type argument.
      using is_transparent = void;

      size_t operator()(const std::unique_ptr<NodeT>& Node) const { return std::hash<T>{}(Node->data); }
      size_t operator()(const T& Data) const { return std::hash<T>{}(Data); }
   };

   template <typename T, typename NodeT>
   struct NodeEqual
   {
      using is_transparent = void;
      bool operator()(const std::unique_ptr<NodeT>& Lhs, const std::unique_ptr<NodeT>& Rhs) const
      {
         return Lhs->data == Rhs->data;
      }
      bool operator()(const T& Lhs, const std::unique_ptr<NodeT>& Rhs) const { return Lhs == Rhs->data; }
   };

   enum class ENaryTreeMode
   {
      WithNoEdgeData,
      WithEdgeData,
   };

   /**
    * Lets you pass in a custom node type like a node with edges or a regular node. 
    */
   template <typename T, typename NodeT = Node<T>>
   class NaryTree
   {
    public:
      using NodeType = std::unique_ptr<NodeT>;
      //using NodeList = std::unordered_set<NodeType, NodeHash<T, NodeT>, NodeEqual<T, NodeT>>;
      using NodeList = std::vector<NodeType>;

      // Use unique pointers to keep pointers valid for the tree even after the underlying data structure reallocates.
      NodeT*          AddNode(const T& Data);
      const NodeList& GetNodes() const { return nodes; }
      NodeT*          FindNode(const T& Data);

      int DescendantDistance(const NodeT& Node, int DistanceTrack);

    private:
      NodeList nodes;
   };

   template <typename T>
   class NaryTreeWithEdgeData
   {
   };

   template <typename T>
   auto Node<T>::operator<=>(const Node& rhs) const
   {
      return data <=> rhs.data;
   }

   template <typename T>
   bool Node<T>::operator==(const Node& rhs) const
   {
      return data == rhs.data;
   }

   template <typename T>
   bool Node<T>::operator==(const T& rhs) const
   {
      return data == rhs;
   }

   template <typename T, typename EdgeDataT>
   NodeWithEdge<T, EdgeDataT>::NodeWithEdge(const T& Data)
   {
      data = Data;
   }

   template <typename T, typename EdgeDataT>
   auto NodeWithEdge<T, EdgeDataT>::operator<=>(const NodeWithEdge& Rhs) const
   {
      return data <=> Rhs.data;
   }

   template <typename T, typename EdgeDataT>
   bool NodeWithEdge<T, EdgeDataT>::operator==(const NodeWithEdge& Rhs) const
   {
      return data == Rhs.data;
   }

   template <typename T, typename EdgeDataT>
   bool NodeWithEdge<T, EdgeDataT>::operator==(const T& Rhs) const
   {
      return data == Rhs;
   }

   template <typename T, typename NodeT>
   NodeT* NaryTree<T, NodeT>::AddNode(const T& Data)
   {
      const auto& Result{nodes.emplace_back(std::make_unique<NodeT>(Data))};
      return Result ? Result.get() : nullptr;
   }

   template <typename T, typename NodeT>
   NodeT* NaryTree<T, NodeT>::FindNode(const T& Data)
   {
      auto It{nodes.find(Data)};
      return It != nodes.end() ? (*It).get() : nullptr;
   }

   template <typename T, typename NodeT>
   int NaryTree<T, NodeT>::DescendantDistance(const NodeT& Node, int DistanceTrack)
   {
      if(DistanceTrack == 1)
      {
         return Node.GetNumChildren();
      }

      int DescendantDistanceSum{0};
      for(int i = 0; i < Node.GetNumChildren(); ++i)
      {
         DescendantDistanceSum += DescendantDistance(*Node.GetChildAt(i), DistanceTrack - 1);
      }

      return DescendantDistanceSum;
   }

}
