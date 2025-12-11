#include <catch2/catch_test_macros.hpp>
#include <print>
#include "Graph/jobscheduler.h"

TEST_CASE("JobScheduler", "[topologicalsort]")
{
   using namespace std::string_view_literals;

   std::vector<JobScheduler::Job> Jobs;
   Jobs.emplace_back("Clean", std::vector({"Do Homowork"sv, "Read Book"sv}));
   Jobs.emplace_back("Do Homowork", std::vector<std::string_view>{});
   Jobs.emplace_back("Read Book", std::vector<std::string_view>{});
   Jobs.emplace_back("Iron Clothes", std::vector<std::string_view>{"Read Book"sv});
   Jobs.emplace_back("Pee", std::vector<std::string_view>{"Iron Clothes"sv});
   Jobs.emplace_back("Walk Dog", std::vector<std::string_view>{"Clean"sv, "Pee"sv});
   Jobs.emplace_back("Shovel Snow", std::vector<std::string_view>{});
   const auto Result{JobScheduler::FindValidJobOrder(Jobs)};
   std::println("Result {}", Result);
}
