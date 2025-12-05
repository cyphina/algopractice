#include <expected>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>

void TestMonadicOptional()
{
   std::optional<int> Result;
   auto               Result2{Result.and_then(
       [](int Value) -> std::optional<int>
       {
          return Value * 2;
       })};
   auto               Result3{Result.transform(
       [](int Value)
       {
          return Value * 2;
       })};
   std::println("Result2: {}. Result3: {}", Result2.value_or(-1), Result3.value_or(-1));
}

std::expected<int, std::string> ParseIntegerString(const std::string& Str)
{
   try
   {
      return std::stoi(Str);
   }
   catch(const std::invalid_argument& e)
   {
      return std::unexpected{e.what()};
   }
   catch(const std::out_of_range& e)
   {
      return std::unexpected{e.what()};
   }
}

void TestIntegerString()
{
   const auto Result{ParseIntegerString("Wee")};
   if(Result.has_value())
   {
      std::println("Value: {}", Result.value());
   }
   else
   {
      std::println("Problem: {}", Result.error());
   }

   const auto Result2{ParseIntegerString("13141")};
   if(Result2.has_value())
   {
      std::println("Value: {}", Result2.value());
   }
   else
   {
      std::println("Problem: {}", Result2.error());
   }
}

int main()
{
   TestMonadicOptional();
   TestIntegerString();
}
