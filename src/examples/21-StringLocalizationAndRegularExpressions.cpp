#include <format>
#include <iostream>
#include <print>

namespace
{
   void DoSomething(const char8_t* MyUTF8String)
   {
      std::println("Have a UTF8 thing here - {}", reinterpret_cast<const char*>(MyUTF8String));
   }

   void TestEncodedStringLiterals()
   {
      const auto s1{"\262"};
      const auto s2{u8"\262"};
      const auto s3{L"\262"};
      const char s4[]{u8"こんに"};

      // Can't mix and match
      std::println("{}", s1);
      std::wcout << std::format(L"{}", s3) << std::endl;

      // Use char_x types for APIs to narrow down what encoding we have.
      DoSomething(s2);
      std::println("{}", s4);
   }

   void TestEscapeSequences()
   {
      const char s1[]{u8"\300"};
#if __cpp_named_character_escapes
      const char s2[]{u8"\N{SUPERSCRIPT TWO}"};
#else
      const char s2[]{u8"NO SUPERSCRIPT SUPPORT"};
#endif
      const char s3[]{u8"\x236A"};
      const char s4[]{u8"\o{236A}"};

      std::println("Escape Sequences - {} {}, {}, {}", s1, s2, s3, s4);
   }
}

int main()
{
   TestEncodedStringLiterals();
   TestEscapeSequences();
}
