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
      void                      remove_node_index(std::size_t node_index);

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
      template <typename DirectedGraph>
      class const_directed_graph_iterator_impl;

      using value_type      = T;
      using reference       = value_type&;
      using const_reference = const value_type&;
      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;
      using iterator        = const_directed_graph_iterator_impl<directed_graph>;
      using const_iterator  = const_directed_graph_iterator_impl<directed_graph>;

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
      const_reference operator[](std::size_t Index) const;

      // Same nodes, same structure. Order nodes added in does not matter.
      bool                      operator==(const directed_graph& rhs) const;
      void                      swap(directed_graph& other_graph) noexcept;
      [[nodiscard]] std::size_t size() const noexcept { return m_nodes.size(); }
      [[nodiscard]] std::size_t max_size() const noexcept { return m_nodes.max_size(); }
      [[nodiscard]] bool        empty() const noexcept { return m_nodes.empty(); }
      [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;

      // Even though these are type aliases for the same kind of iterator and we could get away with just the const overloads in terms of functionality, the STL
      // says we need nonconst versions too.
      iterator       begin() noexcept { return iterator{std::begin(m_nodes)}; }
      iterator       end() noexcept { return iterator(std::end(m_nodes)); }
      const_iterator begin() const noexcept { return const_iterator{std::begin(m_nodes)}; }
      const_iterator end() const noexcept { return const_iterator{std::end(m_nodes)}; }
      // Same as begin and end const
      const_iterator cbegin() const noexcept { return begin(); }
      const_iterator cend() const noexcept { return end(); }

    private:
      using node_container_type = std::vector<graph_node<T>>;

      // We jus provide one iterator type for both the const and non-const iterator since we don't want users to modify the values when iterating since node values must be unique.
      template <typename DirectedGraph>
      class const_directed_graph_iterator_impl
      {
       public:
         using value_type              = typename DirectedGraph::value_type;
         using difference_type         = std::ptrdiff_t;
         using iterator_category       = std::bidirectional_iterator_tag;
         using pointer                 = const value_type*;
         using reference               = const value_type&;
         using node_container_iterator = typename DirectedGraph::node_container_type::const_iterator;

         const_directed_graph_iterator_impl() = default;

         explicit const_directed_graph_iterator_impl(node_container_iterator it) : m_nodeIterator{it} {}

         reference operator*() const;
         pointer   operator->() const;

         const_directed_graph_iterator_impl& operator++();
         const_directed_graph_iterator_impl& operator++(int);
         const_directed_graph_iterator_impl& operator--();
         const_directed_graph_iterator_impl& operator--(int);

         bool operator==(const const_directed_graph_iterator_impl&) const = default;

       private:
         friend class directed_graph<value_type>;

         node_container_iterator m_nodeIterator;
      };

      typename node_container_type::iterator       find_node(const T& node_value);
      typename node_container_type::const_iterator find_node(const T& node_value) const;

      std::size_t get_index_of_node(typename node_container_type::const_iterator node) const noexcept;

      void remove_all_links_to(typename node_container_type::const_iterator node_iter);

      node_container_type m_nodes;
   };

   template <typename T>
   void graph_node<T>::remove_node_index(std::size_t node_index)
   {
      m_adjacentNodeIndices.erase(node_index);
      // since std::set doesn't let us modify its elements in place
      // so rebuild the set from scratch
      std::vector<std::size_t> indices(std::begin(m_adjacentNodeIndices), std::end(m_adjacentNodeIndices));
      std::for_each(std::begin(indices), std::end(indices),
                    [node_index](std::size_t& index)
                    {
                       if(index > node_index)
                       {
                          --index;
                       }
                    });
      m_adjacentNodeIndices.clear();
      m_adjacentNodeIndices.insert(std::begin(indices), std::end(indices));
   }

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
   bool directed_graph<T>::erase(const T& node_value)
   {
      auto iter{find_node(node_value)};
      if(iter == std::end(m_nodes))
      {
         return false;
      }

      remove_all_links_to(iter);
      m_nodes.erase(iter);
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
   template <typename DirectedGraph>
   typename directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::reference
   directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::operator*() const
   {
      // Return a pointer to the actal element so the compiler can aply8 -> to it to access the actual desired field
      return &m_nodeIterator->value();
   }

   template <typename T>
   template <typename DirectedGraph>
   typename directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::pointer
   directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::operator->() const
   {
      // Return a reference to the actual element.
      return m_nodeIterator->value();
   }

   template <typename T>
   template <typename DirectedGraph>
   typename directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>&
   directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::operator++()
   {
      ++m_nodeIterator;
      return *this;
   }

   template <typename T>
   template <typename DirectedGraph>
   typename directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>&
   directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::operator++(int)
   {
      auto oldIt{*this};
      ++*this;
      return oldIt;
   }

   template <typename T>
   template <typename DirectedGraph>
   typename directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>&
   directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::operator--()
   {
      --m_nodeIterator;
      return *this;
   }

   template <typename T>
   template <typename DirectedGraph>
   typename directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>&
   directed_graph<T>::const_directed_graph_iterator_impl<DirectedGraph>::operator--(int)
   {
      auto oldIt{*this};
      --*this;
      return oldIt;
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

   template <typename T>
   void directed_graph<T>::remove_all_links_to(typename node_container_type::const_iterator node_iter)
   {
      // try to find this index in every single node we have

      const std::size_t node_index{get_index_of_node(node_iter)};
      for(auto&& node : m_nodes)
      {
         node.remove_node_index(node_index);
      }
   }
}
