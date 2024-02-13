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

    float arvo = Position::minimax(position, 2);
    cout << arvo;

    bool canPrint = true;
    while (true)
    {
        moves.clear();
        /*position.clear();
        position._board[1][2] = wP;*/
        position.give_moves(moves);

        if (canPrint)
        {
            position.print();
            if (position._turn == WHITE)
            {
                cout << "Turn: White" << endl;
            }
            else if (position._turn == BLACK)
            {
                cout << "Turn: Black" << endl;
            }

            cout << "Valid moves:" << endl;

            static int amount = 1;
            for (Move& m : moves)
            {

                cout << amount << ". ";
                m.print();
                amount++;
                cout << endl;
            }
            amount = 1;
        }
        
        string input;
        cin >> input;

        if (input == "m")
        {
            break;
        }

        Move move(input);

        bool validMove = false;

        for (Move& m : moves)
        {
            if (m == move)
            {
                validMove = true;
                canPrint = true;
                break;
            }
        }

        if (!validMove)
        {
            cout << "Invalid move. Please enter a valid move." << endl;
            canPrint = false;
            continue;
        }

        position.make_move(move);
    }
    
    return 0;
}
