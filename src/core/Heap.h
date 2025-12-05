#pragma once

#include <algorithm>
#include <concepts>
#include <print>
#include <utility>
#include <vector>

namespace Heap
{
   template <typename Comp, typename T>
   concept HeapComparator = std::totally_ordered<T> && std::predicate<Comp, T, T>;

   /**
    * @tparam T - Type we can compare using a HeapComparator
    * @tparam C - The comparison used to check if one element has lower priority than another. By default this leads to a min heap. 
    */
   template <std::totally_ordered T, HeapComparator<T> C = std::greater<>>
   class HeapWithSTL
   {
    public:
      explicit HeapWithSTL(std::vector<T>&& Data);
      T                     ExtractTop();
      void                  Insert(T Elem);
      void                  PrintData();
      const std::vector<T>& GetData() const { return data; }
      bool                  IsEmpty() const { return data.empty(); }
      size_t                Size() const { return data.size(); }

      std::vector<T> data;
   };

   /**
    * @tparam T - Type we can compare using a HeapComparator
    * @tparam C - The comparison used to check if one element has lower priority than another. By default this leads to a min heap. 
    */
   template <std::totally_ordered T, HeapComparator<T> C = std::greater<>>
   class Heap
   {
    public:
      explicit Heap(std::vector<T>&& Data);
      T                     ExtractTop();
      void                  Insert(T Elem);
      void                  PrintData();
      const std::vector<T>& GetData() const { return data; }
      bool                  IsEmpty() const { return data.empty(); }
      size_t                Size() const { return data.size(); }

    private:
      static size_t GetParentIndex(size_t NodeIndex) { return (NodeIndex - 1) / 2; }
      static size_t GetLeftChildIndex(size_t NodeIndex) { return 2 * NodeIndex + 1; }
      static size_t GetRightChildIndex(size_t NodeIndex) { return 2 * NodeIndex + 2; }

      C              comparator;
      std::vector<T> data;
   };

   template <std::totally_ordered T, HeapComparator<T> C>
   HeapWithSTL<T, C>::HeapWithSTL(std::vector<T>&& Data) : data{std::move(Data)}
   {
      std::ranges::make_heap(data, C{});
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   T HeapWithSTL<T, C>::ExtractTop()
   {
      std::ranges::pop_heap(data);
      const auto Largest{data.pop_back()};
      return Largest;
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   void HeapWithSTL<T, C>::Insert(T Elem)
   {
      std::ranges::push_heap(Elem);
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   void HeapWithSTL<T, C>::PrintData()
   {
      std::println("{}", data);
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   ::Heap::Heap<T, C>::Heap(std::vector<T>&& Data)
   {
      for(const auto& Elem : Data)
      {
         Insert(Elem);
      }
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   T Heap<T, C>::ExtractTop()
   {
      T Top{std::exchange(data.front(), data.back())};

      if(data.size() > 2)
      {
         size_t CurrentIndex{0};
         size_t LeftChildIndex{1};
         size_t RightChildIndex{2};
         size_t HigherPriorityIndex;

         bool ValidLeftChild{LeftChildIndex < data.size()};
         bool ValidRightChild{RightChildIndex < data.size()};

         while(ValidLeftChild || ValidRightChild)
         {
            if(!ValidRightChild)
            {
               HigherPriorityIndex = LeftChildIndex;
            }
            else
            {
               HigherPriorityIndex =
                   comparator(data[LeftChildIndex], data[RightChildIndex]) ? RightChildIndex : LeftChildIndex;
            }

            if(comparator(data[CurrentIndex], data[HigherPriorityIndex]))
            {
               std::swap(data[HigherPriorityIndex], data[CurrentIndex]);
            }
            else
            {
               break;
            }

            CurrentIndex = HigherPriorityIndex;

            LeftChildIndex  = GetLeftChildIndex(CurrentIndex);
            RightChildIndex = GetRightChildIndex(CurrentIndex);

            ValidLeftChild  = LeftChildIndex < data.size();
            ValidRightChild = RightChildIndex < data.size();
         }
      }

      data.pop_back();
      return Top;
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   void Heap<T, C>::Insert(T Elem)
   {
      data.push_back(Elem);
      size_t CurrentIndex{data.size() - 1};
      size_t ParentIndex{GetParentIndex(CurrentIndex)};

      while(CurrentIndex != 0 && comparator(data[GetParentIndex(CurrentIndex)], data[CurrentIndex]))
      {
         std::swap(data[CurrentIndex], data[ParentIndex]);
         CurrentIndex = ParentIndex;
         ParentIndex  = GetParentIndex(CurrentIndex);
      }
   }

   template <std::totally_ordered T, HeapComparator<T> C>
   void Heap<T, C>::PrintData()
   {
      std::println("{}", data);
   }
}
