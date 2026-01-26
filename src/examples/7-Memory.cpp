#include <core/DebugUtils.h>
#include <memory>
#include <print>

class Base
{
 public:
   virtual void Test() { std::println("Base"); }

 private:
};

class Derived : public Base
{
 public:
   void Test() override { std::println("Derived"); }

 private:
};

void TestSmartPointerCasting()
{
   std::shared_ptr<Base> Value{std::make_shared<Derived>()};
   auto                  Value2{std::static_pointer_cast<Derived>(Value)};

   std::println("Use count after static cast: {}", Value.use_count());
}

void UseResource(std::weak_ptr<Test::TestCopyVsAssign> WeakThing)
{
   if(const auto Resource{WeakThing.lock()})
   {
      std::println("Resource Locked");
   }
   else
   {
      std::println("Resource Has Been Freed");
   }
}

void TestWeakPointer()
{
   auto                                  Shared{std::make_shared<Test::TestCopyVsAssign>()};
   std::weak_ptr<Test::TestCopyVsAssign> Weak{Shared};
   UseResource(Weak);
   Shared.reset();
   UseResource(Weak);
}

class Enemy;

class World
{
 public:
   void                 SpawnEnemy();
   std::weak_ptr<Enemy> GetEnemy(std::size_t Index) { return enemies[Index]; };

 private:
   std::vector<std::shared_ptr<Enemy>> enemies;
};

class AISystem
{
 public:
   static void RegisterEnemy(const std::shared_ptr<Enemy>& Enemy) { enemies.emplace_back(Enemy); }

 private:
   static inline std::vector<std::shared_ptr<Enemy>> enemies;
};

class Enemy : public std::enable_shared_from_this<Enemy>
{
 public:
   Enemy();
   ~Enemy();
};

void World::SpawnEnemy()
{
   std::shared_ptr<Enemy>& SpawnedEnemy{enemies.emplace_back(std::make_shared<Enemy>())};
   AISystem::RegisterEnemy(SpawnedEnemy->shared_from_this());
}

Enemy::Enemy()
{
   // Need to increment the shared pointer this might be a part of instead of
   // creating a new one.
   /// Cant' do this here since the internal weak pointer isn't setup yet.
   /// AISystem::RegisterEnemy(shared_from_this());
}

Enemy::~Enemy()
{
   std::println("Destroyed Enemy");
}

void TestEnabledSharedFromThis()
{
   World NewWorld;
   NewWorld.SpawnEnemy();

   std::println("Enemy System Use Count: {}", NewWorld.GetEnemy(0).use_count());
}

int main()
{
   TestSmartPointerCasting();
   TestWeakPointer();
   TestEnabledSharedFromThis();
}
