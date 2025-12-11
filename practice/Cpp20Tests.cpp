#include "DebugUtils.h"
#include <format>
#include <iostream>
#include <ranges>
#include <vector>

int main()
{
   const auto Range{std::views::iota(5, 20)};

   DebugUtils::PrintRange(Range);
}
