#pragma once

#include <string>
#include <vector>

namespace JobScheduler
{
   using JobOrderList = std::vector<std::string>;

   struct Job
   {
      std::string                   Name;
      std::vector<std::string_view> Dependencies;
   };

   /**
    * For this problem we'll try to use an adjacency list instad of our graph.
    */
   JobOrderList FindValidJobOrder(const std::vector<Job>& Jobs);
}
