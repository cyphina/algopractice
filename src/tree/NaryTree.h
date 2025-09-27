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
      using NodeList = std::unordered_set<Node<T>>;

    public:
      void            AddNode(const Node<T>& Node);
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
   Node<T> NaryTree<T>::AddNode(const Node<T>& Node)
   {
      return nodes.emplace(Node);
   }

   template <typename T>
   const T* NaryTree<T>::FindNode(const T& Data)
   {
      auto It{nodes.find(Data)};
      return It != nodes.end() ? &(*It) : nullptr;
   }
}

namespace std
{
   template <typename T>
   struct hash<NaryTree::Node<T>>
   {
      size_t operator()(const NaryTree::Node<T>& Node) const { return std::hash<T>{}(Node.data); }
   };
}
