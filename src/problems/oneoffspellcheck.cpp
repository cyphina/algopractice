#include "misc/oneoffspellcheck.h"
#include <print>

int main()
{
   const auto Result{OneOffSpellCheck::IsStringOneOff("abcdxxexxxf", "abcdxxexxf")};
   const auto Result2{OneOffSpellCheck::IsStringOneOff("abcdxxexxf", "abcdxxexxxf")};

   if(Result)
   {
      std::print("Lower Bound - {}, Upper Bound - {}", Result->first, Result->second);
   }

   if(Result2)
   {
      std::print("Lower Bound - {}, Upper Bound - {}", Result2->first, Result2->second);
   }
}
