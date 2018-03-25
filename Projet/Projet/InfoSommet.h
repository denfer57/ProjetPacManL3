#pragma once
#include "InfoAStar.h"
/**

Information associée à un lieu (donc un sommet) d'une carte géographique pour laquelle on veut faire "tourner" A*

*/

class InfoSommet
{
public:
	string nom;
	//InfoAStar infoAStar;

	InfoSommet(const string & nom) : nom(nom) {}
	InfoSommet() {};
	//InfoSommet(const string & nom, const InfoAStar & infoAStar) : nom(nom), infoAStar(infoAStar) {}

	//operator string() const { ostringstream oss; oss << nom << endl; oss << infoAStar; return oss.str(); }
	operator string() const { ostringstream oss; oss << nom << endl; return oss.str(); }
	friend ostream & operator <<(ostream & os, const InfoSommet & infoSommet) { return os << (string)infoSommet; }
};




