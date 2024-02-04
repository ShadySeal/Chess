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
    position.give_every_raw_move(BLACK, moves);
    position.print();

    cout << "Valid moves:" << endl;

    for (Move m : moves)
    {
        m.print();
        cout << endl;
    }

    /*while (true)
    {
        position.give_every_raw_move(BLACK, moves);
        position.print();
        string input;
        cin >> input;

        if (input == "m")
        {
            break;
        }

        Move move(input);

        cout << "Valid moves:" << endl;

        bool validMove = false;

        for (Move m : moves)
        {
            if (m == move)
            {
                validMove = true;
                break;
            }

            m.print();
            cout << endl;
        }

        if (!validMove)
        {
            cout << "Invalid move. Please enter a valid move." << endl;
            continue;
        }

        position.make_move(move);
    }*/
    
    return 0;
}
