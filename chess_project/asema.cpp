#include "asema.h"
#include <vector>

// Tyhjentää laudan.
void Asema::tyhjenna()
{
	for (int rivi = 0; rivi < 8; ++rivi)
		for (int linja = 0; linja < 8; ++linja)
			_lauta[rivi][linja] = NA;
}

void Asema::anna_tornin_raakasiirrot(int rivi, int linja, int pelaaja,
	std::vector<Siirto>& siirrot)
{
	// Ylös (up)
	int rivi_nyt = rivi;
	int linja_nyt = linja;

	while (true)
	{
		rivi_nyt--;

		// Ulkona laudalta?
		if (rivi_nyt < 0)
		{
			break;
		}

		// Tyhjä ruutu?
		if (_lauta[rivi_nyt][linja_nyt] == NA)
		{
			siirrot.push_back(Siirto(rivi, linja, rivi_nyt, linja_nyt));
			continue;
		}

		// Törmätään omaan nappulaan?
		if (nappulan_vari(_lauta[rivi][linja_nyt]) == pelaaja)
		{
			break;
		}

		// Lyödään vastustajan nappula.
		siirrot.push_back(Siirto(rivi, linja, rivi_nyt, linja_nyt));
		break;
	}
}

// Tekee annetun siirron laudalla. Voidaan olettaa, että
// siirto on laillinen.
void Asema::tee_siirto(const Siirto& s)
{
	// Otetaan alkuruudussa oleva nappula talteen.
	int nappula = _lauta[s._a_r][s._a_l];

	// Tyhjennetään alkuruutu.
	_lauta[s._a_r][s._a_l] = NA;

	// Sijoitetaan loppuruutuun alkuperäinen nappula.
	_lauta[s._l_r][s._l_l] = nappula;
}