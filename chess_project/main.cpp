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

    /*position.clear();
    position._board[0][4] = bK;
    position._board[0][0] = bR;
    position._board[0][7] = bR;
    position._board[0][5] = bP;
    position._board[0][3] = bP;*/

    enum PlayerType { HUMAN, COMPUTER };

    PlayerType whitePlayer, blackPlayer;
    wstring choice;
    wcout << "Is white human or computer? (h/c): ";
    wcin >> choice;
    whitePlayer = (choice == L"h" || choice == L"H") ? HUMAN : COMPUTER;
    wcout << "Is black human or computer? (h/c): ";
    wcin >> choice;
    blackPlayer = (choice == L"h" || choice == L"H") ? HUMAN : COMPUTER;

    bool canPrint = true;
    bool canMove = true;
    while (canMove) {
        moves.clear();
        position.give_moves(moves);

        if (canPrint)
        {
            position.print();
            if (position._turn == WHITE) {
                wcout << "Turn: White" << endl;
            }
            else if (position._turn == BLACK) {
                wcout << "Turn: Black" << endl;
            }
        }

        if ((position._turn == WHITE && whitePlayer == HUMAN) ||
            (position._turn == BLACK && blackPlayer == HUMAN)) {
            // Human player's turn
            wstring input;
            bool canMove = true;
            canPrint = false;

            wcout << "Enter your move (e.g., a2a4): ";
            wcin >> input;

            if (input == L"m") {
                break;
            }
            else if (input == L"moves")
            {
                canMove = false;
                wcout << "Valid moves:" << endl;
                int moveNumber = 1;
                int movesAvailable = 0;
                for (const Move& m : moves) {
                    wcout << moveNumber << ". ";
                    m.print();
                    wcout << endl;
                    moveNumber++;
                    movesAvailable++;
                }
                if (movesAvailable == 0)
                {
                    wcout << "Check Mate! " << position._turn << " loses.";
                }
            }
            else if (input == L"undo") {
                canMove = false;
                if (!history.empty()) {
                    canPrint = true;
                    position = history.back(); // Restore previous position
                    history.pop_back(); // Remove last position from history
                }
                else {
                    wcout << "Cannot undo further. History is empty." << endl;
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
                    wcout << "Invalid move. Please enter a valid move." << endl;
                    continue;
                }

                history.push_back(position);
                position.make_move(move);
            }
        }
        else {
            // AI's turn
            wcout << endl << "Computer is thinking..." << endl;
            MinimaxValue bestMove = position.minimax(2);
            Move move = bestMove._move;
            move.print();
            wcout << endl;
            position.make_move(move);
        }
    }

    return 0;
}
