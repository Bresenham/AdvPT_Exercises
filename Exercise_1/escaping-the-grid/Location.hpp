#pragma once

#include "Grid.hpp"

enum Direction { Left, Right, Up, Down };

class Location {
public:
    Location(const size_t x, const size_t y) : _x(x), _y(y) { };
    Location(Location& other) : Location(other._x, other._y) { };
    Location(const Location& other) : Location(other._x, other._y) { };

    void move(const Direction &dir) {
        switch(dir) {
            case Left: {
                this->_x -= 1;
            } break;
            case Right: {
                this->_x += 1;
            } break;
            case Up: {
                this->_y -= 1;
            } break;
            case Down: {
                this->_y += 1;
            } break;
            default: break;
        }
    }

    bool is_valid(const Grid &grid) {

        const bool valid_pos = grid.validPosition(this->get_x(), this->get_y());
        const Tile &tile = grid(this->get_x(), this->get_y());

        return valid_pos && ( tile == Floor );
    }

    friend bool operator==(const Location& lhs, const Location& rhs) {
        return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
    }

    size_t get_x() const { return _x; }
    size_t get_y() const { return _y; }

    bool is_escape_tile(const Grid &grid) {
        return ( this->_x == ( grid.cols() - 1 ) )
                || ( this->_y == ( grid.rows() -1 ) )
                || this->_x == 0
                || this->_y == 0;
    }

private:
    size_t _x;
    size_t _y;
};