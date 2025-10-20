#include "HashUtils.h"

unsigned long HashUtils::oaat(const char* Key, unsigned long Len, unsigned long Bits)
{
   unsigned long hash, i;
   for(hash = 0, i = 0; i < Len; ++i)
   {
      hash += Key[i];
      hash += (hash << 10);
      hash ^= (hash >> 6);
   }

   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);
   return hash & hashmask(Bits);
}
