#include "position.h"
#include <vector>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

// Clears the board.
void Position::clear()
{
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
            _board[row][col] = NA;
}

void Position::generate_raw_moves_in_direction(int row, int col, int row_change, int col_change, int player,
    int max_steps, int promoted_piece, bool can_capture, bool must_capture, std::vector<Move>& moves) const
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
            moves.push_back(Move(row, col, current_row, current_col, promoted_piece));
            steps++;
            continue;
        }

        // Colliding with own piece?
        if (piece_color(_board[current_row][current_col]) == player)
            break;

        // Capture opponent's piece.
        if (can_capture)
        {
            moves.push_back(Move(row, col, current_row, current_col, promoted_piece));
        }
        break;
    }
}

void Position::generate_pawn_moves(int row, int col, int player,
    std::vector<Move>& moves) const
{
    vector<Move> pawn_moves;

    if (player == WHITE)
    {
        if (row == 6)
        {
            generate_raw_moves_in_direction(row, col, -1, 0, player, 1, NA, false, false, pawn_moves);
            generate_raw_moves_in_direction(row, col, -2, 0, player, 1, NA, false, false, pawn_moves);
        }
        else
        {
            generate_raw_moves_in_direction(row, col, -1, 0, player, 1, NA, false, false, pawn_moves);
        }

        if (_board[row - 1][col - 1] != NA)
        {
            generate_raw_moves_in_direction(row, col, -1, -1, player, 1, NA, true, false, pawn_moves);
        }

        if (_board[row - 1][col + 1] != NA)
        {
            generate_raw_moves_in_direction(row, col, -1, 1, player, 1, NA, true, false, pawn_moves);
        }
    }

    if (player == BLACK)
    {
        if (row == 1)
        {
            generate_raw_moves_in_direction(row, col, 1, 0, player, 1, NA, false, false, pawn_moves);
            generate_raw_moves_in_direction(row, col, 2, 0, player, 1, NA, false, false, pawn_moves);
        }
        else
        {
            generate_raw_moves_in_direction(row, col, 1, 0, player, 1, NA, false, false, pawn_moves);
        }

        if (_board[row + 1][col - 1] != NA)
        {
            generate_raw_moves_in_direction(row, col, 1, -1, player, 1, NA, true, false, pawn_moves);
        }

        if (_board[row + 1][col + 1] != NA)
        {
            generate_raw_moves_in_direction(row, col, 1, 1, player, 1, NA, true, false, pawn_moves);
        }
    }

    // pawn-moves vektorissa on sotilaan siirrot
    for (Move& m : pawn_moves)
    {
        if (m._dest_row != 0 && m._dest_row != 7)
            moves.push_back(m);
        else if (m._dest_row == 0)
        {
            // White gets promoted.
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, wQ));
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, wR));
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, wN));
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, wB));
        }
        else
        {
            // Black gets promoted.
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, bQ));
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, bR));
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, bN));
            moves.push_back(Move(m._start_row, m._start_col, m._dest_row, m._dest_col, bB));
        }

        if (double_step != -1 && _board[m._start_row][m._start_col - 1] == bP || _board[m._start_row][m._start_col + 1] == bP && _board[m._start_row][m._start_col] == wP && m._start_row == 3)
        {
            moves.push_back(Move(m._start_row, m._dest_col, 2, double_step, NA));
        }
        else if (double_step != -1 && _board[m._start_row][m._start_col - 1] == wP || _board[m._start_row][m._start_col + 1] == wP && _board[m._start_row][m._start_col] == bP && m._start_row == 4)
        {
            moves.push_back(Move(m._start_row, m._dest_col, 5, double_step, NA));
        }
    }
}

void Position::generate_rook_moves(int row, int col, int player,
    std::vector<Move>& moves) const
{
    generate_raw_moves_in_direction(row, col, -1, 0, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 0, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, -1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, 1, player, 7, NA, true, false, moves);
}

void Position::generate_bishop_moves(int row, int col, int player,
    std::vector<Move>& moves) const
{
    generate_raw_moves_in_direction(row, col, -1, -1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 1, player, 7, NA, true, false, moves);
}

void Position::generate_knight_moves(int row, int col, int player,
    std::vector<Move>& moves) const
{
    generate_raw_moves_in_direction(row, col, -2, -1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, -2, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -2, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 2, -1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 2, 1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 2, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 2, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -2, 1, player, 1, NA, true, false, moves);
}

void Position::generate_queen_moves(int row, int col, int player,
    std::vector<Move>& moves) const
{
    generate_raw_moves_in_direction(row, col, -1, -1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 0, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, -1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, 1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -1, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 0, player, 7, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 1, player, 7, NA, true, false, moves);
}

