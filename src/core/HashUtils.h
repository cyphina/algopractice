#pragma once
#include <cstdint>
#include <functional>

namespace HashUtils
{
   constexpr unsigned long hashsize(unsigned long n)
   {
      return 1 << n;
   }

   constexpr unsigned long hashmask(unsigned long n)
   {
      return hashsize(n) - 1;
   }

   /**
    * One at a time aka oaat aka Jenkins's hash function.
    * Goal is to cause small changes in the keys' bits to cause a huge change in the key's hash function (via the blender).
    * That way we can spread elements across different buckets to prevent having to fall back to linear probing.
    *
    * This way we get less collisions unless we insert some huge number of keys with a pathological dataset designed to screw with this function.
    * Requires hash table to have a number of elements that is a power of 2.
    *
    * @param Key - Data we want to hash (like a string)
    * @param Len - Length of that data (length of the word)
    * @param Bits - Number of bits we want in the resulting hashcode. Basically our hash table should have 1 << NUM_BITS  buckets
    * since the max value of a hash code this returns is one less than 2 to the power of bits.
    */
   unsigned long oaat(const char* Key, unsigned long Len, unsigned long Bits);

   template <typename KeyType, typename BucketItemType, typename Hash = std::hash<KeyType>,
             class KeyEqual = std::equal_to<KeyType>>
   class HashTable
   {
    public:
      /**
       * Pair because with separate chaining we can have collisions in the same bucket.
       * Aka two items with different keys in same bucket so if we want the original key we need to store it */
      using Value_Type = std::pair<const KeyType, BucketItemType>;

      // Remember take an argument by value or by ref. Never do both or you get ambiguity since call by value can take any value type.
      BucketItemType* Find(const KeyType& FindKey);

      // Need another template parameter to get the perfect forawarding syntax even if we expect a BucketItem here.
      template <typename ItemType>
      BucketItemType& Insert(const KeyType& K, ItemType&& Item);

      template <class... ItemConstructorParams>
      BucketItemType& Emplace(const KeyType& K, ItemConstructorParams&&... Args);

      /**
       * Ensure enough buckets for N elements
       */
      void Reserve(size_t N);

    private:
      /**
       * Redistribute how many buckets you are mapping to to spread the same hash value over more slots.
       * Need to recompute indices for existing elements.
       * @param NewBucketCount 
       */
      void Rehash(size_t NewBucketCount);

      std::vector<std::list<Value_Type>> buckets;
      Hash                               hash;
      KeyEqual                           equals;
   };

   template <typename Key, typename BucketItem, typename Hash, class KeyEqual>
   BucketItem* HashTable<Key, BucketItem, Hash, KeyEqual>::Find(const Key& FindKey)
   {
      const auto& Bucket{buckets[hash(FindKey)]};

      for(const auto& Item : Bucket)
      {
         if(Item.first == FindKey)
         {
            return &Item;
         }
      }

      return nullptr;
   }

   template <typename Key, typename BucketItem, typename Hash, class KeyEqual>
   template <typename Item>
   BucketItem& HashTable<Key, BucketItem, Hash, KeyEqual>::Insert(const Key& K, Item&& Item)
   {
      return buckets[hash(K)].insert(Item);
   }

   template <typename Key, typename BucketItem, typename Hash, class KeyEqual>
   template <class... ItemConstructorParams>
   BucketItem& HashTable<Key, BucketItem, Hash, KeyEqual>::Emplace(const Key& K, ItemConstructorParams&&... Args)
   {
      return buckets[hash(K)].emplace(Args...);
   }

   template <typename Key, typename BucketItem, typename Hash, class KeyEqual>
   void HashTable<Key, BucketItem, Hash, KeyEqual>::Reserve(size_t N)
   {
   }

   template <typename Key, typename BucketItem, typename Hash, class KeyEqual>
   void HashTable<Key, BucketItem, Hash, KeyEqual>::Rehash(size_t NewBucketCount)
   {
   }
}
