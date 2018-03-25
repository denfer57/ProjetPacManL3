#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

#include "AElement.h"

using namespace std;

constexpr int LIBRE = 0;
constexpr int OUVERT = 1;
constexpr int FERME = 2;


class InfoAStar
{
public:
	const static char *ETATS[]; 

	AElement * pere;	// pointeur sur un Sommet<?>. où ? est une classe composée ou dérivée de InfoStar
	int etat;		// LIBRE, OUVERT ou FERMé
	double c;		// coût déjà calculé. cf. A* ou Dijkstra
	double h;		// estimation heuristique. cf. A*
	double g;		// coût total : g = h+c

	explicit InfoAStar(AElement * pere = NULL, const int etat = LIBRE,
		const double & c = 0, const double & h = 0, const double & g = 0) :
		pere(pere), etat(etat), c(c), h(h), g(g) {}

	operator string() const;

	friend ostream & operator << (ostream & os, const InfoAStar & infoAStar) { return os << (string)infoAStar; }
};


