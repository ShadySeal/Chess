#include <iostream>
#include <string>
#include "asema.h"
#include "siirto.h"
#include <vector>

using namespace std;

int main()
{
	// Alkuasema.
	Asema asema;
	vector<Siirto> siirrot;
	asema.anna_tornin_raakasiirrot(6, 3, MUSTA, siirrot);

	asema.tulosta();

	for (Siirto s : siirrot)
	{
		s.tulosta();
		cout << endl;
	}

	return 0;
}