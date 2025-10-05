#pragma once

#include <format>
#include <optional>
#include <stdexcept>
#include <vector>

namespace Core
{
   template <typename T>
   class Grid
   {
    public:
      explicit Grid(size_t Width = DefaultWidth, size_t Height = DefaultHeight);
      virtual ~Grid() = default;

      Grid(const Grid& Src)            = default;
      Grid& operator=(const Grid& Rhs) = default;

      Grid(Grid&& Src)            = default;
      Grid& operator=(Grid&& Rhs) = default;

      std::optional<T>&       operator[](std::size_t X, std::size_t Y);
      const std::optional<T>& operator[](std::size_t X, std::size_t Y) const;

      std::optional<T>&       At(std::size_t X, std::size_t Y);
      const std::optional<T>& At(std::size_t X, std::size_t Y) const;

      std::size_t GetHeight() const { return m_height; }
      std::size_t GetWidth() const { return m_width; }

      static constexpr std::size_t DefaultWidth{10};
      static constexpr std::size_t DefaultHeight{10};

    private:
      void VerifyCoordinate(std::size_t X, std::size_t Y) const;

      std::vector<std::optional<T>> m_cells;
      std::size_t                   m_width{0}, m_height{0};
   };

   template <typename T>
   Grid<T>::Grid(size_t Width, size_t Height)
   {
      m_cells.resize(Width * Height);
   }

   template <typename T>
   const std::optional<T>& Grid<T>::operator[](std::size_t X, std::size_t Y) const
   {
      return At(X, Y);
   }

   template <typename T>
   std::optional<T>& Grid<T>::operator[](std::size_t X, std::size_t Y)
   {
      return const_cast<std::optional<T>&>(std::as_const(*this)[X, Y]);
   }

   template <typename T>
   std::optional<T>& Grid<T>::At(std::size_t X, std::size_t Y)
   {
      return const_cast<std::optional<T>&>(std::as_const(*this).At(X, Y));
   }

   template <typename T>
   const std::optional<T>& Grid<T>::At(std::size_t X, std::size_t Y) const
   {
      VerifyCoordinate(X, Y);
      return m_cells[X * m_width + Y];
   }

   template <typename T>
   void Grid<T>::VerifyCoordinate(std::size_t X, std::size_t Y) const
   {
      if(X >= m_width)
      {
         throw std::out_of_range{std::format("X ({}) must be less than width ({}).", X, m_width)};
      }

      if(Y >= m_height)
      {
         throw std::out_of_range{std::format("Y ({}) must be less than height ({}).", Y, m_height)};
      }
   }
}
