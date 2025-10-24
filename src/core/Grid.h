#pragma once

#include <cassert>
#include <format>
#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <vector>

namespace Core
{
   struct GridCoordinate
   {
      size_t Row;
      size_t Column;

      [[nodiscard]] bool operator==(const GridCoordinate& Rhs) const = default;
   };

   template <typename T>
   class Grid
   {
    public:
      // Prevent doing Grid g = 5;
      explicit Grid(size_t Width = DefaultWidth, size_t Height = DefaultHeight);
      constexpr Grid(const std::initializer_list<std::initializer_list<T>>& Init);

      virtual ~Grid() = default;

      Grid(const Grid& Src)            = default;
      Grid& operator=(const Grid& Rhs) = default;

      Grid(Grid&& Src)            = default;
      Grid& operator=(Grid&& Rhs) = default;

      std::optional<T>&       operator[](std::size_t Row, std::size_t Column);
      const std::optional<T>& operator[](std::size_t Row, std::size_t Column) const;

      std::optional<T>&       At(std::size_t Row, std::size_t Column);
      const std::optional<T>& At(std::size_t Row, std::size_t Column) const;

      std::size_t GetHeight() const { return m_height; }
      std::size_t GetWidth() const { return m_width; }

      static constexpr std::size_t DefaultWidth{10};
      static constexpr std::size_t DefaultHeight{10};

    private:
      void VerifyCoordinate(std::size_t Row, std::size_t Col) const;

      std::vector<std::optional<T>> m_cells;
      std::size_t                   m_width{0}, m_height{0};
   };

   template <typename T>
   Grid<T>::Grid(size_t Width, size_t Height)
   {
      m_cells.resize(Width * Height);
      m_width  = Width;
      m_height = Height;
   }

   template <typename T>
   constexpr Grid<T>::Grid(const std::initializer_list<std::initializer_list<T>>& Init)
   {
      size_t NumRows{Init.size()};

      if(NumRows > 0)
      {
         size_t NumCols = Init.begin()->size();

         m_cells.resize(NumRows * NumCols);
         m_width  = NumCols;
         m_height = NumRows;

         for(int i = 0; const auto& Row : Init)
         {
            if(Row.size() != NumCols)
            {
               throw std::runtime_error("All rows must have the same number of columns!");
            }

            for(int j = 0; const auto& Column : Row)
            {
               (*this)[i, j] = Column;
               ++j;
            }
            ++i;
         }
      }
   }

   template <typename T>
   std::optional<T>& Grid<T>::At(std::size_t Row, std::size_t Column)
   {
      return const_cast<std::optional<T>&>(std::as_const(*this).At(Row, Column));
   }

   template <typename T>
   const std::optional<T>& Grid<T>::At(std::size_t Row, std::size_t Column) const
   {
      VerifyCoordinate(Row, Column);
      return m_cells[Row * m_width + Column];
   }

   template <typename T>
   const std::optional<T>& Grid<T>::operator[](std::size_t Row, std::size_t Column) const
   {
      return At(Row, Column);
   }

   template <typename T>
   std::optional<T>& Grid<T>::operator[](std::size_t Row, std::size_t Column)
   {
      return const_cast<std::optional<T>&>(std::as_const(*this)[Row, Column]);
   }

   template <typename T>
   void Grid<T>::VerifyCoordinate(std::size_t Row, std::size_t Col) const
   {
      if(Row >= m_height)
      {
         throw std::out_of_range{std::format("Row ({}) must be less than width ({}).", Row, m_width)};
      }

      if(Col >= m_width)
      {
         throw std::out_of_range{std::format("Row ({}) must be less than height ({}).", Col, m_height)};
      }
   }

   /** Static grid has fixed width and height */
   template <typename T, int WIDTH = 10, int HEIGHT = 10>
   class StaticGrid
   {
    public:
      // Prevent doing Grid g = 5;
      explicit StaticGrid();
      constexpr StaticGrid(const std::array<std::array<T, WIDTH>, HEIGHT>& Init);

      // Rule of 5 since we specified the destructor
      virtual ~StaticGrid() = default;

      // Still need the default since it doesn't use overloads if T == E
      StaticGrid(const StaticGrid& Src)            = default;
      StaticGrid& operator=(const StaticGrid& Rhs) = default;

      template <typename E, int WIDTH2, int HEIGHT2>
      StaticGrid(const StaticGrid<E, WIDTH2, HEIGHT2>& Src);

      template <typename E, int WIDTH2, int HEIGHT2>
      StaticGrid& operator=(const StaticGrid<E, WIDTH2, HEIGHT2>& Rhs);

      StaticGrid(StaticGrid&& Src) noexcept            = default;
      StaticGrid& operator=(StaticGrid&& Rhs) noexcept = default;

      std::optional<T>&       operator[](std::size_t Row, std::size_t Column);
      const std::optional<T>& operator[](std::size_t Row, std::size_t Column) const;

