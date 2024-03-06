#pragma once
#include "chess.h"
#include <string>
#include <iostream>

using namespace std;

// Represents a change in position.
class Move
{
public:
    Move()
    {}

    Move(int start_row, int start_col, int dest_row, int dest_col, int promoted_piece) :
        _start_row(start_row), _start_col(start_col), _dest_row(dest_row), _dest_col(dest_col), _promoted_piece(promoted_piece)
    {}

    Move(const std::string& s);

    void print() const;

    bool operator==(const Move& rhs)
    {
        if (_start_row == rhs._start_row && _start_col == rhs._start_col
            && _dest_row == rhs._dest_row && _dest_col == rhs._dest_col)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int _start_row; // starting square row
    int _start_col; // starting square column

    int _dest_row;  // destination square row
    int _dest_col;  // destination square column

    int _promoted_piece = NA;

    friend class Position;
};