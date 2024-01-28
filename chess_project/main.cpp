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
    position.generate_rook_moves(6, 3, BLACK, moves);

    position.print();

    for (Move m : moves)
    {
        m.print();
        cout << endl;
    }

    return 0;
}
