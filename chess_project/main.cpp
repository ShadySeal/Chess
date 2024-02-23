#include <iostream>
#include <string>
#include "position.h"
#include "move.h"
#include <vector>

using namespace std;

int main() {
    // Initial position.
    Position position;
    vector<Move> moves;

    while (true) {
        moves.clear();
        position.give_moves(moves);

        position.print();
        if (position._turn == WHITE) {
            cout << "Turn: White" << endl;
        }
        else if (position._turn == BLACK) {
            cout << "Turn: Black" << endl;
        }

        cout << "Valid moves:" << endl;

        int moveNumber = 1;
        for (const Move& m : moves) {
            cout << moveNumber << ". ";
            m.print();
            cout << endl;
            moveNumber++;
        }

        if (position._turn == WHITE) {
            // Human player's turn
            cout << "Enter your move (e.g., a2a4): ";
            string input;
            cin >> input;

            if (input == "m") {
                break;
            }

            Move move(input);

            bool validMove = false;

            for (Move& m : moves) {
                if (m == move) {
                    validMove = true;
                    break;
                }
            }

            if (!validMove) {
                cout << "Invalid move. Please enter a valid move." << endl;
                continue;
            }

            position.make_move(move);
        }
        else {
            //// AI's turn
            //MinimaxValue bestMove = position.minimax(2);
            //Move move = bestMove._move;
            //position.make_move(move);

            // Human player's turn
            cout << "Enter your move (e.g., a2a4): ";
            string input;
            cin >> input;

            if (input == "m") {
                break;
            }

            Move move(input);

            bool validMove = false;

            for (Move& m : moves) {
                if (m == move) {
                    validMove = true;
                    break;
                }
            }

            if (!validMove) {
                cout << "Invalid move. Please enter a valid move." << endl;
                continue;
            }

            position.make_move(move);
        }
    }

    return 0;
}
