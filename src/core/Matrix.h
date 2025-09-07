#pragma once
#include <array>
#include <cassert>
#include <ranges>
#include <stdexcept>

namespace Core
{
   /** A square matrix */
   template <typename T, std::size_t RowSize, std::size_t ColumnSize>
   class Matrix
   {
    public:
      Matrix() = default;
      Matrix(std::initializer_list<T> Values)
      {
         if(Values.size() == ColumnSize * RowSize)
         {
            std::ranges::copy(Values, m.begin());
         }
         else
         {
            throw std::out_of_range("Matrix index out of range");
         }
      }
      explicit Matrix(const std::array<T, RowSize * ColumnSize>& Values) : m(Values) {}

      T& At(size_t Row, size_t Column);
      T  At(size_t Row, size_t Column) const;

      template <size_t C2>
      Matrix<T, RowSize, C2> MultiplyMatrix(const Matrix<T, ColumnSize, C2>& A) const;

      T& operator[](std::size_t x) const { return m[x]; }

      std::array<T, RowSize * ColumnSize> m{};
   };

   template <typename T, std::size_t RowSize, std::size_t ColumnSize>
   T Matrix<T, RowSize, ColumnSize>::At(size_t Row, size_t Column) const
   {
      const size_t Index = Column + Row * ColumnSize;
      if(Index >= m.size())
      {
         throw std::out_of_range("Matrix index out of range");
      }
      return m[Index];
   }

   template <typename T, std::size_t RowSize, std::size_t ColumnSize>
   T& Matrix<T, RowSize, ColumnSize>::At(size_t Row, size_t Column)
   {
      const size_t Index = Column + Row * ColumnSize;
      if(Index >= m.size())
      {
         throw std::out_of_range("Matrix index out of range");
      }
      return m[Index];
   }

   template <typename T, std::size_t R, std::size_t C>
   template <size_t C2>
   Matrix<T, R, C2> Matrix<T, R, C>::MultiplyMatrix(const Matrix<T, C, C2>& A) const
   {
      Matrix<T, R, C2> Result;

      for(int i = 0; i < R; ++i)
      {
         for(int j = 0; j < C2; ++j)
         {
            T Sum{};
            for(int k = 0; k < C; ++k)
            {
               Sum += this->At(i, k) * A.At(k, j);
            }
            Result.At(i, j) = Sum;
         }
      }

      return Result;
   }
}
