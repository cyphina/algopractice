#include "LogUtils.h"

void LogUtils::LogMessages(std::string_view Message, const std::source_location& Location)
{
   std::println("{}({}): {}: {}", Location.file_name(), Location.line(), Location.function_name(), Message);
}
