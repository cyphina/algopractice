#pragma once
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

      [[nodiscard]] auto operator<=>(const Node& rhs) const;
      [[nodiscard]] bool operator==(const Node& rhs) const;
      [[nodiscard]] bool operator==(const T& rhs) const;
   };

   template <typename T>
   struct NodeHash
   {
      // Transparent operators are heterogeneous and let us omit the template type argument.
      using is_transparent = void;

      size_t operator()(const std::unique_ptr<Node<T>>& Node) const { return std::hash<T>{}(Node->data); }
      size_t operator()(const T& Data) const { return std::hash<T>{}(Data); }
   };

   template <typename T>
   struct NodeEqual
   {
      using is_transparent = void;
      bool operator()(const std::unique_ptr<Node<T>>& Lhs, const std::unique_ptr<Node<T>>& Rhs) const { return Lhs->data == Rhs->data; }
      bool operator()(const T& Lhs, const std::unique_ptr<Node<T>>& Rhs) const { return Lhs == Rhs->data; }
   };

   template <typename T>
   class NaryTree
   {
    public:
      using NodeType = std::unique_ptr<Node<T>>;
      using NodeList = std::unordered_set<NodeType, NodeHash<T>, NodeEqual<T>>;

      // Use unique pointers to keep pointers valid for the tree even after the underlying data structure reallocates.
      Node<T>*        AddNode(const T& Data);
      const NodeList& GetNodes() const { return nodes; }
      const Node<T>*  FindNode(const T& Data);

    private:
      NodeList nodes;
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

   template <typename T>
   Node<T>* NaryTree<T>::AddNode(const T& Data)
   {
      const auto Result{nodes.emplace(std::make_unique<Node<T>>(Data))};
      return Result.second ? Result.first->get() : nullptr;
   }

   template <typename T>
   const Node<T>* NaryTree<T>::FindNode(const T& Data)
   {
      auto It{nodes.find(Data)};
      return It != nodes.end() ? (*It).get() : nullptr;
   }
}
