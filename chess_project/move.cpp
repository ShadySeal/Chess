#include "move.h"
#include "position.h"

Move::Move(const std::wstring& s)
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
}

void Move::print() const
{
    char start_col = 'a' + _start_col;
    char start_row = '8' - _start_row;
    char dest_col = 'a' + _dest_col;
    char dest_row = '8' - _dest_row;

    wstring promoted_piece;

    switch (_promoted_piece)
    {
    case wQ: case bQ:
        promoted_piece = L" Queen promoted.";
        break;
    case wR: case bR:
        promoted_piece = L" Rook promoted.";
        break;
    case wN: case bN:
        promoted_piece = L" Knight promoted.";
        break;
    case wB: case bB:
        promoted_piece = L" Bishop promoted.";
        break;
    case NA:
        promoted_piece = L"";
        break;
    }

    wcout << start_col << start_row << " to " << dest_col << dest_row << promoted_piece;
}
