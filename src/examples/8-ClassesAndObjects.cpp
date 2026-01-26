#include <memory>
#include <string>

class Person
{
   Person(std::string_view First, std::string_view Last) : first{First}, last{Last} {}

   void SetFirst(std::string_view First);
   void SetLast(std::string_view Last);

   const std::string& GetFirst() const { return first; }
   const std::string& GetLast() const { return last; }

 private:
   std::string first;
   std::string last;
};

int main()
{
   const auto PersonA{std::make_unique<Person>("Zi", "Ha")};
   const autom PersonB{"Zi", "Ha"};
}
