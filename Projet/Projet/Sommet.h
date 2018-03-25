#pragma once

#include "GElement.h"

//Classe template repr�sentant un sommet d'un graphe.
template <class T>
class Sommet : public GElement<T>
{
public:
	int degre;

	T info;

	//Construit un sommet du graphe � partir d'une cl� unique et d'une information. Le d�gr� est � 0 par d�faut.
	Sommet(const int clef, const T & v) :GElement<T>(clef, v), degre(0) {}

	//Convertit en chaine de caract�re
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
