#pragma once

#include <string>
#include <iostream>
#include <sstream>

using namespace std;


//Information associée à une arête  (segment rectiligne) joignant 2 lieux d'une carte routière.

//On ne stocke que le côut de l'arête, c-à-d sa longueur et sa couleur


class InfoArete
{
public:

	double cout1;
	unsigned int couleur;

	/**
	Par défaut, la couleur d'une arête est le bleu
	*/
	explicit InfoArete(const double & cout1, const unsigned int couleur = 0x0000FFFF) :cout1(cout1), couleur(couleur) {}

	operator string() const;
	friend ostream & operator << (ostream & os, const InfoArete & infoArete) { return os << (string)infoArete; }
};

inline InfoArete::operator string() const
{
	ostringstream oss;

	oss << "coût = " << cout1 << ", " << couleur;

	return oss.str();
}

