#pragma once
#include <cstdint>

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
    * This way we get less collisions unless we insert some huge number of keys with a phatological dataset designed to screw with this function.
    * Requires hash table to have a number of elements that is a power of 2.
    */
   unsigned long oaat(char* Key, unsigned long Len, unsigned long Bits);
}
