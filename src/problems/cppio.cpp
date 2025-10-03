#include <filesystem>
#include <iostream>
#include <print>
#include <string>

void PrintDirectoryStructure(const std::filesystem::path& P)
{
   namespace fs = std::filesystem;

   if(!exists(P))
   {
      return;
   }

   fs::recursive_directory_iterator Begin{P};
   fs::recursive_directory_iterator End{};

   try
   {
      for(auto Iter{Begin}; Iter != End; ++Iter)
      {
         const std::string Spacer(Iter.depth() * 2, ' ');
         // Is a directory entry
         auto& Entry{*Iter};

         if(fs::is_regular_file(Entry))
         {
            println("{}File: {} ({} bytes)", Spacer, Entry.path().string(), fs::file_size(Entry));
         }
         else if(fs::is_directory(Entry))
         {
            println("{}Dir: {}", Spacer, Entry.path().string());
         }
      }
   }
   catch(std::exception E)
   {
      std::println("{}", E.what());
   }
}

int main()
{
   //int         wee;
   //std::string pee;
   //std::println(std::cout, "Input number and string");
   //std::cin >> wee >> pee;
   //std::println(std::cout, "{} {}", wee, pee);

   std::filesystem::path Path{R"(C:/Wee/Pee/Dee)"};

   for(const auto& Component : Path)
   {
      std::println("{}", Component.string());
   }

   std::println("Input a Directory Name");
   std::string TestPath;
   while(std::cin >> TestPath && TestPath != "!")
   {
      PrintDirectoryStructure(TestPath);
      std::println("Input a Directory Name or ! to Escape");
   }
}
