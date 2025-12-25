#include <fstream>
#include <iostream>
#include <print>
#include <sstream>

namespace
{
   void TestOut()
   {
      // By default `ios::base_in` reads at start so stream pos is start. Initial value in stream is Hello.
      std::stringstream Stream("Hello");
      Stream << "Wee!";
      std::println("Overwrite from start with mode ios_base::in {}", Stream.str());
   }

   void TestSeekTell()
   {
      std::stringstream Stream{};
      Stream << "Hello!";

      const auto OldPos{Stream.tellp()};
      Stream.seekp(std::ios_base::beg);

      // Prints Yollo!
      Stream << "Yo";
      std::println("{}", Stream.str());

      // Prints Yollo!Mom
      Stream.seekp(OldPos);
      Stream << "Mom";

      std::println("{}", Stream.str());

      Stream.seekp(-3, std::ios_base::end);
      Stream << "Dad";

      // Prints Yollo!Dad
      std::println("{}", Stream.str());

      std::string Value;
      Stream >> Value;

      // Read to a variable.
      // Prints Yollo!Dad
      std::println("{}", Value);
   }

   void TestReadEntireFile()
   {
      // Check out Properties > Debugging > Working Directory to find location to put this.
      // Defaults to project dir aka where the vcxproj files are.
      std::ifstream InputFile{"test.txt"};
      if(InputFile.fail())
      {
         std::println(std::cerr, "Unable to open file for reading.");
         return;
      }

      std::string FileContents;
      std::getline(InputFile, FileContents, '\0');
      std::println("\"{}\"", FileContents);
   }
}

int main()
{
   TestOut();
   TestSeekTell();
   TestReadEntireFile();
}
