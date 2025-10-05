#pragma once

export template <typename T>
class Grid
{
 public:
   explicit Grid(size_t Width = DefaultWidth, size_t Height = DefaultHeight);
   virtual ~Grid() = default;

   Grid(const Grid& Src)            = default;
   Grid& operator=(const Grid& Rhs) = default;

   Grid(Grid&& Src)            = default;
   Grid& operator=(Grid&& Rhs) = default;
};
