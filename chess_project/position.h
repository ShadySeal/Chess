#pragma once
#include <limits>
#include <map>
#include "chess.h"
#include "move.h"
#include <vector>

// Minimax-funktion palauttama arvo. Sis‰lt‰‰ sek‰
// minimax-arvon ett‰ sit‰ vastaavan parhaan siirron.
class MinimaxValue
{
public:
	MinimaxValue(float arvo, Move move) :
		_value(arvo), _move(move)
	{}

	float	_value;
	Move	_move;
};

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
                    moves.push_back(Move(7, 4, 7, 1, NA));
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
                    moves.push_back(Move(0, 4, 0, 1, NA));
                }
            }
        }
    }

	// Pisteytt‰‰ pelin lopputuloksen seuraavasti:
	//
	// Valkea tehnyt matin			1000000
	// Tasapeli (patti)				0
	// Musta tehnyt matin		   -1000000
	//
	// Funktiota kutsutaan, kun asemassa ei ole en‰‰ yht‰‰n laillista
	// siirtoa (anna_siirrot on palattanyt tyhj‰n siirtovektorin).
	//
	float score_end_results() const
	{
		if (_turn == WHITE)
		{
			// Etsit‰‰n valkean kuningas
			int row, col;
			find_piece(wK, row, col);

			// Onko valkean kuningas uhattu?
			if (is_square_threatened(row, col, BLACK))
				return -1000000; // musta on tehnyt matin
			else
				return 0; // patti
		}
		else
		{
			// TODO
			// samat mustille (palautetaan 100000 tai 0).
			// Etsit‰‰n mustan kuningas
			int row, col;
			find_piece(bK, row, col);

			// Onko mustan kuningas uhattu?
			if (is_square_threatened(row, col, WHITE))
				return 1000000; // musta on tehnyt matin
			else
				return 0; // patti
		}
	}


	// Pisteytt‰‰ shakkiaseman heuristisesti.
	float evaluate() const
	{
		return 1.0f * material() + 0.1f * mobility();

		// TODO
		// t‰ydent‰k‰‰ halutessanne uusilla pisteytett‰vill‰ aseman piirteill‰
	}

	//
	// Palauttaa aseman minimax-arvon. Syvyys m‰‰ritt‰‰,
	// kuinka monta asekelta syvemm‰lle pelipuuta k‰yd‰‰n l‰pi.
	//
	// Testaaminen esim. p‰‰ohjelmasta:
	//
	// Asema asema;
	// MinimaxArvo arvo = asema.minimax(4);
	// 
	// Nyt tietokoneen siirto saadaan pelattua n‰in:
	// asema.tee_siirto(arvo._siirto);
	//
	MinimaxValue minimax(int depth)
	{
		// Generoidaan aseman siirrot.
		vector<Move> moves;
		give_moves(moves);

		if (moves.size() == 0)
		{
			// Rekursion kantatapaus 1:
			// peli on p‰‰ttynyt (ei yht‰‰n laillista siirtoa).
			return MinimaxValue(score_end_results(), Move());
		}

		if (depth == 0)
		{
			// Rekursion kantatapaus 2:
			// ollaan katkaisusyvyydess‰.
			return MinimaxValue(evaluate(), Move());
		}

		// Siirtoja on j‰ljell‰ ja ei olla katkaisusyvyydess‰,
		// joten kokeillaan yksitellen mahdollisia siirtoja,
		// ja kutsutaan minimax:a kullekin seuraaja-asemalle.
		// Otetaan paras minimax-arvo talteen (alustetaan
		// paras_arvo mahdollisimman huonoksi siirtovuoroisen
		// pelaajan kannalta).
		float best_value = _turn == WHITE ?
			numeric_limits<float>::lowest() : numeric_limits<float>::max();
		Move best_move;
		for (Move& s : moves)
		{
			Position new_pos = *this;
			new_pos.make_move(s);

			// Rekursioasekel: kutsutaan minimax:ia seuraaja-asemalle.
			MinimaxValue value = new_pos.minimax(depth - 1);
				
			// Jos saatiin paras arvo, otetaan se talteen.
			if (_turn == WHITE && value._value > best_value)
			{
				best_value = value._value;
				best_move = s;
			}
			else if (_turn == BLACK && value._value < best_value)
			{
				best_value = value._value;
				best_move = s;
			}
		}

		// Palautetaan paras arvo.
		return MinimaxValue(best_value, best_move);
	}



	// Laskee materiaalitasapainon (valkean nappuloiden arvo - mustan nappuloiden arvo).
	// Nappuloiden arvot:
	//
	// sotilas		1
	// ratsu		3
	// l‰hetti		3
	// torni		5
	// daami		9
	//
	float material() const
	{
		// Liitet‰‰n nappulatyyppeihin niiden arvot.
		static map<int, float> piece_values = {
			{wP,  1.0f}, {wN,  3.0f}, {wB,  3.0f}, {wR,  5.0f}, {wQ,  9.0f},
			{bP, -1.0f}, {bN, -3.0f}, {bB, -3.0f}, {bR, -5.0f}, {bQ, -9.0f},
			{NA,  0.0f}
		};

		float value = 0;
		for (int row = 0; row < 8; ++row)
			for (int col = 0; col < 8; ++col)
			{
				int piece = _board[row][col];
				value += piece_values[piece];
			}
		return value;
	}


	// Palauttaa valkean ja mustan (raaka)siirtojen lukum‰‰rien erotuksen.
	float mobility() const
	{
		vector<Move> white_moves;
		vector<Move> black_moves;
			
		// Funktion totetus on raskas, koska generoidaan raakasiirtoja.
		// TODO: voisiko optimoida optimoida jotenkin?
		give_every_raw_move(WHITE, white_moves);
		give_every_raw_move(BLACK, black_moves);

		return (float)white_moves.size() - (float)black_moves.size();
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
