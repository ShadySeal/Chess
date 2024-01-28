#include "position.h"
#include <vector>

// Clears the board.
void Position::clear()
{
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
            _board[row][col] = NA;
}

void Position::generate_raw_moves_in_direction(int row, int col, int row_change, int col_change, int player,
    int max_steps, bool can_capture, bool must_capture, std::vector<Move>& moves) const
{
    int current_row = row;
    int current_col = col;
    int steps = 0;

    while (steps < max_steps)
    {
        current_row += row_change;
        current_col += col_change;

        if (current_row < 0 || current_row >= 8 || current_col < 0 || current_col >= 8)
        {
            return;
        }

        // Empty square?
        if (_board[current_row][current_col] == NA)
        {
            if (must_capture)
            {
                break;
            }
            moves.push_back(Move(row, col, current_row, current_col));
            steps++;
            continue;
        }

        // Colliding with own piece?
        if (piece_color(_board[current_row][current_col]) == player)
            break;

        // Capture opponent's piece.
        if (can_capture)
        {
            moves.push_back(Move(row, col, current_row, current_col));
        }
        break;
    }
}

void Position::generate_pawn_moves(int row, int col, int player,
    std::vector<Move>& moves)
{
    if (player == WHITE)
    {
        if (row == 6)
        {
            generate_raw_moves_in_direction(row, col, -1, 0, player, 1, false, false, moves);
            generate_raw_moves_in_direction(row, col, -2, 0, player, 1, false, false, moves);
        }
        else
        {
            generate_raw_moves_in_direction(row, col, -1, 0, player, 1, false, false, moves);
        }

        if (_board[row - 1][col - 1] != NA && piece_color(_board[row - 1][col - 1]) != player)
        {
            generate_raw_moves_in_direction(row, col, -1, -1, player, 1, true, false, moves);
        }

        if (_board[row - 1][col + 1] != NA && piece_color(_board[row - 1][col + 1]) != player)
        {
            generate_raw_moves_in_direction(row, col, -1, 1, player, 1, true, false, moves);
        }
    }

    if (player == BLACK)
    {
        if (row == 6)
        {
            generate_raw_moves_in_direction(row, col, 1, 0, player, 1, false, false, moves);
            generate_raw_moves_in_direction(row, col, 2, 0, player, 1, false, false, moves);
        }
        else
        {
            generate_raw_moves_in_direction(row, col, 1, 0, player, 1, false, false, moves);
        }

        if (_board[row + 1][col - 1] != NA && piece_color(_board[row + 1][col - 1]) != player)
        {
            generate_raw_moves_in_direction(row, col, 1, -1, player, 1, true, false, moves);
        }

        if (_board[row + 1][col + 1] != NA && piece_color(_board[row + 1][col + 1]) != player)
        {
            generate_raw_moves_in_direction(row, col, 1, 1, player, 1, true, false, moves);
        }
    }
}

void Position::generate_rook_moves(int row, int col, int player,
    std::vector<Move>& moves)
{
    generate_raw_moves_in_direction(row, col, -1, 0, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 0, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, -1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, 1, player, 7, true, false, moves);
}

void Position::generate_bishop_moves(int row, int col, int player,
    std::vector<Move>& moves)
{
    generate_raw_moves_in_direction(row, col, -1, -1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 1, player, 7, true, false, moves);
}

void Position::generate_knight_moves(int row, int col, int player,
    std::vector<Move>& moves)
{
    generate_raw_moves_in_direction(row, col, -2, -1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, -2, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -2, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 2, -1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 2, 1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 2, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 2, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, -2, 1, player, 1, true, false, moves);
}

void Position::generate_queen_moves(int row, int col, int player,
    std::vector<Move>& moves)
{
    generate_raw_moves_in_direction(row, col, -1, -1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 0, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, -1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, 1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -1, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 0, player, 7, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 1, player, 7, true, false, moves);
}

void Position::generate_king_moves(int row, int col, int player,
    std::vector<Move>& moves)
{
    generate_raw_moves_in_direction(row, col, -1, -1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 0, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, -1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, 1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -1, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 0, player, 1, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 1, player, 1, true, false, moves);
}


// Makes the given move on the board. Assumes that the move is legal.
void Position::make_move(const Move& m)
{
    // Save the piece in the starting square.
    int piece = _board[m._start_row][m._start_col];

    // Clear the starting square.
    _board[m._start_row][m._start_col] = NA;

    // Place the original piece in the destination square.
    _board[m._dest_row][m._dest_col] = piece;

    _turn = opponent(_turn);
}

void Position::print() const
{
    const string pieces[] =
    { "R", "N", "B", "Q", "K", "P", "r", "n", "b", "q", "k", "p", " " };

    for (int i = 0; i < 8; i++) {
        cout << " +---+---+---+---+---+---+---+---+" << endl;
        cout << 8 - i << "| ";
        for (int j = 0; j < 8; j++) {
            cout << pieces[_board[i][j]] << " | ";
        }
        cout << endl;
    }
    cout << " +---+---+---+---+---+---+---+---+" << endl;
    cout << "   A   B   C   D   E   F   G   H" << endl;
}
