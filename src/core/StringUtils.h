#pragma once

#include <span>

namespace StringUtils
{
   // Swaps data in ranges the views refer to.
   // A and B must be same size.
   void Xor_Swap_Bytes(std::span<std::byte> A, std::span<std::byte> B);

   // We need a and b to be two dynamically allocated buffers.
   // We'd never use this on a `std::string`, we'd just use `std::swap`.
   // Notice how you must null terminate manually, and you're responsible for freeing memory later.
   // And you can't append - you have to copy bytes somewhere.
   void Xor_Swap_LowLevel(unsigned char* A, size_t A_Len, unsigned char* B, size_t B_Len);
}
