#include <print>

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

int main()
{
   PointerToMemberExample();
}
