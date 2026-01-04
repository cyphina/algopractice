#include <iostream>
#include <unordered_set>
#include <vector>

// Given an NxN grid where 0 is empty and 1 is blocked,
// return true if N cameras can be placed on empty cells such that no two share
// the same row, column, or diagonal.
//
// The trick is due to the fact we have N camers and NxN grid that each row has to be used. As we explore we undo if something doesn't work.
//
// Problem is also known as the N-Queens problem.

namespace
{
   int GridSize{};
}

bool canPlaceSecurityCameras(int N, std::vector<std::vector<int>> grid)
{
   if(grid.empty())
   {
      return false;
   }

   if(grid[0].empty())
   {
      return false;
   }

   GridSize = N;

   struct GridCoordinate
   {
      std::size_t Row;
      std::size_t Column;

      [[nodiscard]] bool operator==(const GridCoordinate& Other) const
      {
         return Other.Row == Row && Other.Column == Column;
      }
   };

   struct GridCoordinateHasher
   {
      size_t operator()(const GridCoordinate& Coordinate) const noexcept
      {
         return std::hash<std::size_t>{}(Coordinate.Row * static_cast<std::size_t>(GridSize) + Coordinate.Column);
      }
   };

   using InvalidGridTilesSet = std::unordered_set<GridCoordinate, GridCoordinateHasher>;
   InvalidGridTilesSet InvalidGridTiles;

   for(std::size_t RowIndex{}; RowIndex < grid.size(); ++RowIndex)
   {
      for(std::size_t ColumnIndex{}; ColumnIndex < grid[0].size(); ++ColumnIndex)
      {
         if(grid[RowIndex][ColumnIndex] == 1)
         {
            InvalidGridTiles.emplace(RowIndex, ColumnIndex);
         }
      }
   }

   const auto canPlaceSecurityCamerasImpl =
       [](const std::vector<std::vector<int>>& Grid, InvalidGridTilesSet& InvalidGridTiles)
   {
      const auto canPlaceSecurityCamerasInternal = [](std::size_t RowIndex, const std::vector<std::vector<int>>& Grid,
                                                      InvalidGridTilesSet InvalidGridTiles,
                                                      const auto&         canPlaceSecurityCamerasInternal) -> bool
      {
         const auto& GridRow{Grid[RowIndex]};

         //std::cout << "GridRow Index: " << RowIndex << "\n";
         for(std::size_t ColumnIndex{}; ColumnIndex < GridRow.size(); ++ColumnIndex)
         {
            //std::cout << "Column Index: " << ColumnIndex << "\n";
            if(!InvalidGridTiles.contains({RowIndex, ColumnIndex}))
            {
               for(std::size_t InvalidColumnIndex{}; InvalidColumnIndex < GridRow.size(); ++InvalidColumnIndex)
               {
                  // Can use C++20 parens-init but older code environments can't handle it
                  InvalidGridTiles.emplace(GridCoordinate{RowIndex, InvalidColumnIndex});
               }

               for(std::size_t InvalidRowIndex{}; InvalidRowIndex < Grid.size(); ++InvalidRowIndex)
               {
                  InvalidGridTiles.emplace(GridCoordinate{InvalidRowIndex, ColumnIndex});
               }

               if(RowIndex == Grid.size() - 1)
               {
                  return true;
               }
               else
               {
                  if(canPlaceSecurityCamerasInternal(++RowIndex, Grid, InvalidGridTiles,
                                                     canPlaceSecurityCamerasInternal))
                  {
                     return true;
                  }
               }
            }
         }

         return false;
      };

      return canPlaceSecurityCamerasInternal(0, Grid, InvalidGridTiles, canPlaceSecurityCamerasInternal);
   };

   return canPlaceSecurityCamerasImpl(grid, InvalidGridTiles);
}

int main()
{
   std::cout << "Result: " << canPlaceSecurityCameras(4, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}})
             << "\n";

   std::cout << "Result2: " << canPlaceSecurityCameras(3, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}) << "\n";

   std::cout << "Result3: " << canPlaceSecurityCameras(3, {{0, 1, 1}, {0, 1, 1}, {0, 0, 0}}) << "\n";
}
