#pragma once

#include "Grid.hpp"

class MyGrid : public Grid {
public:

    // The Constructor
    //
    // Constructs a grid with the given size and initial tile.
    MyGrid(size_t rows, size_t cols, const Tile& initialTile) : _rows(rows), _cols(cols), _initTile(initialTile) {

        Tile** grid = new Tile*[rows];
        for(size_t r = 0; r < rows; ++r) {
            grid[r] = new Tile[cols];
            for(size_t c = 0; c < cols; ++c) {
                grid[r][c] = initialTile;
            }
        }
    };

    // The Copy Constructor
    //
    // Constructs a grid with the same size and contents as the supplied
    // other grid.
    MyGrid(const MyGrid& other) : MyGrid(other._rows, other._cols, other._initTile) {

        for(size_t r = 0; r < other._rows; ++r) {
            for(size_t c = 0; c < other._cols; ++c) {
                this->grid[r][c] = other.grid[r][c];
            }
        }
    };

    // The Move Constructor
    //
    // Constructs a grid with the same size and contents as the supplied
    // other grid.  Potentially reuse data from that other grid.
    MyGrid(MyGrid&&) noexcept;

    // The Move Assignment Operator
    //
    //
    MyGrid& operator=(MyGrid&&) noexcept;

    // The remaining functions are those inherited from the abstract Grid
    // class.  We add the 'override' specifier to each of them to declare
    // our intent.  This way, the compiler can warn us when one of these
    // functions doesn't actually override a member function from the base
    // class, e.g., because we forgot a 'const' somewhere.

    ~MyGrid() override;

    MyGrid& operator=(const Grid&);

    size_t rows() const override { return this->_rows; };

    size_t cols() const override { return this->_cols; };

    bool validPosition(size_t row, size_t col) const noexcept override { return ( (row >= 0 && row < this->_rows) && (col >= 0 && col < this->_cols) ); };

    Tile& operator()(size_t row, size_t col) override;

    const Tile& operator()(size_t row, size_t col) const override;

    void print(std::ostream&) const override;

    static MyGrid read(std::istream&);

protected:
    // TODO Add custom member functions and variables here:
private:

    const size_t _rows;
    const size_t _cols;
    const Tile& _initTile;
    Tile **grid;

};
