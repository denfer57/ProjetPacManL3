#pragma once

#include "GElement.h"

//Classe template représentant un sommet d'un graphe.
template <class T>
class Sommet : public GElement<T>
{
public:
	int degre;

	T info;

	//Construit un sommet du graphe à partir d'une clé unique et d'une information. Le dégré est à 0 par défaut.
	Sommet(const int clef, const T & v) :GElement<T>(clef, v), degre(0) {}

	//Convertit en chaine de caractère
	operator string() const;
};

template<class T>
Sommet<T>::operator string() const
{
	ostringstream oss;

	oss << "Sommet (" << endl;
	oss << GElement<T>::operator string() << endl;
	oss << "degre = " << degre << endl;
	oss << "info = " << info << endl;
	oss << ")";

	return oss.str();
}

template <class T>
ostream & operator<<(ostream & os, const Sommet<T> & sommet)
{
	return os << (string)sommet;
}
