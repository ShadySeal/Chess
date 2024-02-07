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

    void generate_pawn_moves(int row, int col, int player,
        std::vector<Move>& moves) const;

    void generate_rook_moves(int row, int col, int player,
        std::vector<Move>& moves) const;

    void generate_bishop_moves(int row, int col, int player,
        std::vector<Move>& moves) const;

    void generate_knight_moves(int row, int col, int player,
        std::vector<Move>& moves) const;

    void generate_queen_moves(int row, int col, int player,
        std::vector<Move>& moves) const;

    void generate_king_moves(int row, int col, int player,
        std::vector<Move>& moves) const;

    // Generate possible raw moves for a piece in a specific direction.
    void generate_raw_moves_in_direction(int row, int col, int row_change, int col_change,
        int player, int max_steps, int promoted_piece, bool can_capture, bool must_capture, std::vector<Move>& moves) const;

    void give_every_raw_move(int player, std::vector<Move>& moves) const;

    void find_piece(int piece, int& row, int& col) const
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (_board[i][j] == piece)
                {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

    bool is_square_threatened(int row, int col, int enemy_player) const
    {
        vector<Move> enemy_moves;
        give_every_raw_move(enemy_player, enemy_moves);
        

        for (Move& m : enemy_moves)
        {
            if (m._dest_row == row && m._dest_col == col)
            {
                return true;
            }
        }
        return false;
    }

    void give_moves(std::vector<Move>& moves) const
    {
        int king = _turn == WHITE ? wK : bK;
        int player = _turn;
        int enemy = opponent(player);

        std::vector<Move> raw_moves;
        give_every_raw_move(player, raw_moves);
        give_castlings(player, raw_moves);

        for (Move& rm : raw_moves)
        {
            Position test_position = *this;

            test_position.make_move(rm);

            int row, col;
            test_position.find_piece(king, row, col);

            if (!test_position.is_square_threatened(row, col, enemy))
            {
                moves.push_back(rm);
            }
        }
    }

    void give_castlings(int player, std::vector<Move>& moves) const
    {
        if (player == WHITE)
        {
            if (_board[7][5] == NA && _board[7][6] == NA &&
                !is_square_threatened(7, 4, BLACK) && !is_square_threatened(7, 5, BLACK))
            {
                if (_white_short_castling_allowed)
                {
                    moves.push_back(Move(7, 4, 7, 6, NA));
                }
                if (_white_long_castling_allowed)
                {
                    moves.push_back(Move(7, 4, 7, 6, NA));
                }
                
            }
        }
        else
        {
            if (_board[0][5] == NA && _board[0][6] == NA &&
                !is_square_threatened(0, 4, WHITE) && !is_square_threatened(0, 5, WHITE))
            {
                if (_white_short_castling_allowed)
                {
                    moves.push_back(Move(0, 4, 0, 6, NA));
                }
                if (_white_long_castling_allowed)
                {
                    moves.push_back(Move(0, 4, 0, 6, NA));
                }
            }
        }
    }

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

    bool _white_short_castling_allowed = true;
    bool _white_long_castling_allowed = true;
    bool _black_short_castling_allowed = true;
    bool _black_long_castling_allowed = true;

    int double_step = -1;
};
