#include <cassert>
#include <iostream>
#include <string>

#include "Tile.hpp"
#include "MyGrid.hpp"

invalid_grid_position invalid_grid_position;

// TODO Define all member functions:

static MyGrid read(std::istream& input_stream) {

    size_t rows, cols;
    input_stream >> rows;
    input_stream >> cols;

    Tile t;
    MyGrid new_grid = MyGrid(rows, cols, t);

    for(size_t r = 0; r < rows; ++r) {

        std::string line;
        std::getline(input_stream, line);

        for(size_t c = 0; c < cols; ++c) {
            
            const Tile t = tile_from_char( line.at(c) );
            
        }

    }

}