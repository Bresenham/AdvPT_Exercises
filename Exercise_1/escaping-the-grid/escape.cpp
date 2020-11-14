#include <cstddef>
#include <cassert>
#include <vector>
#include <queue>

#include "Grid.hpp"
#include "Location.hpp"

// Feel free to include additional headers here!

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

int recursive_walk(const Location &loc, std::vector<Location> &current_path, std::vector< std::vector<Location> > &final_paths, const Direction &dir, const Grid &grid) {

    Location copyLoc(loc);
    copyLoc.move(dir);

    if( copyLoc.is_escape_tile(grid) ) {
        std::vector<Location> new_escape_path;
        new_escape_path.push_back(copyLoc);
        final_paths.push_back(new_escape_path);
        return final_paths.size() - 1;
    }

    if( already_gone(current_path, copyLoc) ) {
        return -1;
    }

    const std::vector<Direction> dirs = available_directions(copyLoc, grid);

    for(size_t i = 0; i < dirs.size(); ++i) {

        std::vector<Location> path;
        
        for(size_t i = 0; i < current_path.size(); ++i) {
            path.push_back(current_path.at(i));
        }

        path.push_back(copyLoc);

        const int final_path_idx = recursive_walk(copyLoc, path, final_paths, dirs.at(i), grid);
        if( final_path_idx >= 0 ) {
            final_paths.at(final_path_idx).push_back(copyLoc);
            return final_path_idx;
        }
    }

    return -1;

}

std::vector<Location> escape_small_grid(Grid &grid) {

    Location loc(1, 1);
    std::vector<Direction> dirs = available_directions(loc, grid);

    std::vector< std::vector<Location> > final_paths;

    for(const Direction &dir : dirs) {

        std::vector<Location> path;
        path.push_back(loc);

        const int ret_idx = recursive_walk(loc, path, final_paths, dir, grid);
        if( ret_idx >= 0 ) {
            final_paths.at(ret_idx).push_back(loc);
        }
    }

    std::vector<Location> shortest_path = final_paths.at(0);

    for(const std::vector<Location> &final_path : final_paths) {
        if(final_path.size() < shortest_path.size()) {
            shortest_path = final_path;
        }
    }

    return shortest_path;
}

void escape_large_grid(Grid &grid) {

    Location start(1, 1);

    std::deque<Location> queue;
    queue.push_back(start);

    std::deque<std::vector<Location>> path_queue;
    std::vector<Location> initial_path;
    initial_path.push_back(start);
    path_queue.push_back(initial_path);


    std::vector<Location> visited;

    while(true) {

        Location loc = queue.front();
        queue.pop_front();

        std::vector<Location> path = path_queue.front();
        path_queue.pop_front();

        if( loc.is_escape_tile(grid) ) {
            for(const Location &l : path) {
                grid(l.get_x(), l.get_y()) = Path;
            }
            break;
        }

        if( already_gone(visited, loc) ) {
            continue;
        }

        visited.push_back(loc);

        std::vector<Direction> directions = available_directions(loc, grid);
        
        for(const Direction &dir : directions) {

            Location l(loc);
            l.move(dir);

            queue.push_back(l);

            std::vector<Location> new_path;
            for(const Location &loc : path) {
                new_path.push_back(loc);
            }

            new_path.push_back(l);

            path_queue.push_back(new_path);
        }

    }
}

void Grid::escape() {
    Grid& grid = *this;
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.

    if(grid.rows() * grid.cols() < 250) {
        std::vector<Location> path = escape_small_grid(grid);
        for(const Location &loc : path) {
            grid(loc.get_x(), loc.get_y()) = Path;
        }
    } else {
        escape_large_grid(grid);
    }


    grid.print(std::cout);

}