      std::optional<T>&       At(std::size_t Row, std::size_t Column);
      const std::optional<T>& At(std::size_t Row, std::size_t Column) const;

      std::size_t GetHeight() const { return m_height; }
      std::size_t GetWidth() const { return m_width; }

      void Swap(StaticGrid& Other) noexcept;

      static constexpr std::size_t DefaultWidth{10};
      static constexpr std::size_t DefaultHeight{10};

    private:
      void VerifyCoordinate(std::size_t Row, std::size_t Col) const;

      std::vector<std::optional<T>> m_cells;
      std::size_t                   m_width{WIDTH}, m_height{HEIGHT};
   };

   template <typename T, int WIDTH, int HEIGHT>
   constexpr StaticGrid<T, WIDTH, HEIGHT>::StaticGrid(const std::array<std::array<T, WIDTH>, HEIGHT>& Init)
   {
      size_t NumRows{Init.size()};

      if(NumRows > 0)
      {
         size_t NumCols = Init.begin()->size();

         m_cells.resize(NumRows * NumCols);

         for(int i = 0; const auto& Row : Init)
         {
            if(Row.size() != NumCols)
            {
               throw std::runtime_error("All rows must have the same number of columns!");
            }

            for(int j = 0; const auto& Column : Row)
            {
               (*this)[i, j] = Column;
               ++j;
            }
            ++i;
         }
      }
   }

   template <typename T, int WIDTH, int HEIGHT>
   std::optional<T>& StaticGrid<T, WIDTH, HEIGHT>::At(std::size_t Row, std::size_t Column)
   {
      return const_cast<std::optional<T>&>(std::as_const(*this).At(Row, Column));
   }

   template <typename T, int WIDTH, int HEIGHT>
   const std::optional<T>& StaticGrid<T, WIDTH, HEIGHT>::At(std::size_t Row, std::size_t Column) const
   {
      VerifyCoordinate(Row, Column);
      return m_cells[Row * m_width + Column];
   }

   template <typename T, int WIDTH, int HEIGHT>
   void StaticGrid<T, WIDTH, HEIGHT>::Swap(StaticGrid& Other) noexcept
   {
      std::swap(m_cells, Other.m_cells);
   }

   template <typename T, int WIDTH, int HEIGHT>
   const std::optional<T>& StaticGrid<T, WIDTH, HEIGHT>::operator[](std::size_t Row, std::size_t Column) const
   {
      return At(Row, Column);
   }

   template <typename T, int WIDTH, int HEIGHT>
   StaticGrid<T, WIDTH, HEIGHT>::StaticGrid()
   {
      m_cells.resize(WIDTH * HEIGHT);
   }

   template <typename T, int WIDTH, int HEIGHT>
   template <typename E, int WIDTH2, int HEIGHT2>
   StaticGrid<T, WIDTH, HEIGHT>::StaticGrid(const StaticGrid<E, WIDTH2, HEIGHT2>& Src)
   {
      m_cells.resize(WIDTH * HEIGHT);

      for(int i = 0; i < HEIGHT; ++i)
      {
         for(int j = 0; j < WIDTH; ++j)
         {
            if(i < HEIGHT2 && j < WIDTH2)
            {
               (*this)[i, j] = Src[i, j];
            }
            else
            {
               (*this)[i, j].reset();
            }
         }
      }
   }

   template <typename T, int WIDTH, int HEIGHT>
   template <typename E, int WIDTH2, int HEIGHT2>
   StaticGrid<T, WIDTH, HEIGHT>& StaticGrid<T, WIDTH, HEIGHT>::operator=(const StaticGrid<E, WIDTH2, HEIGHT2>& Rhs)
   {
      // Note we do overwrite any old values since operator= means we're trying to have something similar to the right not keep anything.
      StaticGrid Temp{Rhs}; // Do all work in a temp instance
      Swap(Temp);           // Commit work with non-throwing operations.
      m_cells.resize(WIDTH * HEIGHT);
      return *this;
   }

   template <typename T, int WIDTH, int HEIGHT>
   std::optional<T>& StaticGrid<T, WIDTH, HEIGHT>::operator[](std::size_t Row, std::size_t Column)
   {
      return const_cast<std::optional<T>&>(std::as_const(*this)[Row, Column]);
   }

   template <typename T, int WIDTH, int HEIGHT>
   void StaticGrid<T, WIDTH, HEIGHT>::VerifyCoordinate(std::size_t Row, std::size_t Col) const
   {
      if(Row >= m_height)
      {
         throw std::out_of_range{std::format("Row ({}) must be less than width ({}).", Row, m_width)};
      }

      if(Col >= m_width)
      {
         throw std::out_of_range{std::format("Row ({}) must be less than height ({}).", Col, m_height)};
      }
   }
}
