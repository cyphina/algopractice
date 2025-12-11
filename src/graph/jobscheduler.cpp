#include "jobscheduler.h"

#include <print>
#include <queue>
#include <unordered_map>

namespace JobScheduler
{
   JobOrderList FindValidJobOrder(const std::vector<Job>& Jobs)
   {
      struct JobNodeT
      {
         std::string_view Name;
         // Need to know everything that depends on us
         std::vector<JobNodeT*> Dependants;
      };

      std::vector<JobNodeT> JobNodes;
      JobNodes.reserve(Jobs.size());

      for(const auto& Job : Jobs)
      {
         JobNodes.emplace_back(Job.Name, std::vector<JobNodeT*>{});
      }

      std::unordered_map<std::string_view, JobNodeT*> NameToNode;
      NameToNode.reserve(JobNodes.size());

      for(auto& JobNode : JobNodes)
      {
         NameToNode.emplace(JobNode.Name, &JobNode);
      }

      std::unordered_map<const JobNodeT*, uint32_t, std::hash<const JobNodeT*>, std::equal_to<>> JobToInDegrees;

      for(const auto& Job : Jobs)
      {
         auto& JobNode = NameToNode.at(Job.Name);
         JobToInDegrees.emplace(JobNode, Job.Dependencies.size());

         for(const auto& Dependency : Job.Dependencies)
         {
            auto& NodeToDependOn = NameToNode.at(Dependency);
            NodeToDependOn->Dependants.emplace_back(JobNode);
         }
      }

      std::queue<const JobNodeT*> JobOrder;
      for(const auto& [JobNode, InDegree] : JobToInDegrees)
      {
         if(InDegree == 0)
         {
            JobOrder.push(JobNode);
         }
      }

      JobOrderList ResultOrder;
      ResultOrder.reserve(Jobs.size());

      while(!JobOrder.empty())
      {
         const auto JobNode{JobOrder.front()};
         JobOrder.pop();
         ResultOrder.emplace_back(JobNode->Name);

         for(const auto& DependencyNode : JobNode->Dependants)
         {
            auto& DependencyNodeDegree{JobToInDegrees.at(DependencyNode)};
            --DependencyNodeDegree;

            if(DependencyNodeDegree == 0)
            {
               JobOrder.push(DependencyNode);
            }
         }
      }

      return ResultOrder;
   }
}
