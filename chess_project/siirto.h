#pragma once
#include <string>
#include <iostream>

using namespace std;

// Kuvaa aseman muutosta.
class Siirto
{
public:
	Siirto(int a_r, int a_l, int l_r, int l_l) :
		_a_r(a_r), _a_l(a_l), _l_r(l_r), _l_l(l_l)
	{}

	Siirto(const std::string& s);

	void tulosta() const
	{
		cout << "Sallitut siirrot: (" << _l_r << ", " << _l_l << ")";
	}

private:
	int _a_r; // siirron alkuruudun rivi
	int _a_l; // siirron alkuruudu linja (eli sarake)

	int _l_r; // siirron loppuruudun rivi
	int _l_l; // siirron loppuruudun linja

	friend class Asema;
};