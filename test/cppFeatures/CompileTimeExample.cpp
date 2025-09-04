#include <catch2/catch_test_macros.hpp>
#include <memory>

struct Car
{
   virtual ~Car()                      = default;
   constexpr virtual int speed() const = 0;
};

struct Mercedes : Car
{
   constexpr int speed() const override { return 5; }
};

struct Toyota : Car
{
   constexpr int speed() const override { return 6; }
};

struct Tesla : Car
{
   constexpr int speed() const override { return 9; }
};

constexpr std::unique_ptr<Car> CreateCar(int i)
{
   switch(i)
   {
      case 0: return std::make_unique<Mercedes>(Mercedes{});
      case 1: return std::make_unique<Toyota>(Toyota{});
      case 2: return std::make_unique<Tesla>(Tesla{});
   }
   return nullptr;
}

constexpr int FastestCarId()
{
   int max   = -1;
   int maxId = -1;
   for(int i = 0; i < 3; ++i)
   {
      const std::unique_ptr<Car> car = CreateCar(i);
      if(car->speed() > max)
      {
         max   = car->speed();
         maxId = i;
      }
   }

   return maxId;
}

TEST_CASE("Compile Time Code", "[compileTime]")
{
   constexpr auto fastestCarId = FastestCarId();
   REQUIRE(fastestCarId == 2);
}
