#pragma once

#include "Grid.hpp"
#include <utility>
#include <stdexcept>

class MyGrid : public Grid {
public:

    // The Constructor
    //
    // Constructs a grid with the given size and initial tile.
    MyGrid(size_t rows, size_t cols, const Tile& initialTile) : _rows(rows), _cols(cols), _initTile(initialTile) {

        this->grid = new Tile*[cols];

        for(size_t c = 0; c < cols; ++c) {

            this->grid[c] = new Tile[rows];

            for(size_t r = 0; r < rows; ++r) {
                this->grid[c][r] = initialTile;
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
                this->grid[c][r] = other.grid[c][r];
            }
        }
    };

    // The Move Constructor k(std::exchange(o.k, 0))
    //
    // Constructs a grid with the same size and contents as the supplied
    // other grid.  Potentially reuse data from that other grid.
    MyGrid(MyGrid&& move) noexcept : _rows( std::exchange(move._rows, 0) ), _cols( std::exchange(move._cols, 0) ), _initTile( move._initTile ),
                                    grid( std::exchange(move.grid, nullptr) ) {  };

    // The Move Assignment Operator
    //
    //
    MyGrid& operator=(MyGrid&& move) noexcept {

        this->_rows = std::exchange( move._rows, 0 );
        this->_cols = std::exchange( move._cols, 0 );
        this->grid = std::exchange( move.grid, nullptr );

        return *this;
    };

    // The remaining functions are those inherited from the abstract Grid
    // class.  We add the 'override' specifier to each of them to declare
    // our intent.  This way, the compiler can warn us when one of these
    // functions doesn't actually override a member function from the base
    // class, e.g., because we forgot a 'const' somewhere.

    ~MyGrid() override {

        for(size_t r = 0; r < this->_rows; ++r) {
            delete[] this->grid[r];
        }

        delete[] this->grid;
    };

    MyGrid& operator=(const Grid&) { return *this; };

    size_t rows() const override { return this->_rows; };

    size_t cols() const override { return this->_cols; };

    bool validPosition(size_t row, size_t col) const noexcept override { return ( (row >= 0 && row < this->_rows) && (col >= 0 && col < this->_cols) ); };

    Tile& operator()(size_t row, size_t col) override {

        if( validPosition(row, col) ) {
            return grid[col][row];
        } else {
            throw invalid_grid_position();
        }
    };

    const Tile& operator()(size_t row, size_t col) const override {

        if( validPosition(row, col) ) {
            return grid[col][row];
        } else {
            throw invalid_grid_position();
        }

    };

    void print(std::ostream&) const override;

    static MyGrid read(std::istream&);

protected:
    // TODO Add custom member functions and variables here:
private:
    size_t _rows;
    size_t _cols;

    const Tile& _initTile;

    Tile** grid;
};
