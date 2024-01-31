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
    cout << i << ". (" << _dest_row << ", " << _dest_col << ")";
    i++;
}
