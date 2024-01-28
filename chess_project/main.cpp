#include <iostream>
#include <string>
#include "position.h"
#include "move.h"
#include <vector>

using namespace std;

int main()
{
    // Initial position.
    Position position;
    vector<Move> moves;
    position._board[5][1] = bP;
    position._board[5][3] = bP;
    position.generate_pawn_moves(6, 2, WHITE, moves);

    position.print();

    for (Move m : moves)
    {
        m.print();
        cout << endl;
    }

    return 0;
}
