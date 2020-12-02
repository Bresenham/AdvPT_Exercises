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

/**
 * Returns all available directions, starting from a position 'loc' in Grid 'grid'
 * 
 */
std::vector<Direction> available_directions(Location loc, const Grid &grid) {

    std::vector<Direction> dirs;

    for(const Direction &dir : ALL_DIRS) {

        Location _loc = loc.move(dir);

        if( _loc.is_valid(grid) ) {
            dirs.push_back(dir);
        }
    }

    return dirs;
}

/**
 * Check whether 'path' contains Location 'loc'
 */
bool already_gone(const std::vector<Location> &path, const Location &loc) {

    for(const Location &p_loc : path) {
        if( p_loc == loc ) {
            return true;
        }
    }

    return false;
}

/**
 * Recursively travels the Grid 'grid' starting from Location 'loc' with path 'current_path'.
 * 'final_paths' contains all valid paths and is updated if a new path is found. In the end, the shortest path will be chosen.
 */
int recursive_walk(Location loc, std::vector<Location> &current_path, std::vector< std::vector<Location> > &final_paths, const Direction &dir, const Grid &grid) {

    Location _loc = loc.move(dir);

    /* Stop recursion if we escaped the grid */
    if( _loc.is_escape_tile(grid) ) {

        std::vector<Location> new_escape_path;
        new_escape_path.push_back(_loc);

        final_paths.push_back(new_escape_path);

        return final_paths.size() - 1;

    }

    /* If we already visited this tile, end this recursive path */
    if( already_gone(current_path, _loc) ) {
        return -1;
    }

    const std::vector<Direction> dirs = available_directions(_loc, grid);

    /* Start new recursive walks from all available directions */
    for(size_t i = 0; i < dirs.size(); ++i) {

        /* All new recursive walks branch out from this existing one */
        std::vector<Location> path(current_path);
        path.push_back(_loc);

        const int final_path_idx = recursive_walk(_loc, path, final_paths, dirs.at(i), grid);

        /* If recursive call was successfull (= escaped the grid), add path to list of successfull paths */
        if( final_path_idx >= 0 ) {

            final_paths.at(final_path_idx).push_back(_loc);

            return final_path_idx;

        }
    }

    return -1;
}

std::vector<Location> escape_small_grid(Grid &grid) {

    /* Start our journey at (1,1) */
    Location loc(1, 1);
    std::vector<Direction> dirs = available_directions(loc, grid);

    std::vector< std::vector<Location> > final_paths;

    /* Prepare initial branching */
    for(const Direction &dir : dirs) {

        std::vector<Location> path;
        path.push_back(loc);

        const int ret_idx = recursive_walk(loc, path, final_paths, dir, grid);
        if( ret_idx >= 0 ) {
            final_paths.at(ret_idx).push_back(loc);
        }
    }

    std::vector<Location> shortest_path = final_paths.at(0);

    /* Search for shortest path and return */
    for(const std::vector<Location> &final_path : final_paths) {
        if(final_path.size() < shortest_path.size()) {
            shortest_path = final_path;
        }
    }

    return shortest_path;
}

/**
 * This is basically a breadth-first search approach
 */
void escape_large_grid(Grid &grid) {

    Location start(1, 1);

    std::deque<Location> remaining_locations;
    remaining_locations.push_back(start);

    std::vector<Location> initial_path;
    initial_path.push_back(start);

    std::deque< std::vector<Location> > path_of_current_location;
    path_of_current_location.push_back(initial_path);

    std::vector<Location> visited;

    while(true) {

        Location loc = remaining_locations.front();
        remaining_locations.pop_front();

        std::vector<Location> path = path_of_current_location.front();
        path_of_current_location.pop_front();

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
        
        for(const Direction &dir : available_directions(loc, grid)) {

            Location _loc = loc.move(dir);

            remaining_locations.push_back(_loc);

            std::vector<Location> new_path;
            for(const Location &__loc : path) {
                new_path.push_back(__loc);
            }

            new_path.push_back(_loc);

            path_of_current_location.push_back(new_path);
        }

    }
}

void Grid::escape() {

    Grid& grid = *this;
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.

    /* Fully recursive approach takes too long for larger grid */
    if(grid.rows() * grid.cols() < 250) {

        std::vector<Location> path = escape_small_grid(grid);
        for(const Location &loc : path) {
            grid(loc.get_x(), loc.get_y()) = Path;
        }

    } else { escape_large_grid(grid); }


    grid.print(std::cout);

}
