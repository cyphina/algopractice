#include <concepts>
#include <functional>
#include <print>
#include <span>
#include <string>

namespace
{
   template <std::predicate<int, int> MatcherT, std::invocable<int, int> MatchHandlerT>
   void FindMatches(std::span<const int> Values1, std::span<const int> Values2, MatcherT Matcher, MatchHandlerT Handler)
   {
   }

   void TestMatches()
   {
      std::vector Values1{2, 5, 6, 9, 10, 1, 1};
      std::vector Values2{4, 4, 2, 9, 0, 3, 1};

      FindMatches(
          Values1, Values2,
          [](int Value1, int Value2) static
          {
             return Value1 == Value2;
          },
          [](int Value1, int Value2) static
          {
             std::println("Match {} {}", Value1, Value2);
          });
   }

   class Unit
   {
    public:
      Unit()          = default;
      virtual ~Unit() = default;

      // Avoid slicing since derived have different types and this isn't virtual
      // Also clang-tidy likes these to be public and up and front.
      Unit& operator=(const Unit& other)     = delete;
      Unit& operator=(Unit&& other) noexcept = delete;

      virtual void SetHealth(int Health) { health = Health; }

      static inline int mana{};
      int               health{};

    protected:
      // Callable only in derived. Avoid implicit conversion to base when passing around.
      Unit(const Unit& other)     = default;
      Unit(Unit&& other) noexcept = default;
   };

   class Hero : public Unit
   {
    public:
      Hero() = default;

      void SetHealth(int Health) override
      {
         std::println("Hero Set!");
         health = Health;
      }
   };

   class FunctorWithStaticCallOperator
   {
    public:
      static void operator()(int a, int b) { std::println("{} - {}", a, b); }
   };

   void FunctorWithStaticCallOperatorExample()
   {
      std::vector<int> V{1, 2, 3, 4, 5};
      for(int i{0}; i < V.size() - 1; ++i)
      {
         FunctorWithStaticCallOperator()(V[i], V[i + 1]);
      }
   }

   void PointerToMemberExample()
   {
      // In the future, use auto instead for convenience.
      void (Hero::*HealthSetter)(int){&Hero::SetHealth};
      Hero hero;
      (hero.*HealthSetter)(5);

      std::println("{}", hero.health);

      int Hero::* HealthValue{&Hero::health};
      hero.*HealthValue = 8;

      std::println("{}", hero.health);

      int* ManaValue{&Hero::mana};
      *ManaValue = 20;
      std::println("{}", Hero::mana);
   }

   template <std::input_iterator Iter, std::copy_constructible StartValue,
             std::invocable<const StartValue&, const StartValue&> Operation>
   auto AccumulateData(Iter begin, Iter end, const StartValue& startValue, Operation op)
   {
      auto Accumulated{startValue};
      for(Iter iter{begin}; iter != end; ++iter)
      {
         Accumulated = op(Accumulated, *iter);
      }
      return Accumulated;
   }

   double GeometricMean(std::span<const int> Values)
   {
      auto Mult{AccumulateData(std::cbegin(Values), std::cend(Values), 1, std::multiplies<int>{})};
      return pow(Mult, 1.0 / Values.size());
   }

   void STLFunctorExample()
   {
      std::vector V{1, 2, 3, 4, 5};
      std::println("{}", GeometricMean(V));
   }

   class MoveOnlyFunctor
   {
    public:
      explicit MoveOnlyFunctor(std::unique_ptr<Hero> Hero) : hero{std::move(Hero)} {}
      void operator()(int Param) const noexcept
      {
         if(hero)
         {
            std::println("Wee {} {}", Param, hero->health);
         }
      }

    private:
      std::unique_ptr<Hero> hero;
   };

   void MoveOnlyFunctionExample()
   {
      MoveOnlyFunctor                                   M{std::make_unique<Hero>()};
      std::move_only_function<void(int) const noexcept> MoveOnlyFunction{std::move(M)};
      MoveOnlyFunction(200);
   }
}

template <typename T>
concept Addable = requires(T a, T b) {
   { a + b } -> std::convertible_to<T>;
};

void TestEverythingLambda()
{
   struct Widget
   {
      int         Value;
      std::string Name;
   };

   int    SomeNumber{42};
   Widget MyWidget{100, "MyWidget"};

   auto my_lambda = [SomeNumber, &MyWidget]<typename T>
      requires Addable<T>
   [[nodiscard]] (T x) /* static */ mutable noexcept(noexcept(x + x)) -> T
   {
      SomeNumber += 10;
      MyWidget.Value = 999;

      auto Result = x + x;
      return Result;
   };

   int Result = my_lambda(5);
   std::println("Everything Lambda Result - {}", Result);
}

int main()
{
   TestMatches();
   PointerToMemberExample();
   FunctorWithStaticCallOperatorExample();
   STLFunctorExample();
   MoveOnlyFunctionExample();
   TestEverythingLambda();
}
