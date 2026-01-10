#pragma once

#include <algorithm>
#include <unordered_set>

namespace digraph
{
   template <typename T>
   class directed_graph;

   template <typename T>
   class graph_node
   {
    public:
      using adjacency_list_type = std::set<std::size_t>;

      explicit graph_node(directed_graph<T>* graph, T t) : m_graph{graph}, m_data{std::move(t)} {}
      [[nodiscard]] const T&    value() const noexcept { return m_data; }
      [[nodiscard]] auto&       get_adjacent_nodes_indices() { return m_adjacentNodeIndices; }
      [[nodiscard]] const auto& get_adjacent_indices() { return m_adjacentNodeIndices; }

    private:
      directed_graph<T>*  m_graph;
      T                   m_data;
      adjacency_list_type m_adjacentNodeIndices;
   };

   /** Directed graph that only allows unique elements */
   template <typename T>
   class directed_graph
   {
    public:
      // Value should not be in the graph yet.
      bool insert(T node_value);
      // Returns true if the give node value was erased, false otherwise.
      bool erase(const T& node_value);
      // Returns true if edge was successfully created, false otherwise.
      bool insert_edge(const T& from_node_value, const T& to_node_value);
      // Returns true if given edge was erased, false otherwise.
      bool erase_edge(const T& from_node_value, const T& to_node_value);
      // Remove all nodes from the graph
      void clear() noexcept;
      // No bounds checking
      const T& operator[](std::size_t Index) const;
      // Same nodes, same structure. Order nodes added in does not matter.
      bool                      operator==(const directed_graph& rhs) const;
      void                      swap(directed_graph& other_graph) noexcept;
      [[nodiscard]] std::size_t size() const noexcept;
      [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;

    private:
      using node_container_type = std::vector<graph_node<T>>;

      typename node_container_type::iterator       find_node(const T& node_value);
      typename node_container_type::const_iterator find_node(const T& node_value) const;

      std::size_t get_index_of_node(typename node_container_type::const_iterator node) const noexcept;

      node_container_type m_nodes;
   };

   template <typename T>
   bool directed_graph<T>::insert(T node_value)
   {
      auto iter{find_node(node_value)};
      if(iter != std::end(m_nodes))
      {
         return false;
      }

      m_nodes.emplace_back(this, std::move(node_value));
      return true;
   }

   template <typename T>
   bool directed_graph<T>::insert_edge(const T& from_node_value, const T& to_node_value)
   {
      auto& from{find_node(from_node_value)};
      auto& to{find_node(to_node_value)};

      if(from == std::end(m_nodes) || to == std::end(m_nodes))
      {
         return false;
      }

      const std::size_t to_index{get_index_of_node(to)};
      // Second value in pair is if the insertion worked
      return from->get_adjacent_nodes_indices().insert(to_index).second;
   }

   template <typename T>
   typename std::vector<graph_node<T>>::iterator directed_graph<T>::find_node(const T& node_value)
   {
      // can't use the const_cast pattern since a const iterator isn't just a iterator const but it's really some pointer like thing yielding const T&.
      return std::ranges::find_if(m_nodes,
                                  [&](const auto& node)
                                  {
                                     return node.value() == node_value;
                                  });
   }

   template <typename T>
   typename std::vector<graph_node<T>>::const_iterator directed_graph<T>::find_node(const T& node_value) const
   {
      return std::ranges::find_if(m_nodes,
                                  [&](const auto& node)
                                  {
                                     return node.value() == node_value;
                                  });
   }

   template <typename T>
   std::size_t directed_graph<T>::get_index_of_node(typename node_container_type::const_iterator node) const noexcept
   {
      return node - std::cbegin(m_nodes);
   }
}
