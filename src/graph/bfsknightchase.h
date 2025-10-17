#pragma once
#include "core/Grid.h"

namespace BFSKnightChase
{
   enum class ChaseResult
   {
      None,
      KnightWin,
      Stalemate,
      PawnWin,
   };

   struct KnightChaseResult
   {
      // How many moves the pawn has to make
      size_t      NumMoves{};
      ChaseResult Outcome{};
   };

   using KnightChaseGrid = Core::Grid<size_t>;

   /**
    * Game where pawn moves first, knight moves second.
    * Knight tries to chase the pawn to see if it can capture it or block it permanently.
    */
   std::optional<KnightChaseResult> KnightChase(KnightChaseGrid& Board, Core::GridCoordinate PawnStart,
                                                Core::GridCoordinate KnightStart);
}
