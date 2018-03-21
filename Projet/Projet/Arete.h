#pragma once

#include "Sommet.h"

//Classe template repr�sentant une ar�te du graphe.
//Une ar�te relie deux sommets une information de type S et une information de type T.
template <class S, class T>
class Arete : public GrapheComposant
{
public:
	Sommet<T> * debut;
	Sommet<T> * fin;

	S info;

	//Construit une ar�te � partir d'une cle unique, du sommet de d�part et d'arriv� ainsi que et d'une information.
	Arete(const int cle, Sommet<T> * debut, Sommet<T> * fin, const S & info) : GrapheComposant(cle), debut(debut), fin(fin), info(info) { }

	//Convertit l'arete en chaine de caract�re
	operator string() const;

	//V�rifie si une ar�te relie deux sommets s1 et s2
	bool relie(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template <class S, class T>
Arete<S, T>::operator string() const
{
	ostringstream oss;

	oss << "Arete (" << endl;
	oss << GrapheComposant::operator string() << endl;
	oss << "cl� du sommet de d�part = " << debut->cle << endl;
	oss << "cl� du sommet de fin = " << fin->cle << endl;
	oss << "info = " << info << endl;
	oss << ")";

	return oss.str();
}

template <class S, class T>
bool Arete<S, T>::relie(const Sommet<T> * s1, const Sommet<T> * s2) const
{
	return (s1 == debut && s2 == fin) || (s1 == fin && s2 == debut);
}

template <class S, class T>
ostream & operator<<(ostream & os, const Arete<S, T> & arete)
{
	return os << (string)arete;
}