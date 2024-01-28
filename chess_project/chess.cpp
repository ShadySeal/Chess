#include "chess.h"

int piece_color(int piece)
{
    switch (piece)
    {
    case wR: case wN: case wB: case wQ: case wK: case wP:
        return WHITE;
        break;
    default:
        return BLACK;
        break;
    }
}

int opponent(int player)
{
    if (player == WHITE)
    {
        return BLACK;
    }
    else
    {
        return WHITE;
    }
}
