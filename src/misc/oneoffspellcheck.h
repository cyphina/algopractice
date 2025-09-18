#pragma once
#include <optional>
#include <string_view>

namespace OneOffSpellCheck
{
   /**
    * Return a -open range [start,end) to indices in the larger string that can be removed.
    * Second string must be larger.
    */
   std::optional<std::pair<int, int>> IsStringOneOff(std::string_view FirstString, std::string_view SecondString);
}
