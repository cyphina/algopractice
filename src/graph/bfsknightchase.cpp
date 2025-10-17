#include "graph/bfsknightchase.h"
#include <queue>

namespace
{
   void AddNewSquareCoordinateToQueueIfValid(std::queue<Core::GridCoordinate>& Queue,
                                             BFSKnightChase::KnightChaseGrid&  Board,
                                             Core::GridCoordinate StartSquareCoordinate, int RowOffset,
                                             int ColumnOffset)
   {
      assert(Board.At(StartSquareCoordinate.Row, StartSquareCoordinate.Column).has_value());

      long long NewRowIndex{static_cast<long long>(StartSquareCoordinate.Row) + RowOffset};
      long long NewColumnIndex{static_cast<long long>(StartSquareCoordinate.Column) + ColumnOffset};

      if(NewRowIndex < 0 || NewRowIndex >= Board.GetHeight())
      {
         return;
      }

      if(NewColumnIndex < 0 || NewColumnIndex >= Board.GetWidth())
      {
         return;
      }

      auto& BoardSlot{Board[NewRowIndex, NewColumnIndex]};
      if(BoardSlot)
      {
         return;
      }

      BoardSlot = Board[StartSquareCoordinate.Row, StartSquareCoordinate.Column].value() + 1;

      Queue.emplace(NewRowIndex, NewColumnIndex);
   }

   std::optional<size_t> FindKnightMinimalDistanceToSquare(BFSKnightChase::KnightChaseGrid& Board,
                                                           Core::GridCoordinate             KnightStart,
                                                           Core::GridCoordinate             TargetSquare)
   {
      const auto CoordinateValue{Board[TargetSquare.Row, TargetSquare.Column]};
      if(CoordinateValue.has_value())
      {
         return CoordinateValue;
      }

      auto& StartSlot{Board[KnightStart.Row, KnightStart.Column]};
      if(!StartSlot)
      {
         StartSlot = 0;
      }

      if(KnightStart == TargetSquare)
      {
         return 0;
      }

      std::queue<Core::GridCoordinate> CoordinatesToExplore;

      CoordinatesToExplore.push(KnightStart);

      while(!CoordinatesToExplore.empty())
      {
         const auto CurrentCoordinateToExplore{CoordinatesToExplore.front()};

         if(CurrentCoordinateToExplore == TargetSquare)
         {
            return Board[CurrentCoordinateToExplore.Row, CurrentCoordinateToExplore.Column];
         }

         CoordinatesToExplore.pop();

         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, -2, -1);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, -2, 1);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, -1, -2);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, -1, 2);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, 1, -2);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, 1, 2);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, 2, -1);
         AddNewSquareCoordinateToQueueIfValid(CoordinatesToExplore, Board, CurrentCoordinateToExplore, 2, 1);
      }

      return {};
   }
}

std::optional<BFSKnightChase::KnightChaseResult>
BFSKnightChase::KnightChase(KnightChaseGrid& Board, Core::GridCoordinate PawnStart, Core::GridCoordinate KnightStart)
{
   if(Board.GetHeight() == 0 || Board.GetWidth() == 0)
   {
      return {};
   }

   if(PawnStart.Row > Board.GetHeight() || KnightStart.Row > Board.GetHeight())
   {
      return {};
   }

   if(PawnStart.Column > Board.GetWidth() || KnightStart.Column > Board.GetWidth())
   {
      return {};
   }

   if(PawnStart.Column == KnightStart.Column && PawnStart.Row + 1 == KnightStart.Row)
   {
      return KnightChaseResult{0, ChaseResult::Stalemate};
   }

   if(PawnStart.Row == Board.GetHeight() - 1)
   {
      return KnightChaseResult{0, ChaseResult::PawnWin};
   }

   std::optional<size_t> MinTiebreakMoves;

   size_t PawnMoveIndex{0};
   for(size_t RowIndex = PawnStart.Row + 1; RowIndex < Board.GetHeight(); ++RowIndex)
   {
      ++PawnMoveIndex;

      Core::GridCoordinate TargetCoord{RowIndex, PawnStart.Column};

      if(const auto OptimalNumMovesToSquare{FindKnightMinimalDistanceToSquare(Board, KnightStart, TargetCoord)})
      {
         const auto OptimalNumMovesToSquareValue{OptimalNumMovesToSquare.value()};

         if(OptimalNumMovesToSquareValue == PawnMoveIndex)
         {
            return KnightChaseResult{OptimalNumMovesToSquareValue, ChaseResult::KnightWin};
         }

         // If knight can arrive here earlier then we can intercept or block.
         if(OptimalNumMovesToSquareValue < PawnMoveIndex)
         {
            // Add two numbers if they become even then they were both odd or even.
            const auto InterceptNumMovesToSquare{OptimalNumMovesToSquareValue + PawnMoveIndex};
            if(InterceptNumMovesToSquare % 2 == 0)
            {
               // This is the first time we hit a square we can both arrive to checking one step at a time from the pawn so it's the least amount of moves
               return KnightChaseResult{PawnMoveIndex, ChaseResult::KnightWin};
            }
            else
            {
               if(!MinTiebreakMoves)
               {
                  // Knight moves before pawn so it moves one less than pawn for block.
                  MinTiebreakMoves = PawnMoveIndex;
               }
            }
         }
      }
   }

   // We returned capture case above.

   if(MinTiebreakMoves)
   {
      return KnightChaseResult{MinTiebreakMoves.value(), ChaseResult::Stalemate};
   }
   else
   {
      return KnightChaseResult{0, ChaseResult::PawnWin};
   }
}
