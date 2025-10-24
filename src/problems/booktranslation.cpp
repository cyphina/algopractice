#include "graph/booktranslation.h"

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "graph/graph.h"

int main()
{
   std::println("Input number of target languages and then number of translators");
   uint32_t NumTargetLanguages{0}, NumTranslators{0};

   std::cin >> NumTargetLanguages >> NumTranslators;

   if(std::cin)
   {
      std::vector<std::string> TargetLanguages;
      TargetLanguages.reserve(NumTargetLanguages);

      std::string TargetLanguage;

      std::println("Input {} Each Target Language", NumTargetLanguages);

      for(int TargetLanguageIndex{0}; TargetLanguageIndex < NumTargetLanguages; TargetLanguageIndex++)
      {
         if(std::cin >> TargetLanguage)
         {
            TargetLanguages.emplace_back(TargetLanguage);
         }
      }

      std::string               TranslatorLanguage;
      uint32_t                  TranslationCost;
      Graph::Graph<std::string> Graph;
      const auto&               Nodes{Graph.GetNodes()};

      for(int NumTranslatorsIndex{0}; NumTranslatorsIndex < NumTranslators; ++NumTranslatorsIndex)
      {
         std::println("Input Source Language, Target Language, then Cost. {}/{}", NumTranslatorsIndex, NumTranslators);
         std::cin >> TranslatorLanguage;
         Graph::Node<std::string>* Node1{};

         if(const auto NodeIt{std::ranges::find_if(Nodes,
                                                   [&TranslatorLanguage](const auto& Node)
                                                   {
                                                      return Node->Data == TranslatorLanguage;
                                                   })};
            NodeIt != Nodes.end())
         {
            Node1 = NodeIt->get();
         }
         else
         {
            Node1 = Graph.EmplaceNode(std::move(TranslatorLanguage));
         }

         std::cin >> TranslatorLanguage;

         Graph::Node<std::string>* Node2{};
         if(const auto NodeIt{std::ranges::find_if(Nodes,
                                                   [&TranslatorLanguage](const auto& Node)
                                                   {
                                                      return Node->Data == TranslatorLanguage;
                                                   })};
            NodeIt != Nodes.end())
         {
            Node2 = NodeIt->get();
         }
         else
         {
            Node2 = Graph.EmplaceNode(std::move(TranslatorLanguage));
         }

         std::cin >> TranslationCost;
         Graph.AddUndirectedEdge(Node1, Node2, TranslationCost);
      }

      std::vector<std::string_view> NodeStrings;
      // Need explicit return tyep cause it's going to return Node->Data aka a string. Then try to assign it to Nodes but then back inserter
      // overrides operator= to mean insert. It would then try to implicit convert the temp string to a string view and then we get garbo.
      std::ranges::transform(Nodes, std::back_inserter(NodeStrings),
                             [](const std::unique_ptr<Graph::Node<std::string>>& Node) -> std::string_view
                             {
                                return Node->Data;
                             });
      std::println("Nodes: {}", NodeStrings);

      for(const auto& TargetLanguage : TargetLanguages)
      {
         if(const auto MinimalCost{BookTranslation::FindMinimalCostTranslation(Graph, "English", TargetLanguage)})
         {
            std::println("Minimal Cost Edges {} Cost {}", MinimalCost->EdgeCountCost, MinimalCost->EdgeCost);
         }
      }
   }
}
