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

      std::optional<DataT> Query(std::size_t LeftIndex, std::size_t RightIndex) const;

      const std::vector<SegmentTreeNode<DataT>>& GetData() const { return data; }

      void Print() const;

    private:
      static size_t GetLeftChildIndex(size_t NodeIndex) { return 2 * NodeIndex + 1; }
      static size_t GetRightChildIndex(size_t NodeIndex) { return 2 * NodeIndex + 2; }

      void InitSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex, std::size_t LeftIndex,
                       std::size_t RightIndex);
      void FillSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex);

      std::optional<DataT> Query(std::size_t NodeIndex, std::size_t LeftIndex, std::size_t RightIndex) const;

      void Print(std::size_t NodeIndex) const;

      std::vector<SegmentTreeNode<DataT>> data;
      MergeOp                             merge;
   };

   template <typename DataT, Mergeable<DataT> MergeOp>
   SegmentTree<DataT, MergeOp>::SegmentTree(const std::vector<DataT>& Values)
   {
      if(!Values.empty())
      {
         // 4x the size of our input for safety to prevent accessing indices outside of our data bounds when recursion. Lets us avoid some size checks.
         data.resize(Values.size() * 4);
         InitSegtree(Values, 0, 0, Values.size());
         FillSegtree(Values, 0);
      }
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   std::optional<DataT> SegmentTree<DataT, MergeOp>::Query(std::size_t LeftIndex, std::size_t RightIndex) const
   {
      if(data.empty())
      {
         return {};
      }

      if(LeftIndex >= RightIndex)
      {
         return {};
      }

      const auto& RootNode{data[0]};

      if(RightIndex > RootNode.Right)
      {
         return {};
      }

      return Query(0, LeftIndex, RightIndex);
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   std::optional<DataT> SegmentTree<DataT, MergeOp>::Query(std::size_t NodeIndex, std::size_t LeftIndex,
                                                           std::size_t RightIndex) const
   {
      // Case 1 - Node's range is not in the query range.
      // [1,2) [2,3) - Right <= LeftIndex
      // [2,3) [1 2) - Left >= RightIndex
      const auto& Node{data[NodeIndex]};
      if(Node.Left >= RightIndex || Node.Right <= LeftIndex)
      {
         return {};
      }

      // Case 2 - Node's range exactly in query range
      if(Node.Left >= LeftIndex && Node.Right <= RightIndex)
      {
         return Node.Value;
      }

      // Case 3 - Node's range partially in query range.
      const auto LeftValue{Query(GetLeftChildIndex(NodeIndex), LeftIndex, RightIndex)};
      const auto RightValue{Query(GetRightChildIndex(NodeIndex), LeftIndex, RightIndex)};

      if(!LeftValue)
      {
         return RightValue;
      }
      if(!RightValue)
      {
         return LeftValue;
      }

      return merge(LeftValue.value(), RightValue.value());
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::Print() const
   {
      if(data.empty())
      {
         return;
      }

      std::print("[{}", data[0].Value);

      Print(GetLeftChildIndex(0));
      Print(GetRightChildIndex(0));

      std::print("]", data[0].Value);
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::Print(std::size_t NodeIndex) const
   {
      const auto& Node{data[NodeIndex]};

      if(Node.Left + 1 >= Node.Right)
      {
         std::print(" {}", Node.Value);
         return;
      }

      std::print(" {}", Node.Value);

      Print(GetLeftChildIndex(NodeIndex));
      Print(GetRightChildIndex(NodeIndex));
   }

   template <typename DataT, Mergeable<DataT> MergeOp>
   void SegmentTree<DataT, MergeOp>::InitSegtree(const std::vector<DataT>& Values, std::size_t NodeIndex,
                                                 std::size_t LeftIndex, std::size_t RightIndex)
   {
      // We need to avoid NodeIndex.Left = Values.size() for the filling of the seg tree which happens with this logic and half open ranges.

      size_t Mid{(LeftIndex + RightIndex) / 2};

      data[NodeIndex]       = SegmentTreeNode<DataT>{};
      data[NodeIndex].Left  = LeftIndex;
      data[NodeIndex].Right = RightIndex;

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

      if(Node.Left + 1 >= Node.Right)
      {
         Node.Value = Values[Node.Left];
      }
      else
      {
         const auto LeftChildIndex{GetLeftChildIndex(NodeIndex)};
         const auto RightChildIndex{GetRightChildIndex(NodeIndex)};

         FillSegtree(Values, LeftChildIndex);
         FillSegtree(Values, RightChildIndex);

         const auto& Left{data[LeftChildIndex]};
         const auto& Right{data[RightChildIndex]};

         Node.Value = merge(Left.Value, Right.Value);
      }
   }
}
