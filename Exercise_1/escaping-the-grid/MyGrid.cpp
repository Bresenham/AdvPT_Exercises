#include <cassert>
#include <iostream>
#include <string>

#include "Tile.hpp"
#include "MyGrid.hpp"


// TODO Define all member functions:

void MyGrid::print(std::ostream& ostream) const {

    ostream << this->_rows << std::endl;

    ostream << this->_cols << std::endl;

    for(size_t r = 0; r < this->_rows; ++r) {
        for(size_t c = 0; c < this->_cols; ++c) {
            ostream << char_from_tile( this->grid[c][r] );
        }

        ostream << std::endl;
    }  
}

MyGrid MyGrid::read(std::istream& input_stream) {

    size_t rows, cols;
    input_stream >> rows;
    input_stream >> cols;

    Tile t;
    MyGrid new_grid = MyGrid(rows, cols, t);

    for(size_t r = 0; r < rows; ++r) {

        for(size_t c = 0; c < cols; ++c) {

            char tile;
            input_stream >> tile;
            new_grid(r, c) = tile_from_char( tile );
        }

    }

    return new_grid;

}
