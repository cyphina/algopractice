#include <format>
#include <iostream>
#include <locale>
#include <print>
#include <sstream>

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
      // wchar_t literal
      const auto s3{L"\262"};
      // Since C++23 you can store this utf-8 in const char[] whicih is supported by format and print
      const char s4[]{u8"こんに"};

      // Can't mix and match
      std::println("{}", s1);
      std::wcout << std::format(L"{}", s3) << std::endl;

      // Use char_x types for APIs to narrow down what encoding we have. The STL doesn't let you use too many encodings except for perhaps
      // wchar_t and utf-8 stored in const char[].
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
      const char s4[]{u8"\o{236}"};

      std::println("Escape Sequences - {} {}, {}, {}", s1, s2, s3, s4);
   }

   void Print()
   {
      std::stringstream Stream;
      Stream << 32767;
      std::println("{}", Stream.str());
   }

   void TestLocale()
   {
      Print();
      std::locale::global(std::locale{"en-US"});
      Print();
   }

   void TestChangeLocaleForStream()
   {
      // Use the environment locale
      std::cout.imbue(std::locale{""});
      std::cout << "User's Locale: " << 32767 << std::endl;
      // Change Back
      std::cout.imbue(std::locale::classic());
   }

   void TestGlobalLocaleFormatSpecifier()
   {
      std::println("println() using classic locale: {}", 32767);
      std::println("println() using global locale: {:L}", 32767);
      // Specified locale
      std::cout << std::format(std::locale{"en-US"}, "format() with en-US locale: {:L}", 32767) << std::endl;
   }

   void TestCharacterClassificationAndConversion()
   {
      std::println("É {}", isupper(L'É', std::locale{"fr-FR"}));                     // True
      std::println("é {}", isupper(L'é', std::locale{"fr-FR"}));                     // False
      std::wcout << std::format(L"{}", toupper(L'é', std::locale{"fr-FR"})) << '\n'; // Prints É
   }

   void TestFacets()
   {
      std::locale LocUSEng{"en-US"};
      std::locale LocBritEng{"en-GB"};

      std::wstring Dollars{std::use_facet<std::moneypunct<wchar_t>>(LocUSEng).curr_symbol()};
      std::wstring Pounds{std::use_facet<std::moneypunct<wchar_t>>(LocBritEng).curr_symbol()};

      std::wcout << std::format(L"En Currency {}. GB Currency {}.", Dollars, Pounds) << "\n";
      std::wcout << std::format(L"En Currency {}. GB Currency {}.", Dollars, Pounds) << "\n";

      // Here's an examlpe of feature we can probably forget since it's not really used much but it's there.

      std::string                    Source{"March 25 2024"};
      std::istringstream             Str{Source.data()};
      std::ios_base::iostate         Err{std::ios_base::goodbit};
      std::tm                        Time;
      std::istreambuf_iterator<char> Last{};

      const auto TimeGetEn{std::use_facet<std::time_get<char>>(LocUSEng).get_monthname({Str}, {}, Str, Err, &Time)};

      if(Str && !(Err & std::ios_base::failbit))
      {
         std::println("En {}.", Time.tm_mon);

         if(TimeGetEn != Last)
         {
            std::println("Remaining Content");
            std::copy(TimeGetEn, Last, std::ostreambuf_iterator<char>(std::cout));
            std::cout << "\n";
         }
      }

      // Reset the stream
      Str.seekg(0);
      const auto TimeGetGB{std::use_facet<std::time_get<char>>(LocBritEng).get_monthname({Str}, {}, Str, Err, &Time)};
      if(Str && !(Err & std::ios_base::failbit))
      {
         std::println("GB {}.", Time.tm_mon);

         if(TimeGetGB != Last)
         {
            std::println("Remaining Content");
            std::copy(TimeGetGB, Last, std::ostreambuf_iterator<char>(std::cout));
            std::cout << "\n";
         }
      }
   }
}

int main()
{
   TestEncodedStringLiterals();
   TestEscapeSequences();
   TestLocale();
   TestChangeLocaleForStream();
   TestGlobalLocaleFormatSpecifier();
   TestCharacterClassificationAndConversion();
   TestFacets();
}
