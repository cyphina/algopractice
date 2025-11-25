#pragma once

#include <print>
#include <source_location>
#include <string_view>

namespace LogUtils
{
   void LogMessages(std::string_view Message, const std::source_location& Location = std::source_location::current());
}
