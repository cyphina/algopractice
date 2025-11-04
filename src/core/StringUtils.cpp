#include "StringUtils.h"

void StringUtils::Xor_Swap_Bytes(std::span<std::byte> A, std::span<std::byte> B)
{
   if(A.size() == B.size())
   {
      for(size_t i = 0; i < A.size(); ++i)
      {
         A[i] ^= B[i];
         B[i] ^= A[i];
         A[i] ^= B[i];
      }
   }
}

void StringUtils::Xor_Swap_LowLevel(unsigned char* A, size_t A_Len, unsigned char* B, size_t B_Len)
{
   size_t min_len = A_Len < B_Len ? A_Len : B_Len;

   for(size_t i = 0; i < min_len; ++i)
   {
      A[i] ^= B[i];
      B[i] ^= A[i];
      A[i] ^= B[i];
   }

   // Now handle leftover bytes from the longer string
   if(A_Len > B_Len)
   {
      // move the leftover bytes from a into b
      B = (unsigned char*)realloc(B, A_Len);
      memcpy(B + B_Len, A + B_Len, A_Len - B_Len);
      A[A_Len = B_Len] = '\0';
   }
   else if(B_Len > A_Len)
   {
      A = (unsigned char*)realloc(A, B_Len);
      memcpy(A + A_Len, B + A_Len, B_Len - A_Len);
      B[B_Len = A_Len] = '\0';
   }
}
