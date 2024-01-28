#pragma once
#include <string>
#include <iostream>

using namespace std;

// Represents a change in position.
class Move
{
public:
    Move(int start_row, int start_col, int dest_row, int dest_col) :
        _start_row(start_row), _start_col(start_col), _dest_row(dest_row), _dest_col(dest_col)
    {}

    Move(const std::string& s);

    void print() const;

private:
    int _start_row; // starting square row
    int _start_col; // starting square column

    int _dest_row;  // destination square row
    int _dest_col;  // destination square column

    friend class Position;
};