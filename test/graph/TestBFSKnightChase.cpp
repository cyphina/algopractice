#include <catch2/catch_test_macros.hpp>
#include "graph/bfsknightchase.h"

TEST_CASE("Test BFS Knight Chase", "[bfs]")
{
   BFSKnightChase::KnightChaseGrid EmptyBoard1{0, 0};
   const auto                      EmptyResult{BFSKnightChase::KnightChase(EmptyBoard1, {0, 0}, {0, 0})};
   REQUIRE(!EmptyResult.has_value());

   BFSKnightChase::KnightChaseGrid OutsideBoard{4, 4};
   const auto                      OutsideResult{BFSKnightChase::KnightChase(OutsideBoard, {5, 5}, {5, 5})};
   REQUIRE(!OutsideResult.has_value());

   BFSKnightChase::KnightChaseGrid Board1{7, 7};
   const auto                      Result{BFSKnightChase::KnightChase(Board1, {0, 0}, {3, 5})};

   REQUIRE(Result->NumMoves == 3);
   REQUIRE(Result->Outcome == BFSKnightChase::ChaseResult::KnightWin);

   // Need to reset the values in the board since we write to it.
   BFSKnightChase::KnightChaseGrid Board2{7, 7};
   const auto                      Result2{BFSKnightChase::KnightChase(Board2, {2, 0}, {5, 0})};
   REQUIRE(Result2->NumMoves == 3);
   REQUIRE(Result2->Outcome == BFSKnightChase::ChaseResult::Stalemate);
}
