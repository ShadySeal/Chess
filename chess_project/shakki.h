#pragma once

// Pelaajat.
enum { VALKEA, MUSTA };

// Vakioarvot eri nappululoille (NA = tyhjä ruutu).
enum { wR, wN, wB, wQ, wK, wP, bR, bN, bB, bQ, bK, bP, NA };

int nappulan_vari(int nappula);

// Plauttaa vastustajan.
int vastustaja(int pelaaja);