void Position::generate_king_moves(int row, int col, int player,
    std::vector<Move>& moves) const
{
    generate_raw_moves_in_direction(row, col, -1, -1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 0, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, -1, 1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, -1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 0, 1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, -1, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 0, player, 1, NA, true, false, moves);
    generate_raw_moves_in_direction(row, col, 1, 1, player, 1, NA, true, false, moves);
}

void Position::give_every_raw_move(int player, std::vector<Move>& moves) const
{
    if (player == WHITE)
    {
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                int piece = _board[row][col];

                switch (piece)
                {
                case wR:
                    generate_rook_moves(row, col, player, moves);
                    break;
                case wN:
                    generate_knight_moves(row, col, player, moves);
                    break;
                case wB:
                    generate_bishop_moves(row, col, player, moves);
                    break;
                case wQ:
                    generate_queen_moves(row, col, player, moves);
                    break;
                case wK:
                    generate_king_moves(row, col, player, moves);
                    break;
                case wP:
                    generate_pawn_moves(row, col, player, moves);
                    break;
                }
            }
        }
    }

    if (player == BLACK)
    {
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                int piece = _board[row][col];

                switch (piece)
                {
                case bR:
                    generate_rook_moves(row, col, player, moves);
                    break;
                case bN:
                    generate_knight_moves(row, col, player, moves);
                    break;
                case bB:
                    generate_bishop_moves(row, col, player, moves);
                    break;
                case bQ:
                    generate_queen_moves(row, col, player, moves);
                    break;
                case bK:
                    generate_king_moves(row, col, player, moves);
                    break;
                case bP:
                    generate_pawn_moves(row, col, player, moves);
                    break;
                }
            }
        }
    }
}

// Makes the given move on the board. Assumes that the move is legal.
void Position::make_move(const Move& m)
{
    vector<Move> moves;

    // Save the piece in the starting square.
    int piece = _board[m._start_row][m._start_col];

    // Clear the starting square.
    _board[m._start_row][m._start_col] = NA;

    bool isPawn = (piece == wP || piece == bP);

    if (isPawn && m._start_col != m._dest_col && _board[m._dest_row][m._dest_col] == NA)
    {
        _board[m._start_row][m._dest_col] = NA;
    }

    // Place the original piece in the destination square.
    if (m._promoted_piece == NA)
    {
        _board[m._dest_row][m._dest_col] = piece;
    }
    else
    {
        _board[m._dest_row][m._dest_col] = m._promoted_piece;
    }

    _turn = opponent(_turn);

    if (piece == wK && m._start_row == 7 && m._start_col == 4 && m._dest_row == 7 && m._dest_col == 6 )
    {
        if (_board[7][7] == wR)
        {
            _board[7][7] = NA;
            _board[7][5] = wR;
        }
        else if (_board[7][0] == wR)
        {
            _board[7][7] = NA;
            _board[7][2] = wR;
        }
        
    }
    else if (piece == bK && m._start_row == 0 && m._start_col == 4 && m._dest_row == 0 && m._dest_col == 6)
    {
        _board[0][7] = NA;
        _board[0][5] = bR;
    }

    switch (piece)
    {
    case wK:
        _white_short_castling_allowed = false;
        _white_long_castling_allowed = false;
        break;
    case bK:
        _black_short_castling_allowed = false;
        _black_long_castling_allowed = false;
        break;
    }

    if (m._start_row == 7 || m._start_col == 7 || m._dest_row == 7 || m._dest_col == 7)
    {
        _white_short_castling_allowed = false;
    }
    else if (m._start_row == 0 || m._start_col == 0 || m._dest_row == 0 || m._dest_col == 0)
    {
        _black_short_castling_allowed = false;
    }

    

    if (isPawn && abs(m._start_row - m._dest_row) == 2)
    {
        double_step = m._dest_col;
    }
    else
    {
        double_step = -1;
    }

}

void Position::print() const
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    WORD defaultAttributes = consoleInfo.wAttributes;

    _setmode(_fileno(stdout), _O_U16TEXT);
    const wstring pieces[] =
    { L"\u2656", L"\u2658", L"\u2657", L"\u2655", L"\u2654", L"\u2659",
        L"\u265C", L"\u265E", L"\u265D", L"\u265B", L"\u265A", L"\u265F", L" " };

    for (int i = 0; i < 8; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultAttributes);
        wcout << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            else
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    BACKGROUND_INTENSITY | BACKGROUND_GREEN);

            wcout << "     ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultAttributes);
        }

        wcout << endl << "  ";

        for (int j = 0; j < 8; j++) {
            
            if ((i + j) % 2 == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    BACKGROUND_INTENSITY | BACKGROUND_GREEN);
            }
            
            wcout << "  " << pieces[_board[i][j]] << "  ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultAttributes);
        }
        wcout << endl;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultAttributes);
    wcout << "    A    B    C    D    E    F    G    H" << endl << endl;
}
