#include <cstddef>
#include <cassert>
#include <vector>

#include "Grid.hpp"

// Feel free to include additional headers here!

enum Direction { Left, Right, Up, Down };

std::string print_dir(const Direction &dir) {
    switch(dir) {
        case Left: {
            return "Left";
        } break;
        case Right: {
            return "Right";
        } break;
        case Up: {
            return "Up";
        } break;
        case Down: {
            return "Down";
        } break;
        default: return "";
    }
}

static const std::vector<Direction> ALL_DIRS = { Left, Right, Up, Down };

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

// Feel free to define auxiliary functions here!

std::vector<Direction> available_directions(const Location &loc, const Grid &grid) {

    std::vector<Direction> dirs;

    for(const Direction &dir : ALL_DIRS) {

        Location copyLoc(loc);
        copyLoc.move(dir);

        if( copyLoc.is_valid(grid) ) {
            dirs.push_back(dir);
        }
    }

    return dirs;
}

bool already_gone(const std::vector<Location> &path, const Location &loc) {

    for(const Location &p_loc : path) {
        if( p_loc == loc ) {
            return true;
        }
    }

    return false;
}

bool recursive_walk(std::vector<Location> &current_path, const Direction &dir, const Grid &grid) {

    Location copyLoc(current_path.back());
    copyLoc.move(dir);

    if( copyLoc.is_escape_tile(grid) ) {
        current_path.push_back(copyLoc);
        std::cout << "Received escape tile, this is my path: " << std::endl;
        for(const Location &loc : current_path) {
            std::cout << "  (" << loc.get_x() << "," << loc.get_y() << ")" << std::endl;
        }
        return true;
    }

    if( already_gone(current_path, copyLoc) ) {
        return false;
    }

    const std::vector<Direction> dirs = available_directions(copyLoc, grid);

    current_path.push_back(copyLoc);

    if( dirs.size() == 1 ) {
        if( recursive_walk(current_path, dirs.at(0), grid) ) {
            return true;
        }
    } else {

        for(size_t i = 0; i < dirs.size(); ++i) {

            std::vector<Location> path;

            for(size_t i = 0; i < current_path.size(); ++i) {
                path.push_back( current_path.at(i) );
            }

            if( recursive_walk(path, dirs.at(i), grid) ) {
                return true;
            }
        }
    }

    return false;

}

void Grid::escape() {
    Grid& grid = *this;
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.
    assert(grid.validPosition(3,4) == true);
    assert(grid(3,4) == Floor);

    // TODO implement some path finding algorithm find a correct path to an
    // exit tile, and then write that path to the grid.

    Location loc(1, 1);
    std::vector<Direction> dirs = available_directions(loc, grid);

    for(const Direction &dir : dirs) {

        std::vector<Location> path;
        path.push_back(loc);

        const bool success = recursive_walk(path, dir, grid);
        if( success ) {
            std::cout << "SUCCESS PATH:" << std::endl;
            for(Location &loc : path) {
                std::cout << "(" << loc.get_x() << "," << loc.get_y() << ")" << std::endl;
            }
        }
    }

}
