#include <print>
#include <stacktrace>

void PrintStackTrace()
{
   const std::stacktrace Trace{std::stacktrace::current()};
   std::println("{}", Trace);
}

int main()
{
   PrintStackTrace();
}
