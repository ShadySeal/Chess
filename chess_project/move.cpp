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
    static int i = 1;
    char start_col = 'a' + _start_col;
    char start_row = '8' - _start_row;
    char dest_col = 'a' + _dest_col;
    char dest_row = '8' - _dest_row;

    cout << i << ". " << start_col << start_row << dest_col << dest_row;
    i++;
}
