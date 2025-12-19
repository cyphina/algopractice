#pragma once

#include <cassert>
#include <cstddef>
#include <optional>
#include <print>
#include <vector>

namespace SegmentTree
{

   template <typename T>
   struct SegmentTreeNode
   {
      std::size_t Left{}, Right{};
      T           Value;
   };

   template <typename Merge, typename T>
   concept Mergeable = std::invocable<Merge, const T&, const T&> &&
                       std::convertible_to<std::invoke_result_t<Merge, const T&, const T&>, T>;

   template <typename T>
   struct MaxMerge
   {
    public:
      static T operator()(const T& A, const T& B) { return std::max(A, B); }
   };

   /**
    * Full binary tree where each node is associated with a particular segment of an underlying array.
    * Useful to solve problems like range queries (max, min, sum, etc.) and has an update cost of O(log n) which is better than updating a prefix sum O(n) granted its lookup cost is worse.
    *
    * Can be used in ranges with continous data (times, distances) if you discretize it.
    */
   template <typename DataT = int, Mergeable<DataT> MergeOp = MaxMerge<DataT>>
   class SegmentTree
   {
    public:
      /**
       * Takes in the inital range to build a segment tree from.
       */
      SegmentTree(const std::vector<DataT>& Values);

      DataT Query(std::size_t LeftIndex, std::size_t RightIndex);

      const std::vector<SegmentTreeNode<DataT>>& GetData() const { return data; }

      void Print() const;

    private:
      static size_t GetLeftChildIndex(size_t NodeIndex) { return 2 * NodeIndex + 1; }
      static size_t GetRightChildIndex(size_t NodeIndex) { return 2 * NodeIndex + 2; }

      void InitSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex, std::size_t LeftIndex,
                       std::size_t RightIndex);
      void FillSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex);

      void Print(std::size_t NodeIndex) const;

      std::vector<std::optional<SegmentTreeNode<DataT>>> data;
      MergeOp                                            merge;
   };

   template <typename DataT, Mergeable<DataT> MergeOp>
   SegmentTree<DataT, MergeOp>::SegmentTree(const std::vector<DataT>& Values)
   {
      if(!Values.empty())
      {
         // This segment tree is stored in a heap-like array and is not a full binary tree.
         // Some child nodes may be placeholders that do not correspond to any range in the
         // original array. Such nodes must behave as identity elements so that merging them
         // does not affect the result, thus we test here that the default constructed value type for elements
         // act as identity values when merging.
         assert(merge(DataT{}, Values[0]) == Values[0]);
         // 4x the size of our input for safety to prevent accessing indices outside of our data bounds when recursion. Lets us avoid some size checks.
         data.resize(Values.size() * 4);
         InitSegtree(Values, 0, 0, Values.size());
         FillSegtree(Values, 0);
      }
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   DataT SegmentTree<DataT, MergeOp>::Query(std::size_t LeftIndex, std::size_t RightIndex)
   {
      return {};
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::Print() const
   {
      if(data.empty())
      {
         return;
      }

      std::print("[{}", data[0]->Value);

      Print(GetLeftChildIndex(0));
      Print(GetRightChildIndex(0));

      std::print("]", data[0]->Value);
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::Print(std::size_t NodeIndex) const
   {
      const auto& Node{data[NodeIndex]};

      if(Node.has_value())
      {
         if(Node->Left + 1 >= Node->Right)
         {
            std::print(" {}", data[NodeIndex]->Value);
            return;
         }

         std::print(" {}", data[NodeIndex]->Value);

         Print(GetLeftChildIndex(NodeIndex));
         Print(GetRightChildIndex(NodeIndex));
      }
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::InitSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex,
                                                 std::size_t LeftIndex, std::size_t RightIndex)
   {
      // We need to avoid NodeIndex.Left = Values.size() for the filling of the seg tree which happens with this logic and half open ranges.

      size_t Mid{(LeftIndex + RightIndex) / 2};

      data[NodeIndex]        = SegmentTreeNode<DataT>{};
      data[NodeIndex]->Left  = LeftIndex;
      data[NodeIndex]->Right = RightIndex;

      if(LeftIndex + 1 >= RightIndex)
      {
         return;
      }

      const auto LeftChildIndex{GetLeftChildIndex(NodeIndex)};
      const auto RightChildIndex{GetRightChildIndex(NodeIndex)};

      InitSegtree(Values, LeftChildIndex, LeftIndex, Mid);
      InitSegtree(Values, RightChildIndex, Mid, RightIndex);
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::FillSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex)
   {
      auto& Node{data[NodeIndex]};

      if(!Node.has_value())
      {
         return;
      }

      if(Node->Left + 1 >= Node->Right)
      {
         Node->Value = Values[Node->Left];
      }
      else
      {
         const auto LeftChildIndex{GetLeftChildIndex(NodeIndex)};
         const auto RightChildIndex{GetRightChildIndex(NodeIndex)};

         FillSegtree(Values, LeftChildIndex);
         FillSegtree(Values, RightChildIndex);

         const auto& Left{data[LeftChildIndex]};
         const auto& Right{data[RightChildIndex]};

         Node->Value = merge(Left->Value, Right->Value);
      }
   }
}
