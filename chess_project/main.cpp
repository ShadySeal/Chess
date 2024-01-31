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
        position.print();
        string input;
        cin >> input;

        if (input == "m")
        {
            break;
        }

        Move move(input);
        position.make_move(move);
        
        for (Move m : moves)
        {
            m.print();
            cout << endl;
        }
    }*/
    
    return 0;
}
