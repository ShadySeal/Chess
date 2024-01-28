#pragma once

// Players.
enum { WHITE, BLACK };

// Constants for different pieces (NA = empty square).
enum { wR, wN, wB, wQ, wK, wP, bR, bN, bB, bQ, bK, bP, NA };

int piece_color(int piece);

// Returns the opponent.
int opponent(int player);
