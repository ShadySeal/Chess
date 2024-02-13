#pragma once
#include <limits>
#include <map>
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
                if (_black_short_castling_allowed)
                {
                    moves.push_back(Move(0, 4, 0, 6, NA));
                }
                if (_black_long_castling_allowed)
                {
                    moves.push_back(Move(0, 4, 0, 6, NA));
                }
            }
        }
    }

    float score_end_result() const
    {
        if (_turn == WHITE)
        {
            int row, col;
            find_piece(wK, row, col);

            if (is_square_threatened(row, col, BLACK))
                return -1000000;
            else
                return 0;
        }
        else
        {
            int row, col;
            find_piece(bK, row, col);

            if (is_square_threatened(row, col, WHITE))
                return -1000000;
            else
                return 0;
        }
    }

    float evaluate() const
    {
        return 1.0 * material() + 0.05 * mobility();
    }

    static float minimax(Position& position, int depth)
    {
        vector<Move> moves;
        position.give_moves(moves);

        if (moves.size() == 0)
        {
            return position.score_end_result();
        }

        if (depth == 0)
        {
            return position.evaluate();
        }

        float best_value = position._turn == WHITE ? numeric_limits<float>:: min() : numeric_limits<float>::max();
        for (Move& s : moves)
        {
            Position new_position = position;
            new_position.make_move(s);

             float value = minimax(new_position, depth - 1);
             

             if (position._turn == WHITE && value > best_value)
             {
                 best_value = value;
             }
             else if (position._turn == BLACK && value > best_value)
             {
                 best_value = value;
             }
        }

        return best_value;
    }

    float material() const
    {
        static map<int, float> piece_values = {
            {wP, 1}, {wN, 3}, {wB, 3}, {wR, 5}, {wQ, 9},
            {wP, 1}, {wN, 3}, {wB, 3}, {wR, 5}, {wQ, 9},
            {NA, 0}
        };

        float value = 0;
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                int piece = _board[row][col];
                value += piece_values[piece];
            }
        }
        return 0; // Tarkista.
    }

    float mobility() const
    {
        vector<Move> white_moves;
        vector<Move> black_moves;

        give_every_raw_move(WHITE, white_moves);
        give_every_raw_move(BLACK, black_moves);

        return white_moves.size() - black_moves.size();
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
