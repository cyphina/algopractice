#pragma once

#include <concepts>
#include <optional>
#include <unordered_map>
#include <vector>

namespace DisjointSet
{
   template <typename Key>
   concept DisjointSetKey = requires(Key K) {
      { std::hash<Key>{}(K) } -> std::convertible_to<std::size_t>;
      { K == K } -> std::convertible_to<bool>;
   };

   template <DisjointSetKey Key>
   class DisjointSet
   {
    public:
      DisjointSet() : MaxCommunitySize(std::numeric_limits<std::size_t>::max()) {}
      DisjointSet(std::size_t MaxCommunitySize) : MaxCommunitySize{MaxCommunitySize} {}

      void               Add(const Key& Id);
      std::optional<Key> FindRepresentative(const Key& Id);
      void               Unite(const Key& A, const Key& B);
      bool               Same(const Key& A, const Key& B);
      /**
       * Returns 0 if we don't query a representative.
       */
      size_t Size(const Key& Id);

    private:
      struct DisjointSetNode
      {
         Key    Parent{};
         size_t Size{};
         // TODO: I think it's used when you want to keep the tree balanced. You can use path compression and union by size
         // but I guess paths between nodes you don't hit can go out of wack apparently.
         size_t Rank{};
      };

      size_t                                                                    MaxCommunitySize{};
      std::unordered_map<Key, DisjointSetNode, std::hash<Key>, std::equal_to<>> Data;
   };

   template <DisjointSetKey Key>
   void DisjointSet<Key>::Add(const Key& Id)
   {
      Data.emplace(Id, DisjointSetNode{Id, 1, 0});
   }

   template <DisjointSetKey Key>
   std::optional<Key> DisjointSet<Key>::FindRepresentative(const Key& Id)
   {
      if(const auto IdNodeIt{Data.find(Id)}; IdNodeIt != Data.end())
      {
         auto  CurrentKey{Id};
         auto& CurrentKeyNode{Data.at(CurrentKey)};

         while(CurrentKeyNode.Parent != CurrentKey)
         {
            CurrentKey     = CurrentKeyNode.Parent;
            CurrentKeyNode = Data.at(CurrentKey);
         }

         const auto& Representative{CurrentKeyNode};

         // Path compression
         CurrentKey     = Id;
         CurrentKeyNode = Data.at(CurrentKey);

         while(CurrentKeyNode.Parent != Representative.Parent)
         {
            CurrentKeyNode.Parent = Representative.Parent;
            CurrentKey            = CurrentKeyNode.Parent;
            CurrentKeyNode        = Data.at(CurrentKey);
         }

         return Representative.Parent;
      }

      return {};
   }

   template <DisjointSetKey Key>
   void DisjointSet<Key>::Unite(const Key& A, const Key& B)
   {
      const auto AKey{FindRepresentative(A)};
      const auto BKey{FindRepresentative(B)};

      if(AKey.has_value() && BKey.has_value())
      {
         if(AKey == BKey)
         {
            return;
         }

         DisjointSetNode& ANode{Data.at(AKey.value())};
         DisjointSetNode& BNode{Data.at(BKey.value())};

         const auto ASize{ANode.Size};
         const auto BSize{BNode.Size};
         const auto CombinedSize{ASize + BSize};

         // Union by Size
         if(CombinedSize < MaxCommunitySize)
         {
            if(ASize < BSize)
            {
               ANode.Parent = BKey.value();
               BNode.Size   = CombinedSize;
            }
            else
            {
               BNode.Parent = AKey.value();
               ANode.Size   = CombinedSize;
            }
         }
      }
   }

   template <DisjointSetKey Key>
   bool DisjointSet<Key>::Same(const Key& A, const Key& B)
   {
      const auto AKey{FindRepresentative(A)};
      const auto BKey{FindRepresentative(B)};

      if(AKey.has_value() && BKey.has_value())
      {
         if(AKey == BKey)
         {
            return true;
         }
      }

      return false;
   }

   template <DisjointSetKey Key>
   size_t DisjointSet<Key>::Size(const Key& Id)
   {
      if(const auto It{Data.find(Id)}; It != Data.end())
      {
         if(It->second.Parent == Id)
         {
            return It->second.Size;
         }
      }
      return 0;
   }
}
