#include "asema.h"
#include <vector>

// Tyhjent‰‰ laudan.
void Asema::tyhjenna()
{
	for (int rivi = 0; rivi < 8; ++rivi)
		for (int linja = 0; linja < 8; ++linja)
			_lauta[rivi][linja] = NA;
}

void Asema::lisaa_siirto(int rivi, int linja, int rivi_nyt, int linja_nyt,
	std::vector<Siirto>& siirrot, int pelaaja)
{
	if (rivi_nyt < 0 || rivi_nyt >= 8 || linja_nyt < 0 || linja_nyt >= 8)
	{
		return;
	}

	if (_lauta[rivi_nyt][linja_nyt] == NA)
	{
		siirrot.push_back(Siirto(rivi, linja, rivi_nyt, linja_nyt));
	}
	else if (nappulan_vari(_lauta[rivi][linja_nyt]) != pelaaja)
	{
		siirrot.push_back(Siirto(rivi, linja, rivi_nyt, linja_nyt));
	}
}

void Asema::anna_tornin_raakasiirrot(int rivi, int linja, int pelaaja,
	std::vector<Siirto>& siirrot)
{
	// Ylˆs (up)
	for (int rivi_nyt = rivi - 1; rivi_nyt >= 0; rivi_nyt--)
	{
		lisaa_siirto(rivi, linja, rivi_nyt, linja, siirrot, pelaaja);
		if (_lauta[rivi_nyt][linja] != NA)
		{
			break;
		}
	}

	// Alas (down)
	for (int rivi_nyt = rivi + 1; rivi_nyt < 8; rivi_nyt++)
	{
		lisaa_siirto(rivi, linja, rivi_nyt, linja, siirrot, pelaaja);
		if (_lauta[rivi_nyt][linja] != NA)
		{
			break;
		}
	}

	// Oikea (right)
	for (int linja_nyt = linja + 1; linja_nyt < 8; linja_nyt++)
	{
		lisaa_siirto(rivi, linja, rivi, linja_nyt, siirrot, pelaaja);
		if (_lauta[rivi][linja_nyt] != NA)
		{
			break;
		}
	}

	// Vasen (left)
	for (int linja_nyt = linja - 1; linja_nyt >= 0; linja_nyt--)
	{
		lisaa_siirto(rivi, linja, rivi, linja_nyt, siirrot, pelaaja);
		if (_lauta[rivi][linja_nyt] != NA)
		{
			break;
		}
	}
}


// Tekee annetun siirron laudalla. Voidaan olettaa, ett‰
// siirto on laillinen.
void Asema::tee_siirto(const Siirto& s)
{
	// Otetaan alkuruudussa oleva nappula talteen.
	int nappula = _lauta[s._a_r][s._a_l];

	// Tyhjennet‰‰n alkuruutu.
	_lauta[s._a_r][s._a_l] = NA;

	// Sijoitetaan loppuruutuun alkuper‰inen nappula.
	_lauta[s._l_r][s._l_l] = nappula;
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