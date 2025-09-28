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
   class NaryTree
   {
    public:
      using NodeType = std::unique_ptr<Node<T>>;
      using NodeList = std::unordered_set<NodeType,>;

      // Use unique pointers to keep pointers valid for the tree even after the underlying data structure reallocates.
      Node<T>*        AddNode(const T& Data);
      const NodeList& GetNodes() const { return nodes; }
      const T*        FindNode(const T& Data);

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
   const T* NaryTree<T>::FindNode(const T& Data)
   {
      auto It{nodes.find(Data)};
      return It != nodes.end() ? &(*It) : nullptr;
   }
}

// Only use a global hash specialization if we're storing the actual node objects directly.
//namespace std
//{
//   template <typename T>
//   struct hash<std::unique_ptr<NaryTree::Node<T>>>
//   {
//      size_t operator()(const NaryTree::Node<T>& Node) const { return std::hash<T>{}(Node.data); }
//   };
//}
