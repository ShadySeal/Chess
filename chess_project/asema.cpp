#include "asema.h"
#include <vector>

// Tyhjentää laudan.
void Asema::tyhjenna()
{
	for (int rivi = 0; rivi < 8; ++rivi)
		for (int linja = 0; linja < 8; ++linja)
			_lauta[rivi][linja] = NA;
}

void Asema::anna_raakasiirrot_suunnassa(int rivi, int linja, int rivi_muutos, int linja_muutos, int pelaaja,
	int max_askeleet, bool voi_lyoda, bool pakko_lyoda, std::vector<Siirto>& siirrot) const
{
	// Ylös (up)
	int rivi_nyt = rivi;
	int linja_nyt = linja;
	int askeleet = 0;

	while (askeleet < max_askeleet)
	{
		rivi_nyt+= rivi_muutos;
		linja_nyt += linja_muutos;

		if (rivi_nyt < 0 || rivi_nyt >= 8 || linja_nyt < 0 || linja_nyt >= 8)
		{
			return;
		}

		// Tyhjä ruutu?
		if (_lauta[rivi_nyt][linja_nyt] == NA)
		{
			if (pakko_lyoda)
			{
				break;
			}
			siirrot.push_back(Siirto(rivi, linja, rivi_nyt, linja_nyt));
			askeleet++;
			continue;
		}

		// Törmätään omaan nappulaan?
		if (nappulan_vari(_lauta[rivi_nyt][linja_nyt]) == pelaaja)
			break;

		// Lyödään vastustajan nappula.
		if (voi_lyoda)
		{
			siirrot.push_back(Siirto(rivi, linja, rivi_nyt, linja_nyt));
		}
		break;
	}
}

void Asema::anna_tornin_raakasiirrot(int rivi, int linja, int pelaaja,
	std::vector<Siirto>& siirrot)
{
	anna_raakasiirrot_suunnassa(rivi, linja, -1, 0, pelaaja, 7, true, false, siirrot);
	anna_raakasiirrot_suunnassa(rivi, linja, 1, 0, pelaaja, 7, true, false, siirrot);
	anna_raakasiirrot_suunnassa(rivi, linja, 0, -1, pelaaja, 7, true, false, siirrot);
	anna_raakasiirrot_suunnassa(rivi, linja, 0, 1, pelaaja, 7, true, false, siirrot);
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

	_siirtovuoro = vastustaja(_siirtovuoro);
}

void Asema::tulosta() const
{
	const string nappulat[] =
	{ "R", "N", "B", "Q", "K", "P", "r", "n", "b", "q", "k", "p", " " };

	for (int i = 0; i < 8; i++) {
		cout << " +---+---+---+---+---+---+---+---+" << endl;
		cout << 8 - i << "| ";
		for (int j = 0; j < 8; j++) {
			cout << nappulat[_lauta[i][j]] << " | ";
		}
		cout << endl;
	}
	cout << " +---+---+---+---+---+---+---+---+" << endl;
	cout << "   A   B   C   D   E   F   G   H" << endl;
}