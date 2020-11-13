#include <cassert>
#include <iostream>
#include <string>

#include "Tile.hpp"
#include "MyGrid.hpp"

invalid_grid_position invalid_grid_position;

// TODO Define all member functions:

void MyGrid::print(std::ostream& ostream) const {

    ostream << this->_rows << std::endl;
    ostream << this->_cols << std::endl;

    for(size_t r = 0; r < this->_rows; ++r) {
        for(size_t c = 0; c < this->_rows; ++c) {
            ostream << char_from_tile( this->grid[r][c] );
        }
    }

}

MyGrid MyGrid::read(std::istream& input_stream) {

    size_t rows, cols;
    input_stream >> rows;
    input_stream >> cols;

    Tile t;
    MyGrid new_grid = MyGrid(rows, cols, t);

    for(size_t r = 0; r < rows; ++r) {

        std::string line;
        std::getline(input_stream, line);

        for(size_t c = 0; c < cols; ++c) {
            new_grid(r, c) = tile_from_char( line.at(c) );
        }

    }

    return new_grid;

}
