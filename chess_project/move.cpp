#include "move.h"
#include "position.h"

Move::Move(const std::string& s)
{

    _start_col = s[0] - 'a';
    _start_row = '8' - s[1];
    _dest_col = s[2] - 'a';
    _dest_row = '8' - s[3];

    // tarkista, onko s:n pituus 5
    // jos on, aseta _promoted_piece
    // arvo s[4]:n perusteella:
    // wQ, wR, ...

    if (s.size() == 5)
    {
        if (_dest_row == 0)
        {
            switch (s[4])
            {
            case 'q':
                _promoted_piece = wQ;
                break;
            case 'r':
                _promoted_piece = wR;
                break;
            case 'n':
                _promoted_piece = wN;
                break;
            case 'b':
                _promoted_piece = wB;
                break;
            }
        }
        else
        {
            switch (s[4])
            {
            case 'q':
                _promoted_piece = bQ;
                break;
            case 'r':
                _promoted_piece = bR;
                break;
            case 'n':
                _promoted_piece = bN;
                break;
            case 'b':
                _promoted_piece = wB;
                break;
            }
        }
    }
/*
    if (s.substr(s.length() - 1) == "q") {
        if (position._turn == WHITE) {
            int piece = wQ;
            position._board[_dest_row][_dest_col] = bQ;
        }
        else if (_promoted_piece == bQ)
        {
            position._board[_dest_row][_dest_col] = bQ;
        }
    }
    else if (s.substr(s.length() - 1) == "r") {
        if (_promoted_piece == wR) {
            position._board[_dest_row][_dest_col] = wR;
        }
        else if (_promoted_piece == bR)
        {
            position._board[_dest_row][_dest_col] = bR;
        }
    }
    else if (s.substr(s.length() - 1) == "n") {
        if (_promoted_piece == wN) {
            position._board[_dest_row][_dest_col] = wN;
        }
        else if (_promoted_piece == bN)
        {
            position._board[_dest_row][_dest_col] = bN;
        }
    }
    else if (s.substr(s.length() - 1) == "b") {
        if (_promoted_piece == wB) {
            position._board[_dest_row][_dest_col] = wB;
        }
        else if (_promoted_piece == bB)
        {
            position._board[_dest_row][_dest_col] = bB;
        }
    }
*/
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
