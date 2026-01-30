#include <print>
#include <utility>

class Foo2
{
 public:
   void Test();
};

class Bar
{
   friend class Foo;
   // Needs complete type
   friend void Foo2::Test();

 private:
   int Thing{5};
};

class Foo
{
   void Test()
   {
      Bar b;
      std::println("Foo {}", b.Thing);
   }
};

void Foo2::Test()
{
   Bar b;
   std::println("Foo 2 {}", b.Thing);
}

namespace DynamicMemoryInClass
{
   class SpreadsheetCell
   {
   };

   class Spreadsheet
   {
    public:
      Spreadsheet(std::size_t Width, std::size_t Height);
      Spreadsheet(const Spreadsheet& Src);
      void         swap(Spreadsheet& Other) noexcept;
      Spreadsheet& operator=(const Spreadsheet& Rhs);
      ~Spreadsheet();

      // X is like RowIndex Y is like ColumnIndex in a grid as oposed to X being (X,Y) coordinate pair in grid.
      // Example - Width 3. Height - 4
      // Order in Memory [0,11]
      // [0] [1] [2] - cells [x]
      //  |   |   |
      // [0] [4] [8] - order in memory, [0,0], [0,1], ... ,[2,3]
      // [1] [5] [9]
      // [2] [6] [10]
      // [3] [7] [11]
      // Keeping the names from the book but using X Y is a mismatch - it kind of like feels like a spatial index graph paper view type thing.
      // ANd under the hood we're just indexing linear memory but we can reimagine it as a table.
      // If a function describes index storage we use row, col, and if it describes space we cna use x,y.
      void             SetCellAt(std::size_t X, std::size_t Y, const SpreadsheetCell& Cell);
      SpreadsheetCell& GetCellAt(std::size_t X, std::size_t Y);

    private:
      bool              InRange(std::size_t Value, std::size_t Upper) const;
      std::size_t       width{};
      std::size_t       height{};
      SpreadsheetCell** cells{nullptr};
   };

   // Swap will be used by STL algorithms and can be found via ADL.
   void swap(Spreadsheet& First, Spreadsheet& Second) noexcept
   {
      First.swap(Second);
   }

   Spreadsheet::Spreadsheet(std::size_t Width, std::size_t Height) : width{Width}, height{Height}
   {
      // Each row we'll have a pointer to some pointer in the free store.
      cells = new SpreadsheetCell*[width];
      for(std::size_t i{}; i < width; ++i)
      {
         // Each pointer we have will point to an array of size height.
         cells[i] = new SpreadsheetCell[height];
      }
   }

   // Delegating constructor runs first. It allocates proper amount of memory. Then we run this body.
   Spreadsheet::Spreadsheet(const Spreadsheet& Src) : Spreadsheet(width, height)
   {
      for(size_t i{0}; i < width; ++i)
      {
         for(size_t j{0}; j < height; ++j)
         {
            cells[i][j] = Src.cells[i][j];
         }
      }
   }

   void Spreadsheet::swap(Spreadsheet& Other) noexcept
   {
      std::swap(width, Other.width);
      std::swap(height, Other.height);
      std::swap(cells, Other.cells);
   }

   Spreadsheet& Spreadsheet::operator=(const Spreadsheet& Rhs)
   {
      // Long variant
      /*
      // Check for self-assignment
      if(this == &Rhs)
      {
         return *this;
      }
      // Free the old memory
      for(size_t i{0}; i < width; ++i)
      {
         delete[] cells[i];
      }
      delete[] cells;
      cells = nullptr;
      // Allocate new memory
      width  = Rhs.m_width;
      height = Rhs.m_height;
      cells  = new SpreadsheetCell*[width];
      for(size_t i{0}; i < width; ++i)
      {
         cells[i] = new SpreadsheetCell[height];
      }
      // Copy the data
      for(size_t i{0}; i < width; ++i)
      {
         for(size_t j{0}; j < height; ++j)
         {
            cells[i][j] = Rhs.m_cells[i][j];
         }
      }
      return *this;
      */

      // Copy and swap for strong safety guarantee aka this class won't be partially updated if an exception is thrown.
      // Since we swap the destructor will do that cleanup work.
      // Relies on copy constructor for th data copying to the temporary and swapping to move it to this.
      Spreadsheet Temp{Rhs};
      swap(Temp);
      return *this;
   }

   Spreadsheet::~Spreadsheet()
   {
      for(std::size_t i{0}; i < width; ++i)
      {
         delete[] cells[i];
      }
      delete[] cells;
      cells = nullptr;
   }

   void Spreadsheet::SetCellAt(std::size_t X, std::size_t Y, const SpreadsheetCell& Cell)
   {
      cells[X][Y] = Cell;
   }

   SpreadsheetCell& Spreadsheet::GetCellAt(std::size_t X, std::size_t Y)
   {
      return cells[X][Y];
   }

   bool Spreadsheet::InRange(std::size_t Value, std::size_t Upper) const
   {
      return Value < Upper;
   }
}

int main()
{
   Foo2 F;
   F.Test();
}
