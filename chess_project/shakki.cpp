#include "shakki.h"

int nappulan_vari(int nappula)
{
	switch (nappula)
	{
	case wR: case wN: case wB: case wQ: case wK: case wP:
		return VALKEA;
		break;
	default:
		return MUSTA;
		break;
	}
}

int vastustaja(int pelaaja)
{
	if (pelaaja == VALKEA)
	{
		return MUSTA;
	}
	else
	{
		return VALKEA;
	}
}