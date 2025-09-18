#pragma once

export template <typename T>
class Grid
{
 public:
   explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
   virtual ~Grid() = default;

   Grid(const Grid& Source)         = default;
   Grid& operator=(const Grid& RHS) = default;
};
