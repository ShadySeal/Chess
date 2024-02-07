#include "move.h"

Move::Move(const std::string& s)
{
    _start_col = s[0] - 'a';
    _start_row = '8' - s[1];
    _dest_col = s[2] - 'a';
    _dest_row = '8' - s[3];
}

void Move::print() const
{
    char start_col = 'a' + _start_col;
    char start_row = '8' - _start_row;
    char dest_col = 'a' + _dest_col;
    char dest_row = '8' - _dest_row;

    string promoted_piece;

    switch (_promoted_piece)
    {
    case wQ: case bQ:
        promoted_piece = " Queen promoted.";
        break;
    case wR: case bR:
        promoted_piece = " Rook promoted.";
        break;
    case wN: case bN:
        promoted_piece = " Knight promoted.";
        break;
    case wB: case bB:
        promoted_piece = " Bishop promoted.";
        break;
    case NA:
        promoted_piece = "";
        break;
    }

    cout << start_col << start_row << " to " << dest_col << dest_row << promoted_piece;
}
