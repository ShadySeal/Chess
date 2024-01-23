#include "siirto.h"

Siirto::Siirto(const std::string& s)
{
	_a_l = s[0] - 'a';
	_a_r = '8' - s[1];
	_l_l = s[2] - 'a';
	_l_r = '8' - s[3];
}

void Siirto::tulosta() const
{
	cout << "Sallitut siirrot: (" << _l_r << ", " << _l_l << ")";
}