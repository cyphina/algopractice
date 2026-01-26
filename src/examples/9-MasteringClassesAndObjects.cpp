#include <print>

class Foo2
{
 public:
   void Test();
};

class Bar
{
   friend class Foo;
   // Needs complete type
   friend void Foo2::Test();

 private:
   int Thing{5};
};

class Foo
{
   void Test()
   {
      Bar b;
      std::println("Foo {}", b.Thing);
   }
};

void Foo2::Test()
{
   Bar b;
   std::println("Foo 2 {}", b.Thing);
}

int main()
{
   Foo2 F;
   F.Test();
}
