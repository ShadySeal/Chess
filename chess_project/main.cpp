#include <iostream>
#include <string>
#include "position.h"
#include "move.h"
#include <vector>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

using namespace std;

int main() {
    // Initial position.
    Position position;
    vector<Move> moves;
    vector<Position> history;

    position.clear();
    position._board[7][4] = wK;
    position._board[7][0] = wR;
    position._board[7][7] = wR;

    enum PlayerType { HUMAN, COMPUTER };

    PlayerType whitePlayer, blackPlayer;
    char choice;
    cout << "Is white human or computer? (h/c): ";
    cin >> choice;
    whitePlayer = (choice == 'h' || choice == 'H') ? HUMAN : COMPUTER;
    cout << "Is black human or computer? (h/c): ";
    cin >> choice;
    blackPlayer = (choice == 'h' || choice == 'H') ? HUMAN : COMPUTER;

    bool canPrint = true;
    while (true) {
        moves.clear();
        position.give_moves(moves);

        if (canPrint)
        {
            position.print();
            if (position._turn == WHITE) {
                cout << "Turn: White" << endl;
            }
            else if (position._turn == BLACK) {
                cout << "Turn: Black" << endl;
            }
        }

        if ((position._turn == WHITE && whitePlayer == HUMAN) ||
            (position._turn == BLACK && blackPlayer == HUMAN)) {
            // Human player's turn
            string input;
            bool canMove = true;
            canPrint = false;

            cout << "Enter your move (e.g., a2a4): ";
            cin >> input;

            if (input == "m") {
                break;
            }
            else if (input == "moves")
            {
                canMove = false;
                cout << "Valid moves:" << endl;
                int moveNumber = 1;
                for (const Move& m : moves) {
                    cout << moveNumber << ". ";
                    m.print();
                    cout << endl;
                    moveNumber++;
                }
            }
            else if (input == "undo") {
                canMove = false;
                if (!history.empty()) {
                    canPrint = true;
                    position = history.back(); // Restore previous position
                    history.pop_back(); // Remove last position from history
                }
                else {
                    cout << "Cannot undo further. History is empty." << endl;
                    continue; // Continue command input loop
                }
            }

            if (canMove)
            {
                Move move(input);
                bool validMove = false;
                for (Move& m : moves) {
                    if (m == move) {
                        validMove = true;
                        canPrint = true;
                        break;
                    }
                }

                if (!validMove) {
                    cout << "Invalid move. Please enter a valid move." << endl;
                    continue;
                }

                history.push_back(position);
                position.make_move(move);
            }
        }
        else {
            // AI's turn
            cout << endl << "Computer is thinking..." << endl;
            MinimaxValue bestMove = position.minimax(2);
            Move move = bestMove._move;
            move.print();
            cout << endl;
            position.make_move(move);
        }
    }

    return 0;
}
