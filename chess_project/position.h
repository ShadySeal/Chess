#pragma once
#include "chess.h"
#include "move.h"
#include <vector>

class Position
{
public:

    void clear();
    void make_move(const Move& m);

    // Prints the chessboard as ASCII graphics.
    void print() const;

    void add_move(int row, int col, int dest_row, int dest_col,
        std::vector<Move>& moves, int player);
    void generate_rook_moves(int row, int col, int player,
        std::vector<Move>& moves);

    // Generate possible raw moves for a piece in a specific direction.
    void generate_raw_moves_in_direction(int row, int col, int row_change, int col_change,
        int player, int max_steps, bool can_capture, bool must_capture, std::vector<Move>& moves) const;

    // Chessboard pieces. Indexing [row][col], for example:
    //
    // [0][0] : top-left corner ("a8")
    // [7][0] : bottom-left corner ("a1")
    // [7][7] : bottom-right corner ("h1")
    //

    int _board[8][8] = {
        { bR, bN, bB, bQ, bK, bB, bN, bR },
        { bP, bP, bP, bP, bP, bP, bP, bP },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { wP, wP, wP, wP, wP, wP, wP, wP },
        { wR, wN, wB, wQ, wK, wB, wN, wR }
    };

    int _turn = WHITE;
};