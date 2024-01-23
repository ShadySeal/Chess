#include <iostream>
#include <string>
#include "asema.h"
#include "siirto.h"
#include <vector>

using namespace std;

// Tulostaa shakkilaudan ascii-grafiikkana.
void tulosta_lauta(const Asema& asema)
{
	const string nappulat[] =
	{ "R", "N", "B", "Q", "K", "P", "r", "n", "b", "q", "k", "p", " " };

	for (int i = 0; i < 8; i++) {
		cout << " +---+---+---+---+---+---+---+---+" << endl;
		cout << 8 - i << "| ";
		for (int j = 0; j < 8; j++) {
			cout << nappulat[asema._lauta[i][j]] << " | ";
		}
		cout << endl;
	}
	cout << " +---+---+---+---+---+---+---+---+" << endl;
	cout << "   A   B   C   D   E   F   G   H" << endl;
}

int main()
{
	// Alkuasema.
	Asema asema;
	vector<Siirto> siirrot;

	asema.tyhjenna();
	asema._lauta[3][4] = wR;
	asema.anna_tornin_raakasiirrot(3, 4, VALKEA, siirrot);

	for (Siirto s : siirrot)
	{
		// tulosta siirron s tiedot
	}

	//tulosta_lauta(asema);
	//
	//cout << endl;

	//string siirra = "e2e4";
	//Siirto siirto(siirra);
	//asema.tee_siirto(siirto);

	//tulosta_lauta(asema);

	return 0;
}