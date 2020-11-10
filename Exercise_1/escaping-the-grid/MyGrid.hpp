#pragma once

#include "Grid.hpp"

class MyGrid : public Grid {
public:

    // The Constructor
    //
    // Constructs a grid with the given size and initial tile.
    MyGrid(size_t rows, size_t cols, const Tile& initialTile);

    // The Copy Constructor
    //
    // Constructs a grid with the same size and contents as the supplied
    // other grid.
    MyGrid(const MyGrid&);

    // The Move Constructor
    //
    // Constructs a grid with the same size and contents as tha supplied
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

    size_t rows() const override;

    size_t cols() const override;

    bool validPosition(size_t row, size_t col) const noexcept override;

    Tile& operator()(size_t row, size_t col) override;

    const Tile& operator()(size_t row, size_t col) const override;

    void print(std::ostream&) const override;
    static MyGrid read(std::istream&);

protected:
    // TODO Add custom member functions and variables here:
};
